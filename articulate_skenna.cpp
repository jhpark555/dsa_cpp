#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stack>
#include <iostream>
#include <iterator>

using namespace std;

#define MAXV 100
#define UNCOLORED (-1)
#define WHITE (1)
#define BLACK  (0)

#define TREE (1)
#define BACK (-1)
#define FORWARD (2)
#define CROSS (3)


bool processed[MAXV+1];
bool discovered[MAXV+1];
int parent[MAXV+1];
bool finished=false;
int reachable_ancestor[MAXV+1];
int tree_out_degree[MAXV+1];
int entry_time[MAXV+1];

std::stack<int> sorted;


typedef struct graph graph;
void insert_edge(graph *g,int x, int y, bool directed);

typedef struct edgenode{
    int y;
    int weight;
    struct edgenode *next;
}edgenode;

typedef struct graph{
    edgenode *edges[MAXV+1];
    int degree[MAXV+1];
    int nvertices;
    int nedges;
    int directed;
}graph;



void find_path(int start, int end, int parent[]);
void dfs(graph *g, int v);


void initialize_graph(graph *g, bool directed){
    int i;
    
    g->nvertices=0;
    g->nedges = 0;
    g->directed = directed;
    
    for(i=1; i<=MAXV; i++)
        g->degree[i] =0;
        
    for(i =1; i<=MAXV; i++)
        g->edges[i]=NULL;
}



void insert_edge(graph *g,int x, int y, bool directed){
    edgenode *p;
    
    //p=malloc(sizeof(edgenode));
    p = new edgenode;
    p->weight =0;
    p->y =y;
    p->next =g->edges[x];
    g->edges[x]=p; 
    g->degree[x]++;
    

    if(!directed){
        insert_edge(g,y,x, true);
    }
    else{
        g->nedges++;
    }
}

void print_graph(graph *g){
    int i;
    
    edgenode *p;
    
    for(i=1; i<= g->nvertices; i++){
        printf("%d: ",i);
        p=g->edges[i];
        while(p !=NULL){
            printf(" %d", p->y);
            p=p->next;
        }
        printf("\n");
    }
}


void initialize_search(graph *g){
    int i;
    
    for(i=0; i<g->nvertices; i++){
        processed[i]=false;
        discovered[i]=false;
        parent[i]=-1;
    }

}

void process_vertex_early(int v) {
   //printf("processed vertex %d\n", v);
   reachable_ancestor[v]=v;

}

int edge_classification(int x, int y) {
    if (parent[y] == x) {
        return(TREE);
    }
    if (discovered[y] && !processed[y]) {
        return(BACK);
    }
    if (processed[y] && (entry_time[y]>entry_time[x])) {
        return(FORWARD);
    }
    if (processed[y] && (entry_time[y]<entry_time[x])) {
        return(CROSS);
    }
    printf("Warning: self loop (%d,%d)\n", x, y);
    return -1;
}


#if 0 //for articulation 
void process_edge(int x, int y) {
  int clas;  //edge class

  clas= edge_classification(x,y);

  if(clas ==TREE){
    tree_out_degree[x]=tree_out_degree[x]+1;
  }
  if((clas ==BACK) &&(parent[x]!=y)){
    if(entry_time[y] < entry_time[reachable_ancestor[x]]){
        reachable_ancestor[x]=y;
    }
  }

}


void process_vertex_late(int v) {
    bool root; /* is parent[v] the root of the DFS tree? */
    int time_v; /* earliest reachable time for v */
    int time_parent; /* earliest reachable time for parent[v] */
    
    if (parent[v] == -1) { /* test if v is the root */
        if (tree_out_degree[v] > 1) {
            printf("root articulation vertex: %d \n",v);
        }
        return;
    }
    root = (parent[parent[v]] == -1); /* is parent[v] the root? */
        if (!root) {
            if (reachable_ancestor[v] == parent[v]) {
                printf("parent articulation vertex: %d \n", parent[v]);
            }
        if (reachable_ancestor[v] == v) {
            printf("bridge articulation vertex: %d \n",parent[v]);
            if (tree_out_degree[v] > 0) { /* is v is not a leaf? */
                printf("bridge articulation vertex: %d \n", v);
            }
        }
    }
    time_v = entry_time[reachable_ancestor[v]];
    time_parent = entry_time[reachable_ancestor[parent[v]]];
    if (time_v < time_parent) {
        reachable_ancestor[parent[v]] = reachable_ancestor[v];
    }
}
#else    // for topological sort
void process_vertex_late(int v){
    sorted.push(v);
}
void process_edge(int x,int y){
    int clas;

    clas= edge_classification(x,y);

    if(clas ==BACK) printf("Warning : directed cycle found, not a DAG\n");
}
#endif


void topsort(graph *g){
    int i;

    for(i =1; i<= g->nvertices; i++ ){
        if(!discovered[i]){
            dfs(g,i);
        }
    }
    while(!sorted.empty()){
       std::cout<< sorted.top()<<" ";
       sorted.pop();
    }
}
void find_path(int start, int end, int parent[]){
    
    if((start==end) || (end==-1)) 
       printf("\n=>%d", start);
    else{
        find_path(start,parent[end],parent);
        printf(" %d",end);
    }
}

void dfs(graph *g, int v){
    edgenode *p;
    int y;

    if(finished) {
        return;
    }
    discovered[v]=true;
    process_vertex_early(v);

    p=g->edges[v];

    while(p!=NULL){
        y=p->y;    //y is adjeancy vertex of v

        if(!discovered[y]){
            parent[y]= v;
            process_edge(v,y);
            dfs(g,y);     // v next is y
        }
        else if (((!processed[y]) && (parent[v] != y)) || (g->directed)) {
            process_edge(v,y);
        }
        if(finished){
            return;
        }
        p=p->next;
    }
    process_vertex_late(v);
    processed[v]=true;
}

graph *transpose(graph *g){
    graph *gt;
    int x;
    edgenode *p;

    gt= new graph;

    initialize_graph(gt,true);
    gt->nvertices = g->nvertices;

    for( x=1; x<=g->nvertices; x++){
        p=g->edges[x];
        while(p!=NULL){
            insert_edge(gt,p->y,x,true);
            p=p->next;
        }
    }
    return gt;
}

int main()
{
    graph g;
    
    //read_graph(&g,false);
    initialize_graph(&g,false);
    g.nvertices= 8;
    insert_edge(&g,1,2,false);
    insert_edge(&g,1,8,false);
    insert_edge(&g,1,7,false);
    insert_edge(&g,2,7,false);
    insert_edge(&g,2,5,false);
    insert_edge(&g,2,3,false);
    insert_edge(&g,3,4,false);
    insert_edge(&g,3,5,false);
    insert_edge(&g,4,5,false);
    insert_edge(&g,5,6,false);
    
    initialize_search(&g);
    print_graph(&g);
    //dfs(&g,1);
    //topsort(&g);

    print_graph(transpose(&g));   //reversed edges
    
    //for(int i=1; i<=8; i++)
    //  printf("%d ",parent[i]);

   
    return 0;
}
