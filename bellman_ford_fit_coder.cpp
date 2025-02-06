#include <iostream>
#include <vector>
#include <map>

using namespace std;

//bool bellman_ford(int start, map<pair<int, int>, int> &edges,
//                  vector<int> &dist, int V)
bool bellman_ford(int start, vector<tuple<int,int,int>> &edges,
                  vector<int> &dist, int V)
{
    for(int i=0; i< V; i++){
        for( auto e: edges)
        {
            int u=get<0>(e);//e.first.first;
            int v=get<1>(e);//e.first.second;
            int w=get<2>(e);//e.second;
            if(dist[u]!=INT_MAX && (dist[v]>dist[u] +w ))
                dist[v]=dist[u]+w;
        }
    }
    for(auto e: edges)
    {
        int u= get<0>(e);//e.first.first;
        int v=get<1>(e);//e.first.second;
        int w=get<2>(e);//e.second;
        if (dist[u] != INT_MAX && (dist[v] > dist[u] + w))
            return false;
    }
    return true;
}

//void addEdge(map<pair<int,int>,int>& edges, int u, int v, int w)
void addEdge(vector<tuple<int,int,int>> &edges, int u,int v,int w)
{
   // edges[{u,v}]=w;
   edges.push_back({u,v,w});
}
int main()
{
    int V=5;
    //map<pair<int,int>,int> edges;
    vector<tuple<int,int,int>> edges;
    addEdge(edges, 0, 1, 6);
    addEdge(edges, 0, 2, 7);
    addEdge(edges, 1, 3, 5);
    addEdge(edges, 3, 1, -2);
    addEdge(edges, 1, 2, 8);
    addEdge(edges, 2, 4, 9);

    addEdge(edges, 2, 3, -3);
    addEdge(edges, 1, 4, -4);
    addEdge(edges, 4, 0, 2);
    addEdge(edges, 4, 3, 7);    //4 negative

    vector<int> dist(V,INT_MAX);
    int start=0;
    dist[start]=0;
    bool res = bellman_ford(start, edges, dist, V);
    if (!res)
        cout << "Negative-weight cycle exists" << endl;
    else
    {
        cout << "Shortest path distance from start vertex (" << start << ")" << endl;
        for (int i = 0; i < V; i++)
            cout << start << "-" << i << " : " << dist[i] << endl;
    }
    return 0;
}
