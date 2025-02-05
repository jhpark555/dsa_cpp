#include <iostream>
#include <vector>
#include <queue>
#include <bits/stdc++.h>

using namespace std;

vector<int> dijkstra(vector<vector<pair<int,int>>> g, int start)
{
    vector<int> dist(g.size(), INT_MAX);
    //weight,vertex pair
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;

    pq.push({start,0});    //vertex, weight
    dist[start]=0;

    while(!pq.empty()){
        int u=pq.top().first;
        //printf("%d->",u);
        pq.pop();

        for(int i=0; i< g[u].size(); i++){
            int v=g[u][i].first;   //vertex
            int w=g[u][i].second;   //weight

            if(dist[v] > dist[u] + w){
                dist[v]=dist[u]+w;
                pq.push({v,dist[v]});
            }
        }
    }
    return dist;

}

void addEdge(vector<vector<pair<int,int>>>&g, int u, int v, int w)
{
    g[u].push_back({v,w});
    g[v].push_back({u,w});
}

int main()
{
    // pair of node, weight
    vector<vector<pair<int, int>>> graph(9, vector<pair<int, int>>(9));

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
    for (int i = 0; i < 9; ++i)
        cout << i << "\t\t" << dist[i] << endl;
    return 0;
}
