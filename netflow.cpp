#include <iostream>
#include <stdbool.h>
#include <queue>

using namespace std;

#define MAXV 100     /* maximum number of vertices */
#define MAXDEGREE 50 /* maximum outdegree of a vertex */

bool processed[MAXV + 1];  /* which vertices have been processed */
bool discovered[MAXV + 1]; /* which vertices have been found */
int parent[MAXV + 1];      /* discovery relation */

bool finished = false; /* if true, cut off search immediately */


typedef struct edgenode
{
    int v;                 /* neighboring vertex */
    int capacity;          /* capacity of edge */
    int flow;              /* flow through edge */
    int residual;          /* residual capacity of edge */
    struct edgenode *next; /* next edge in list */
} edgenode;

typedef struct
{
    edgenode *edges[MAXV + 1]; /* adjacency info */
    int degree[MAXV + 1];      /* outdegree of each vertex */
    int nvertices;             /* number of vertices in the graph */
    int nedges;                /* number of edges in the graph */
} flow_graph;

void initialize_graph(flow_graph *g)
{          /* graph to initialize */
    int i; /* counter */

    g->nvertices = 0;
    g->nedges = 0;

    for (i = 0; i < MAXV; i++)
    {
        g->degree[i] = 0;
    }

    for (i = 0; i < MAXV; i++)
    {
        g->edges[i] = NULL;
    }
}

void insert_edge(flow_graph *g, int x, int y, int w, bool directed)
{
    edgenode *p; /* temporary pointer */

    p = new edgenode ;  /* allocate storage for edgenode */

    p->v = y;
    p->capacity = w;
    p->flow = 0;
    p->residual = w;
    p->next = g->edges[x];

    g->edges[x] = p; /* insert at head of list */
    g->degree[x]++;

    if (directed == false)
    {
        insert_edge(g, y, x, w,true);
    }
    else
    {
        g->nedges++;
    }
}

edgenode *find_edge(flow_graph *g, int x, int y){
    edgenode *p =g->edges[x];

    while(p!=NULL){
        if(p->v ==y)
            return p;
        p=p->next;
    }
    return NULL;
}

void add_residual_edges(flow_graph *g){
    int i,j;
    edgenode *p;
    for(i=1; i<=g->nvertices; i++){
        p=g->edges[i];
        while (p!=NULL){
            if(find_edge(g,p->v,i)==NULL){
                insert_edge(g,p->v,i,0,true);
            }
            p=p->next;
        }
    }
}

void print_flow_graph(flow_graph *g){
    int i;
    edgenode *p;

    for(i=1; i<=g->nvertices; i++){
        printf("%d:",i);
        p=g->edges[i];
        while(p!=NULL){
            printf(" %d(%d,%d,%d)", p->v, p->capacity, p->flow, p->residual);
            p=p->next;
        }
        printf("\n");
    }
}


void initialize_search(flow_graph *g)
{
    int i;

    for (i = 0; i < g->nvertices; i++)
    {
        processed[i] = false;
        discovered[i] = false;
        parent[i] = -1;
    }
}

void process_vertex_early(int v)
{ /* vertex to process */
}

void process_vertex_late(int v)
{ /* vertex to process */
}

void process_edge(int x, int y)
{ /* edge to process */
}

void bfs(flow_graph *g, int start)
{
    queue<int> q;
    int v;
    int y;

    edgenode *p;
    q.push(start);
    discovered[start] = true;

    while (!q.empty())
    {
        v = q.front();
        q.pop();
        process_vertex_early(v);
        processed[v] = true;
        p = g->edges[v];
        while (p != NULL)
        {
            y = p->v;
            if ((!processed[y]) /*|| (g->directed)*/)
            {
                process_edge(v, y);
            }
            if (!discovered[y])
            {
                q.push(y);
                discovered[y] = true;
                parent[y] = v;
                // printf("%d ->",v);
            }
            p = p->next;
        }
        process_vertex_late(v);
    }
}

void find_path(int start, int end, int parents[]){
    if((start ==end) || (end==-1))
        printf("%d ",start);
    else{
        find_path(start,parent[end],parents);
        printf(" %d",end);
    }
}

int path_volume(flow_graph *g, int start,int end){
    edgenode *e;  //edge in question
    
    if(parent[end]==-1)
        return 0;
    
    e=find_edge(g,parent[end],end);

    if(start==parent[end])
        return e->residual;
    else{
        return min(path_volume(g, start,parent[end]),e->residual);
    }
}

void augment_path(flow_graph *g, int start, int end, int volume){
    edgenode *e;  //edge in question

    if(start==end) return ;

    e= find_edge(g,parent[end],end);
    e->flow +=volume;
    e->residual -=volume;

    e=find_edge(g,end,parent[end]);
    e->residual +=volume;

    augment_path(g,start, parent[end], volume);
}

void netflow(flow_graph *g, int source, int sink){
    int volume; /* weight of the augmenting path */

    add_residual_edges(g);

    initialize_search(g);
    bfs(g,source);

    volume = path_volume(g,source, sink);

    while(volume >0 ){
        augment_path(g,source, sink, volume);
        initialize_search(g);
        bfs(g, source);
        volume = path_volume(g,source, sink);
    }
}

int main()
{
    flow_graph g;
    

    initialize_graph(&g);

    g.nvertices = 7;
    insert_edge(&g, 1, 2, 5, 0);
    insert_edge(&g, 1, 3, 12, 0);
    //insert_edge(&g, 1, 4, 7, 0);
    insert_edge(&g, 2, 4, 9, 0);
    insert_edge(&g, 2, 5, 7, 0);
    insert_edge(&g, 3, 4, 4, 0);
    insert_edge(&g, 3, 6, 7, 0);
    insert_edge(&g, 4, 5, 3, 0);
    insert_edge(&g, 4, 6, 3, 0);
    insert_edge(&g, 5, 7, 5, 0);
    //insert_edge(&g, 5, 6, 2, 0);
    insert_edge(&g, 6, 7, 2, 0);


    netflow(&g,1,7);

    print_flow_graph(&g);

    int flow=0;
    edgenode *p=g.edges[1];
    while(p!=NULL){
        flow +=p->flow;
        p=p->next;
    }

    printf("total flow =%d \n",flow);

    return 0;
}