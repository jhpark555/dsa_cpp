#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <queue>

using namespace std;

#define MAXV 100
#define UNCOLORED (-1)
#define WHITE (1)
#define BLACK  (0)


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


void read_graph(graph *g, bool directed){
    int i;
    int m;   //number of edges
    int x,y; //vertices in edge(x,y)
    
    initialize_graph(g,directed);
    printf("nvertices , num of edges\n");
    scanf("%d %d",&(g->nvertices), &m);
    
    printf("vertices in edges\n");
    for(i=1; i<=m; i++){
        scanf("%d %d",&x,&y);
        insert_edge(g,x,y,directed);
    }
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
int color[MAXV+1];
bool bipartite;

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
}
void process_vertex_late(int v) {
    
}
int complement(int color) {
    if (color == WHITE) {
        return(BLACK);
    }
    if (color == BLACK) {
        return(WHITE);
    }
    return(UNCOLORED);
}

void process_edgec(int x, int y){
    if(color[x] == color[y]) {
        bipartite =false;
        printf("Warning : notbipartite, due to (%d %d) \n",x,y);
    }
    color[y]= complement(color[x]);
}

void find_path(int start, int end, int parent[]){
    
    if((start==end) || (end==-1)) 
       printf("\n=>%d", start);
    else{
        find_path(start,parent[end],parent);
        printf(" %d",end);
    }
}
void bfs(graph *g, int start){
    queue<int> q;
    int v;
    int y;
    
    edgenode *p;
    q.push(start);
    discovered[start]=true;
    
    while(!q.empty()){
        v= q.front(); q.pop();
        process_vertex_early(v);
        processed[v]=true;
        p= g->edges[v];
        while(p!=NULL){
            y=p->y;
            if((!processed[y]) || (g->directed)) {
                process_edge(v,y);
            }
            if(!discovered[y]){
                q.push(y);
                discovered[y]=true;
                parent[y]=v;
               // printf("%d ->",v);
            }
            p=p->next;
        }
        process_vertex_late(v);
    }
}

void connected_component(graph *g){
    int c;
    int i;
    
   
    c=0;
    
    for(i=1; i< g->nvertices; i++){
        if(!discovered[i]){
            c=c+1;
            printf("\nComponent %d:",c);
            bfs(g,i);
            printf("\n");
        }
    }
}


void twocolor(graph *g){
    int i;
    
    for(i=1; i<= g->nvertices; i++){
        color[i]=UNCOLORED;
    }
    
    bipartite = true;
    initialize_search(g);
    
    for(i =1; i<=g->nvertices ; i++ ){
        if(!discovered[i]){
            color[i]=WHITE;
            bfs(g,i);
        }
    }
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
    
    bfs(&g,1);
    
    //for(int i=1; i<=8; i++)
    //  printf("%d ",parent[i]);

    find_path(1,6,parent);
   
    //initialize_search(&g);
    
    //connected_component(&g);
    //twocolor(&g);
    return 0;
}