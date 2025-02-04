#include <bits/stdc++.h>

// https://www.topcoder.com/thrive/articles/kosarajus-algorithm-for-strongly-connected-components

#define MAX_N 20001
#define ll long long int

using namespace std;
int n,m;

struct Node{
    vector<int> adj;
    vector<int> rev_adj;
};

Node g[MAX_N];

stack<int> S;
bool visited[MAX_N];

int component[MAX_N];
vector<int> components[MAX_N];
int numComponents;

void dfs_1(int x){
    visited[x]=true;
    for(int i=0; i< g[x].adj.size(); i++){
        if(!visited[g[x].adj[i]])
            dfs_1(g[x].adj[i]);
    }
    S.push(x);
    //printf("%d->",x);
}

void dfs_2(int x){
    printf(" %d", x);
    //component[x]=numComponents;
    //components[numComponents].push_back(x);
    visited[x]=true;
    for(int i=0; i< g[x].rev_adj.size(); i++){
        if (!visited[g[x].rev_adj[i]]) dfs_2(g[x].rev_adj[i]);
    }
}

void Kosaraju(){
    for(int i=0; i< n;i++)
        if(!visited[i]) dfs_1(i);

    for(int i=0;i<n ; i++)
        visited[i]=false;

    while(!S.empty()){
        int v=S.top();  S.pop();
        //printf("%d->", v);
        if(!visited[v]){
            printf("Component count %d: ",numComponents);
            dfs_2(v);
            numComponents++;
            printf("\n");
        }
    }
}

void topologicalSort()
{
    for(int i=0;i <=8;i++)   visited[i]=false;

    for(int x=0; x< 8; x++)
      for(int i=0;i< g[x].adj.size(); i++)
        if(!visited[i])
            dfs_1(i);

    for(int i=0;i <8; i++)
    {
        int v= S.top(); S.pop();
        printf("%d->",v);
    }
}

int main()
{
    n=8; m=10;

    g[0].adj.push_back(1);
    g[1].rev_adj.push_back(0);
    g[1].adj.push_back(2);
    g[2].rev_adj.push_back(1);
    g[2].adj.push_back(0);
    g[0].rev_adj.push_back(2);
    g[2].adj.push_back(3);
    g[3].rev_adj.push_back(2);
    g[3].adj.push_back(4);
    g[4].rev_adj.push_back(3);
    g[4].adj.push_back(5);
    g[5].rev_adj.push_back(4);
    g[5].adj.push_back(6);
    g[6].rev_adj.push_back(5);
    g[6].adj.push_back(7);
    g[7].rev_adj.push_back(6);
    g[4].adj.push_back(7);
    g[7].rev_adj.push_back(4);
    g[6].adj.push_back(4);
    g[4].rev_adj.push_back(6);

    Kosaraju();

    printf("Total number of components: %d \n",numComponents);

    topologicalSort();
     return 0;
}