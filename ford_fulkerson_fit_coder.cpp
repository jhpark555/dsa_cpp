#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int bfs(int source, int sink, vector<int>& parent, vector<vector<int>>&resG)
{
    for(int i=0;i<parent.size(); i++) parent[i]=-1;
    int V=resG.size();
    parent[source]=-2;
    queue<pair<int,int>> q;
    q.push({source,INT_MAX});

    while(!q.empty()){
        int u=q.front().first;
        int capacity=q.front().second;
        q.pop();
        for(int av=0; av< V; av++){
            if(u !=av && parent[av]==-1 &&resG[u][av] !=0){
                parent[av]=u;
                int min_cap=min(capacity, resG[u][av]);
                if(av==sink)  
                    return min_cap;
                q.push({av,min_cap});
            }
        }
    }
    return 0;
}

int ford_fulkerson(vector<vector<int>>&graph, int source ,int sink)
{
    vector<int> parent(graph.size(),-1);
    vector<vector<int>> resG=graph;
    int min_cap=0;
    int max_flow=0;

    while( min_cap=bfs(source,sink,parent,resG)){
        max_flow +=min_cap;
        int u=sink;
        while(u!=source){
            int v = parent[u];
            resG[u][v] +=min_cap;
            resG[v][u] -=min_cap;
            u=v;    //u->v
        }
    }
    return max_flow;
}

void addEdge(vector<vector<int>>& graph,int u, int v, int w)
{
    graph[u][v]=w;
}

int main()
{
    int V = 6;
    vector<vector<int>> graph(V, vector<int>(V, 0));

    addEdge(graph, 0, 1, 16);
    addEdge(graph, 0, 3, 13);
    addEdge(graph, 1, 2, 12);
    addEdge(graph, 2, 3, 9);
    addEdge(graph, 2, 5, 20);
    addEdge(graph, 3, 4, 14);
    addEdge(graph, 3, 1, 4);
    addEdge(graph, 4, 2, 7);
    addEdge(graph, 4, 5, 4);

    cout << "Maximum Flow: " << ford_fulkerson(graph, 0, 5) << endl;
    return 0;
}
