#include <iostream>
#include <vector>
#include <list>
#include <queue>

using namespace std;

int V=5;
void addEdge(vector<int> graph[], int u, int v)
{
    graph[u].push_back(v);
}
void topological_sort(vector<int> g[], vector<bool>& visited, list<int>&result, int node)
{
    visited[node]=true;
    //for(auto i=g[node].begin(); i!=g[node].end(); i++)
    //for(int i=0; i<g[node].size(); i++)
    for(auto u: g[node])
        //if(!visited[g[node][i]])
        if(!visited[u])
            //topological_sort(g,visited,result,g[node][i]);
            topological_sort(g,visited,result,u);
    result.push_front(node);
}
void topsort(vector<int> g[])
{
    int count[V];
    queue<int> q;

    for(int i=0;i<V;i++)  count[i]=0;
    
    for(int v=0; v< V; v++)
        for(auto w: g[v])
            count[w]++;
    for(int v=0; v<V; v++)
        if(count[v]==0)
            q.push(v);
    while(!q.empty()){
        int v=q.front(); q.pop();
        cout<<v<<" ";
        for( auto w: g[v]){
            count[w]--;
            if(count[w]==0)
                q.push(w);
                
        }
    }
}
int main()
{
    
    vector<int> g[V];
    vector<bool> vis(V,false);

    addEdge(g, 0, 1);
    addEdge(g, 0, 2);
    addEdge(g, 1, 2);
    addEdge(g, 1, 3);
    addEdge(g, 2, 3);
    addEdge(g, 2, 4);

    list<int> result;

    cout<<"Topological sort result DFS: \n";
    for(int i=0;i< V;i++)
        if(!vis[i])
            topological_sort(g,vis,result,i);

    for(auto i: result)
        cout<<i<<" ";
    
    cout<<"Topological sort not recursive way\n";
    topsort(g);
}