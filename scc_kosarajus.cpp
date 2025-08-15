
#include <iostream>
#include <vector>
#include <stack>

int  V=7;
using namespace std;

void edge(vector<vector<int>> &adj,int u, int v)
{
    adj[u].push_back(v);
    
}

void dfsFill(int u, vector<vector<int>>& adj, vector<bool>& visited, stack<int>& st)
{
        visited[u] = true;
        
        for(int &v : adj[u]) {
            if(!visited[v]) {
                dfsFill(v, adj, visited, st);
            }
        }
        
        st.push(u);
}
    
    
// Helper function to perform DFS and traverse the reversed graph.
void dfsTraverse(int u, vector<vector<int>>& adjReversed, vector<bool>& visited)
{
        visited[u] = true;
         printf("%d ", u);
        for(int &v : adjReversed[u]) {
            if(!visited[v]) {
                dfsTraverse(v, adjReversed, visited);
            }
        }
}
    
 // Function to find the number of strongly connected components in the graph.
int kosaraju(int V, vector<vector<int>>& adj) 
{
        stack<int> st;
        vector<bool> visited(V, false);
        
        // 1. Fill the stack using DFS on the original graph.
        for(int i = 0; i < V; i++) {
            if(!visited[i]) {
                dfsFill(i, adj, visited, st);
            }
        }
        
        // 2. Create the reversed graph.
        vector<vector<int>> adjReversed(V);
        for(int u = 0; u < V; u++) {
            for(int &v : adj[u]) {
                // Reverse the edges for the reversed graph.
                adjReversed[v].push_back(u);
            }
        }
        
        int count = 0;
        
        // 3. Traverse the stack and perform DFS on the reversed graph to count SCCs.
        visited = vector<bool>(V, false);
        while(!st.empty()) {
            int node = st.top();
            st.pop();
            if(!visited[node]) {
                dfsTraverse(node, adjReversed, visited);
                count++;
                printf("\n");
            }
        }
        
        return count;
}
    
    
int main()
{
    vector<vector<int>> g(V);
    
    edge(g,0,1);
    edge(g,1,3);
    edge(g,1,2);
    edge(g,2,3);
    edge(g,2,5);
    edge(g,3,0);
    edge(g,3,4);
    edge(g,4,5);
    edge(g,5,6);
    edge(g,6,4);
   
   kosaraju(V,g);
   
   // for(auto i:g)
    //   std::cout<<i;

    return 0;
}