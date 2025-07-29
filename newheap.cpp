#include <iostream>

using namespace std;



void max_heap_insert(int heap[],int *num_heap,int cost)
{
    int i;
    int temp;
    (*num_heap)++;
    heap[*num_heap]= cost;
    i = *num_heap;
    while(i >1 && heap[i] > heap[i/2]){
        temp=heap[i];
        heap[i]=heap[i/2];
        heap[i/2]=temp;
        i= i/2;
    }
}

int max_heap_extract(int heap[],int *num_heap){
    int remove,temp;
    int i, child;
    remove=heap[1];
    heap[1]=heap[*num_heap];
    (*num_heap)--;
    i=1;
    while(i*2<=*num_heap){
        child = i*2;
        if(child< *num_heap && heap[child+1] > heap[child])
           child++;
        if(heap[child] > heap[i]) {
            temp=heap[i];
            heap[i]=heap[child];
            heap[child]=temp;
            i=child;
        }
        else  break;
    }
    return remove;
}

void min_heap_insert(int heap[],int *num_heap,int cost)
{
    int i;
    int temp;
    (*num_heap)++;
    heap[*num_heap]= cost;
    i = *num_heap;
    while(i >1 && heap[i] < heap[i/2]){
        temp=heap[i];
        heap[i]=heap[i/2];
        heap[i/2]=temp;
        i= i/2;
    }
}

int min_heap_extract(int heap[],int *num_heap){
    int remove,temp;
    int i, child;
    remove=heap[1];
    heap[1]=heap[*num_heap];
    (*num_heap)--;
    i=1;
    while(i*2<=*num_heap){
        child = i*2;
        if(child< *num_heap && heap[child+1] < heap[child])
           child++;
        if(heap[child] < heap[i]) {
            temp=heap[i];
            heap[i]=heap[child];
            heap[child]=temp;
            i=child;
        }
        else  break;
    }
    return remove;
}

int main(int argc, char *argv[])
{

    int arr[]={10,30,3,5,8,91,22,36,89,95,54,28,67,1};
    int size= sizeof(arr)/sizeof(arr[0]);
    int heap[size];
    int num_heap=0;

    for(int i=0 ; i< size ;i ++)
        max_heap_insert(heap,&num_heap,arr[i]);
    
    int ret = max_heap_extract(heap,&num_heap);
    printf("Max element= %d \n",ret);

    num_heap=0;

    for(int i=0 ; i< size ;i ++)
        min_heap_insert(heap,&num_heap,arr[i]);
    
     ret = min_heap_extract(heap,&num_heap);
    printf("Min element= %d \n",ret);
}