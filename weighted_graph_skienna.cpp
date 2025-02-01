#include <iostream>
#include <stdbool.h>

using namespace std;

#define MAXV 100
#define MAXINT  100000

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
            printf(" %d", p->y);
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

int main()
{
    graph g;
    
    initialize_graph(&g,true);

    g.nvertices= 8;
    insert_edge(&g,1,2,2,0);
    insert_edge(&g,1,8,4,0);
    insert_edge(&g,1,7,5,0);
    insert_edge(&g,2,7,6,0);
    insert_edge(&g,2,5,7,0);
    insert_edge(&g,2,3,8,0);
    insert_edge(&g,3,4,9,0);
    insert_edge(&g,3,5,1,0);
    insert_edge(&g,4,5,10,0);
    insert_edge(&g,5,6,11,0);
    
    print_graph(&g);

    int w= prim(&g,1);
    printf("w=%d \n",w);

    return (0);
    
}