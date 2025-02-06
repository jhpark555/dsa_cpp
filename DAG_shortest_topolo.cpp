#include <iostream>
#include <vector>
#include <list>
#include <bits/stdc++.h>

#define INF INT_MAX

using namespace std;

void addEdge(vector<pair<int,int>> graph[], int u, int v,int w)
{
    graph[u].push_back({v,w});
}
void topological_sort(vector<pair<int,int>> g[], vector<bool> &visited, list<int> &result, int node)
{
    visited[node] = true;
    // for(auto i=g[node].begin(); i!=g[node].end(); i++)
    for (int i = 0; i < g[node].size(); i++)
        if (!visited[g[node][i].first])
            topological_sort(g, visited, result, g[node][i].first);
    result.push_front(node);
}

void SrtPath(int V,int s,list<int> &Top,vector<pair<int,int>>g[])
{
    int dist[V];

    for(int i=0; i<V; i++) {
        dist[i]=INF;
    }
    dist[s]=0;

    for(auto itr=Top.begin(); itr!=Top.end(); ++itr)
    {
        int u = *itr;
        if(dist[u] !=INF)
        {
            for(int i=0; i< g[u].size(); i++)
            {
                //cout << u<<"-> ";
                if (dist[g[u][i].first] >dist[u] + g[u][i].second) 
                    dist[g[u][i].first] =dist[u] + g[u][i].second;
            }
        }
    }
    for(int i=0; i< V; i++)
        (dist[i]==INF)? cout<<"INF ": cout<<dist[i]<<" ";   
    
}

int main()
{
    int V = 6;
    vector<pair<int,int>> g[V];
    vector<bool> vis(V, false);

    addEdge(g, 0, 1, 5);
    addEdge(g, 0, 2, 3);
    addEdge(g, 1, 3, 6);
    addEdge(g, 1, 2, 2);
    addEdge(g, 2, 4, 4);
    addEdge(g, 2, 5, 2);
    addEdge(g, 2, 3, 7);
    addEdge(g, 3, 4, -1);
    addEdge(g, 4, 5, -2);

    list<int> result;

    cout << "Topological sort result DFS: \n";
    for (int i = 0; i < V; i++)
        if (!vis[i])
            topological_sort(g, vis, result, i);

    for (auto i : result)
        cout << i << " ";

    cout << "DAG shortest path: \n";
    SrtPath(V,1,result,g);
}