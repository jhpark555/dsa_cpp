#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int V=7;

void addEdge(vector<int> g[], int u, int v)
{
    g[u].push_back(v);
    g[v].push_back(u);
}

void bfs(vector<int> g[], int start)
{
    vector<bool> visited(V,false);
    queue<int> q;
    q.push(start);
    visited[start]=true;
    vector<int> d(V),p(V);
    p[start]=-1;

    while(!q.empty()){
        int v=q.front();
        cout<<v <<"  ";
        q.pop();

        //for(int i=0; i< g[v].size(); i++){
        for(int u: g[v]){
            //if(!visited[g[v][i]])
            if(!visited[u]){
                //q.push(g[v][i]);
                q.push(u);
                //visited[g[v][i]] = true;
                visited[u]=true;
                d[u]=d[v]+1;
                p[u]=v;
            }
        }
    }
}

int main()
{
    vector<int> g[V];

    addEdge(g, 0, 1);
    addEdge(g, 0, 3);
    addEdge(g, 1, 2);
    addEdge(g, 2, 3);
    addEdge(g, 2, 6);
    addEdge(g, 3, 4);
    addEdge(g, 4, 5);
    addEdge(g, 5, 6);

    cout<<"BFS : \n"; 
    bfs(g,0);

    return 0;
}