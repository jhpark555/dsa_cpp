#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int V=7;

void addEdge(vector<int> g[], int u, int v)
{
    g[u].push_back(v);
    g[v].push_back(u);
}

void dfs(vector<int> g[], vector<bool> &visited, int v)
{
    visited[v]=true;
    cout<< v<<"  ";
    //for(int i=0; i< g[v].size(); i++)
    for(auto u: g[v])
        //if(!visited[g[v][i]])
        if(!visited[u])
            //dfs(g,visited,g[v][i]);
            dfs(g,visited,u);
}

void dfs_iter(vector<int> g[],  int v)
{
    vector<int> visited(V,false);
    stack<int> st;
    st.push(v);
    visited[v]=true;
    while(!st.empty()){
        int u= st.top(); st.pop();
        cout<<u<<"  ";
        for(int i=0; i<g[u].size(); i++)
            if(!visited[g[u][i]]){
                st.push(g[u][i]);
                visited[g[u][i]]=true;
            }               
    }

}

int farthestNode(int curr, vector<bool>& visited, vector<int> adj[], int dist) {
    if (visited[curr]) return 0;

    visited[curr] = true;
    int maxDist = dist;

    for (int next : adj[curr]) {
        // visiting the next node 
        // if not visited already
        if (!visited[next]) {
            maxDist = max(maxDist, farthestNode(next, visited, adj, dist + 1));
        }
    }
    return maxDist;
}

int diameter(vector<int> adj[]) {
    int n = V;
    int res = 0;

    // taking maximum across all nodes
    for (int i = 0; i < n; i++) {
        vector<bool> visited(n, false);
        res = max(res, farthestNode(i, visited, adj, 0));
    }
    return res;
}

int main()
{
    vector<int> g[V];

    
   // addEdge(g, 0, 1);
    addEdge(g, 0, 3);
    addEdge(g, 1, 2);
   // addEdge(g, 2, 3);
    addEdge(g, 2, 6);
    addEdge(g, 3, 4);
    addEdge(g, 4, 5);
   // addEdge(g, 5, 6);
    

    cout<<"DFS : \n";
    vector<bool> visited(V,false);
    dfs(g,visited,0);
    cout<<"\n";
    dfs_iter(g,0);
    int max= diameter(g);
    printf("max diameter=%d \n",max);
    
    return 0;

}