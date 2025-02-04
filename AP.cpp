#include <bits/stdc++.h>

using namespace std;

int V=5;
int Time=0;

vector<int> low(V+1,0), disc(V+1,0),ap(V+1,0);

void dfs(vector<int> adj[], int v, vector<int> & vis, int i, int curr)
{
   vis[curr]= 1;

   for(auto x: adj[curr]){
    if(x!=i){
        if(!vis[x])
            dfs(adj,v,vis,i,x);
    }
   }
}

void AP(vector<int> adj[],int v)
{
    for(int i=1; i<=v ; i++){
        int components=0;
        vector<int> vis(v+1,0);
        for(int j=1; j<=v ;j++){
            if(j!=i){
                if(!vis[j]){
                    components++;
                    dfs(adj,v,vis,i,j);
                }
            }
        }
        if(components>1){
            std::cout<<i<<"\n";
        }
    }
}

int dfsAP(int u,int p,vector<int> adj[])
{
    int children =0;
    low[u]=disc[u]= ++Time;

    for(int &v :adj[u]){
        if(v==p) continue;

        if(!disc[v]){
            children++;
            dfsAP(v,u,adj);
            if(disc[u]<=low[v])
                ap[u] =1;
            low[u]=min( low[u],low[v]);
        }
        else   
            low[u]=min( low[u], disc[v]);
    }
    return children;
}

void AP1(vector<int> adj[])
{
   
  for ( int u=1; u<= V; u++){
    if(!disc[u]){
        ap[u]=dfsAP(u,u,adj)>1;
        printf("%d ,",ap[u]);
    }
  }

}
void addEdge(vector<int> adj[],int u, int v)
{
    adj[u].push_back(v);
    adj[v].push_back(u);
}

int main()
{
    
    vector<int> adj[V+1];
    addEdge(adj, 1, 2);
    addEdge(adj, 2, 3);
    addEdge(adj, 1, 3);
    addEdge(adj, 3, 4);
    addEdge(adj, 4, 5);

    AP(adj,V);

    AP1(adj);

    return 0;
}