#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int V = 7;

vector<int> comp(V);

void addEdge(vector<int> g[], int u, int v)
{
    g[u].push_back(v);
    g[v].push_back(u);
}

void dfs(vector<int> g[], vector<bool> &visited, int v)
{
    visited[v] = true;
   // cout << v << "  ";
    comp.push_back(v);
    for (auto u : g[v])
        if (!visited[u])
            dfs(g, visited, u);
}

void find_comps(vector<int> g[], vector<bool>& visited)
{
    for(int v=0;v < V; ++v){
        if(!visited[v]){
            comp.clear();
            dfs(g,visited,v);
            cout<<"Component: ";
            for( auto u:comp)
                cout<<' '<<u;
            cout<<"\n";
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

        
    cout << "find_comp : \n";
    vector<bool> visited(V, false);
    find_comps(g, visited);
    
    return 0;
}