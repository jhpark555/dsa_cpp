#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <queue>

using namespace std;

#define MAXV 100
#define UNCOLORED (-1)
#define WHITE (1)
#define BLACK  (0)

void find_path(int start, int end, int parent[]);

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

bool processed[MAXV+1];
bool discovered[MAXV+1];
int parent[MAXV+1];
bool finished=false;

void initialize_search(graph *g){
    int i;
    
    for(i=0; i<g->nvertices; i++){
        processed[i]=false;
        discovered[i]=false;
        parent[i]=-1;
    }

}

void process_vertex_early(int v) {
   printf("processed vertex %d\n", v);
}
void process_edge(int x, int y) {
   printf("processed edge (%d,%d)\n", x, y);
   if(parent[y]!=x){
    printf("Cycle from %d to %d \n",y,x);
    find_path(y,x,parent);
    finished = true;
   }
}
void process_vertex_late(int v) {
    
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
    
    //print_graph(&g);
    dfs(&g,1);
    
    //for(int i=1; i<=8; i++)
    //  printf("%d ",parent[i]);

   
    return 0;
}
