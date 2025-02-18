#include <iostream>
#include <vector>
#include <queue>
#include <bits/stdc++.h>

#define INF 10000

using namespace std;

int V= 9;

vector<int> dijkstra(vector<vector<pair<int, int>>> g, int start)
{
    vector<int> dist(g.size(), INT_MAX);
    // <weight, vertex> pair. First element of priority queue will be the minimum
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    // priority queue compares first element default so put the weight first.
    pq.push({0, start}); // weight, vertex
    dist[start] = 0;

    while (!pq.empty())
    {
        int u = pq.top().second;
        printf("%d->", u);
        pq.pop();

        for (int i = 0; i < g[u].size(); i++)
        {
            int v = g[u][i].first;  // vertex
            int w = g[u][i].second; // weight

            if (dist[v] > dist[u] + w)
            {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

int minVertex( int *D,int *visited)
{
    int i, v=-1;

    for(i=0; i<V; i++)
        if(visited[i]==0){
            //printf("**%d   %d\n",i,D[i]);
            v=i; break;
        }
     //printf("i=%d \n",i);   
    for(i++; i< V; i++)
        if(visited[i]==0 && D[i]< D[v])
            v=i;
    //printf("* v=%d \n",v);
    return v;
}
void Dijkstra(vector<vector<pair<int,int>>> g,int *D,int s)
{
    int i,v,w;
    int visited[V];

    for(i=0;i < V; i++) {
          D[i]=INF;
          visited[i]=0;
    }
     
    D[0]=0;
    for(i=0; i< V;i++){
        v= minVertex(D,visited);
        if(D[v]==INF) return ;
        visited[v]=1;
        for(w=0; w <g[v].size(); w++)
            if(D[g[v][w].first] > (D[v] + g[v][w].second))
                D[g[v][w].first] = D[v] + g[v][w].second;
    }
}

void addEdge(vector<vector<pair<int, int>>> &g, int u, int v, int w)
{
    g[u].push_back({v, w});
    g[v].push_back({u, w});
}

int main()
{
    // pair of node, weight
    vector<vector<pair<int, int>>> graph(V, vector<pair<int, int>>(V));
    int D[V];

    addEdge(graph, 0, 1, 4);
    addEdge(graph, 0, 7, 8);
    addEdge(graph, 1, 2, 8);
    addEdge(graph, 1, 7, 11);
    addEdge(graph, 2, 3, 7);
    addEdge(graph, 2, 8, 2);
    addEdge(graph, 2, 5, 4);
    addEdge(graph, 3, 4, 9);
    addEdge(graph, 3, 5, 14);
    addEdge(graph, 4, 5, 10);
    addEdge(graph, 5, 6, 2);
    addEdge(graph, 6, 7, 1);
    addEdge(graph, 6, 8, 6);
    addEdge(graph, 7, 8, 7);

    vector<int> dist = dijkstra(graph, 0);
    // Print shortest distances stored in dist[]
    cout << "Vertex      Distance from Source" << endl;
    for (int i = 0; i < V; ++i)
        cout << i << "\t\t" << dist[i] << endl;

    Dijkstra(graph,D,0);
    cout << "New Vertex      Distance from Source" << endl;
    for (int i = 0; i < V; ++i)
        cout << i << "\t\t" << D[i] << endl;

    return 0;
}
