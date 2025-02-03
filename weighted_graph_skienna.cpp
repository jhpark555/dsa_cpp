#include <iostream>
#include <stdbool.h>

using namespace std;

#define MAXV 100
#define MAXINT  100000
#define SET_SIZE 100

int parent[MAXV+1];

typedef struct edgenode{
    int y;
    int weight;
    struct edgenode *next;
}edgenode;

typedef struct{
    edgenode *edges[MAXV+1];
    int degree[MAXV+1];
    int nvertices;
    int nedges;
    int directed;
}graph;

typedef struct
{
    int p[SET_SIZE + 1];    /* parent element */
    int size[SET_SIZE + 1]; /* number of elements in subtree i */
    int n;                  /* number of elements in set */
} union_find;

typedef struct{
    int x;
    int y;
    int weight;
}edge_pair;

int prim(graph *g, int start){
    int i;

    edgenode *p;
    bool intree[MAXV+1];
    int distance[MAXV+1];
    int v;     //current
    int w;     //next
    int dist;  //cheapest
    int weight =0; 

    for(i =1; i<=g->nvertices; ++i){
        intree[i]=false;
        distance[i]= MAXINT;
        parent[i]= -1;
    }
    distance[start]= 0;
    v=start;

    while(!intree[v]){
        intree[v]=true;
        if(v !=start){
            printf("edge (%d %d ) in tree ",parent[v],v);
            weight =weight +dist;
            printf(":%d \n",weight);
        }
        p= g->edges[v];
        while(p!=NULL){
            w=p->y;   //next edge
            if((distance[w] > p->weight ) && (!intree[w])) {
                distance[w]= p->weight;
                parent[w]=v;
                printf("#%d %d \n",v,w);
            }
            p=p->next;
        }

        dist = MAXINT;
        for(i=1; i<=g->nvertices; i++){
            if((!intree[i]) && (dist > distance[i])){   //to find minimum edge weight
                dist=distance[i];
                printf("@%d \n",i);
                v=i;
            }
        }
    }
    return (weight);
}

int dijkstra(graph *g, int start){
    int i;
    edgenode *p;
    bool intree[MAXV+1];
    int distance[MAXV+1];
    int v;      //current vertex
    int w;      //next vertex
    int dist;    //cheapest cost
    int weight =0;

    for(i=1; i<=g->nvertices; i++){
        intree[i] = false;
        distance[i]= MAXINT;
        parent[i]=-1;
    }

    distance[start]=0;
    v= start;

    while(!intree[v]){
        intree[v]=true;
        if(v!=start){            
            weight= weight + dist;
           // printf("edge (%d %d) in tree \n", parent[v], v);
        }
        p=g->edges[v];
        while( p!=NULL){
            w=p->y;   //next vertex           
            if (distance[w] > (distance[v] + p->weight))
            {
                distance[w] = distance[v] + p->weight;
                parent[w]=v;   //parent of w is v
                //printf("#%d)\n",distance[v]);
            }            
            p=p->next;
        }
        dist =MAXINT;
        for(i=1; i<=g->nvertices; i++){
            if((!intree[i]) && (dist > distance[i])){
               dist=distance[i];
               //printf("@%d %d \n",dist,i);
               v=i;              // select minimum dist               
            }
        }
    }
    return (weight);

}

void union_find_init(union_find *s, int n){
    int i;

    for(i=1; i<=n ;i++){
        s->p[i]=i;
        s->size[i]=1;
    }
    s->n =n;
}

int find(union_find *s, int x){
    if(s->p[x]==x) return x;   //found
    return find(s,s->p[x]);   //search recursively with parent
}

void union_sets(union_find *s, int s1, int s2){
    int r1, r2;  //root of each sets

    r1=find(s,s1);
    r2=find(s,s2);

    if(r1==r2)  return;  // already same sets

    if(s->size[r1] >=s->size[r2]) {    // merge to r1 ( r1>r2)
        s->size[r1]=s->size[r1]+s->size[r2];
        s->p[r2]=r1;
    }
    else{
        s->size[r2]=s->size[r1]+s->size[r2];
        s->p[r1]=r2;
    }

}

bool same_component(union_find *s, int s1, int s2){
    return (find(s,s1)==find(s,s2));
}

void to_edge_array(graph *g, edge_pair e[])
{
    int i, m;    /* counters */
    edgenode *p; /* temporary pointer */

    m = 0;
    for (i = 1; i <= g->nvertices; i++)
    {
        p = g->edges[i];
        while (p != NULL)
        {
            if (p->y > i)
            {
                e[m].x = i;
                e[m].y = p->y;
                e[m].weight = p->weight;
                m = m + 1;
            }
            p = p->next;
        }
    }
}

int weight_compare(const void *e1,const void  *e2)
{
  edge_pair *_x= (edge_pair*)e1;
  edge_pair *_y= (edge_pair*)e2;

  if(_x->weight < _y->weight) return -1;
  if (_x->weight > _y->weight)  return 1;
  return 0;
}

int kruskal(graph *g){
    int i;
    union_find s;
    edge_pair e[MAXV+1];
    int weight=0;

    union_find_init(&s,g->nvertices);

    to_edge_array(g,e);

    qsort(&e, g->nedges, sizeof(edge_pair), &weight_compare);

    for(i=0;i<(g->nedges) ;i++){
        if(!same_component(&s,e[i].x, e[i].y)){
            printf("edge (%d %d) of weight %d in MST\n", e[i].x,e[i].y,e[i].weight);
            weight = weight + e[i].weight;
            union_sets(&s, e[i].x, e[i].y);
        }
    }
    return (weight);
}

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

void print_graph(graph *g){
    int i;
    
    edgenode *p;
    
    for(i=1; i<= g->nvertices; i++){
        printf("%d: ",i);
        p=g->edges[i];
        while(p !=NULL){
            printf(" %d(%d)", p->y,p->weight);
            p=p->next;
        }
        printf("\n");
    }
}

void insert_edge(graph *g,int x, int y, int weight, bool directed){
    edgenode *p;
   
    p = new edgenode;
    p->weight =weight;
    p->y =y;
    p->next =g->edges[x];
    g->edges[x]=p; 
    g->degree[x]++;   
    
     if(!directed){
        insert_edge(g,y,x, weight, true);
    }
    else{
        g->nedges++;
    }
}

void find_path(int start, int end, int parents[])
{
    if ((start == end) || (end == -1))
    {
        printf("\n@%d", start);
    }
    else
    {
        find_path(start, parents[end], parents);
        printf(" %d", end);
    }
}

int main()
{
    graph g;
    
    initialize_graph(&g,true);

    g.nvertices= 7;
    insert_edge(&g,1,2,5,0);
    insert_edge(&g,1,3,12,0);
    insert_edge(&g,1,4,7,0);
    insert_edge(&g,2,4,9,0);
    insert_edge(&g,2,5,7,0);
    insert_edge(&g,3,4,4,0);
    insert_edge(&g,3,6,7,0);
    insert_edge(&g,4,5,4,0);
    insert_edge(&g,4,6,3,0);
    insert_edge(&g,5,7,5,0);
    insert_edge(&g,5,6,2,0);
    insert_edge(&g,6,7,2,0);

    // print_graph(&g);

    int w = dijkstra(&g,1); //kruskal(&g); // prim(&g, 1);
    printf("w=%d \n",w);

    for (int i = 1; i <= g.nvertices; i++)
    {
        find_path(1, i, parent);
    }
    return (0);
    
}