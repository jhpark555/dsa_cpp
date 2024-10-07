#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

template<typename E>
class HeapPriorityQueue;


template <typename E>
class VectorCompleteTree
{ 
    private:
        vector<E> V;
    public:
        typedef typename vector<E>::iterator Position;
        Position pos(int i)
        { return V.begin()+i; }
        int idx(const Position &p) const
        { return p-V.begin(); }
    public:
        VectorCompleteTree() : V(1) {} // constructor
        int size() const { return V.size()-1; } 
        Position left(const Position& p) { return pos(2*idx(p)); } 
        Position right(const Position& p) { return pos(2*idx(p) + 1); } 
        Position parent(const Position& p) { return pos(idx(p)/2); }
        bool hasLeft(const Position& p) const { return 2*idx(p) <= size(); }
        bool hasRight(const Position& p) const { return 2*idx(p) + 1 <= size(); } 
        bool isRoot(const Position& p) const { return idx(p) == 1; } 
        Position root() { return pos(1); }
        Position last() { return pos(size()); } 
        void addLast(const E& e) { V.push_back(e); } 
        void removeLast() { V.pop_back(); } 
        void swap(const Position& p, const Position& q)
        { E e = *q; *q = *p; *p = e; }

};

template<typename E>
class HeapPriorityQueue
{
    public:        
        int size() const
        { return T.size(); }
        bool empty() const
        { return size() ==0; }
        void insert(const E& e)
        {
            T.addLast(e);    //push back
            Position v= T.last();   //last position
            while(!T.isRoot(v))    // is 1 position?
            {
                Position u= T.parent(v);
                if(!isless(*v,*u))  break; // parent>child
                T.swap(u,v);    //swap parent, child
                v=u;     //adbance v to parent position
            }
        }
        const E& min()
        { return *(T.root()); }

        void removeMin()
        {
            if(size()==1) T.removeLast();
            else{
                Position u=T.root();
                T.swap(u,T.last());
                T.removeLast();
                while(T.hasLeft(u))
                {
                    Position v=T.left(u);
                    if(T.hasLeft(u) && isless(*(T.right(u))),*v) //right < left
                        v=T.right(u);
                    if(isless(*v,*u)){
                        T.swap(u,v);
                        u=v;    // advance to down!! 
                    }
                    else break;
                }
            }
           
        }
        void print()
        {
            Position u=T.root();
            while(u!=T.last()){
               cout<<*u <<endl;
               u++;
            } 
             //cout<<*u <<endl;
        }
        void buildHeap()
        {
            cout<< T.size()/2 ;
            for(int i= T.size()/2; i>0; --i)
                removeMin();
        }
    private:
        VectorCompleteTree<E> T;
        typedef typename VectorCompleteTree<E>::Position Position;
};

int main()
{
    HeapPriorityQueue<int> h;
    int arr[]={3,2,6,4,5,8};
    for(int i=0;i< 6; i++)
        h.insert(arr[i]);

    //h.buildHeap();
    h.print();
    return 0;
}