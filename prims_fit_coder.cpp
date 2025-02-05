#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <bits/stdc++.h>

using namespace std;

vector<tuple<int,int,int>> prim(vector<vector<pair<int,int>>>& g,
    int start)
{
    vector<int> parent(g.size(),-1);
    vector<int> key(g.size(),INT_MAX);
    vector<int> inMST(g.size(), false);
    key[start]=0;

    priority_queue<pair<int,int>,vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({0,start});

    vector<tuple<int,int,int>> result;

    while(!pq.empty()){
        int v= pq.top().second; pq.pop();

        if(parent[v] !=-1 && inMST[v] ==false)
            result.push_back({parent[v],v,key[v]});
        
        inMST[v]=true;
        //cout<<v<<endl;
        for(auto x: g[v]){
            int av=x.first;   
            int w=x.second;
            if(inMST[av] ==false && key[av]> w)   //weigh is less than INF
            {
                parent[av]=v;
                key[av]=w;
                pq.push({key[av],av});
            }
        }
    }
    return result;

}

void addEdge(vector<vector<pair<int,int>>>& g, int u,int v,int w)
{
    g[u].push_back({v,w});
    g[v].push_back({u,w});
}


int main()
{
    int V = 7;
    // pair of vertex, weight
    vector<vector<pair<int, int>>> graph(V, vector<pair<int, int>>(V));

    addEdge(graph, 0, 1, 2);
    addEdge(graph, 0, 3, 7);
    addEdge(graph, 0, 5, 2);
    addEdge(graph, 1, 2, 1);
    addEdge(graph, 1, 3, 4);
    addEdge(graph, 1, 4, 3);
    addEdge(graph, 1, 5, 5);
    addEdge(graph, 2, 4, 4);
    addEdge(graph, 2, 5, 4);
    addEdge(graph, 3, 4, 1);
    addEdge(graph, 3, 6, 5);
    addEdge(graph, 4, 6, 7);

    vector<tuple<int, int, int>> res = prim(graph, 0);
    cout << "Minimum Spanning Tree: " << endl;
    for (tuple<int, int, int> t : res)
        cout << get<0>(t) << "-" << get<1>(t) << "," << get<2>(t) << endl;
    return 0;
}