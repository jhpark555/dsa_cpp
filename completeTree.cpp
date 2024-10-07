#include <iostream>
#include <vector>
#include <list>

using namespace std;

template <typename E>
class VectorCompleteTree { // left-complete tree interface  
    private: // member data
        vector<E> V; // tree contents
    public: // publicly accessible types
        typedef typename vector<E>::iterator Position; // a position in the tree
    protected: // protected utility functions
        Position pos(int i) // map an index to a position
        { return V.begin() + i; } 
        int idx(const Position& p) const // map a position to an index
        { return p - V.begin(); }

    public: // publicly accessible types
        VectorCompleteTree(): V(1){}
        int size() const { return V.size() - 1; } 
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

template<typename E,typename C>
class HeapPriorityQueue{
    public:
        int size() const {return T.size();}
        bool empty() const {return size()==0;}
        void insert(const E& e);
        const E& min() {return *(T.root());}
        void removeMin();
    private:
        VectorCompleteTree<E> T;
        C isLess;
    typedef typename VectorCompleteTree<E>::Position Position;
};
template<typename E,typename C>
void HeapPriorityQueue<E,C>::insert(const E& e){
    T.addLast(e);
    Position v=T.last();
    while( !T.isRoot(v)){
        Position u= T.parent(v);
        if( !isLess(*v,*u)) break;
        T.swap(v,u);
        v=u;
    }
}
template<typename E,typename C>
void HeapPriorityQueue<E,C>::removeMin(){
    if(size()==1) T.removeLast();
    else{
        Position u=T.root();
        T.swap(u,T.last());
        T.removeLast();
        while( T.hasLeft(u)){
            Position v=T.left();
            if(T.hasRight() && isLess(*(T.right(u)),*v))
              v=T.right(u);
            if( isLess(*v,*u)){
                u=v;
            }
            else break;
              
        }
    }
}

template<typename E,typename C>
class AdaptPriorityQueue{
    protected:
        typedef std::list<E> ElementList;
  
    public:
        class Position{
            private:
                typename ElementList::iterator q;
            public:
                const E& operator*(){ return *q;}
                friend class AdaptPriorityQueue;
        };
    public:
        int size() const;
        bool empty() const;
        const E& min() const;
        Position insert(const E& e);
        void removeMin();
        void remove(const Position& p);
        Position replace(const Position& p,const E& e);
    private:
        ElementList L;
        C isLess;
};
template<typename E,typename C>
typename AdaptPriorityQueue<E,C>::Position 
AdaptPriorityQueue<E,C>::insert(const E& e){
    typename ElementList::iterator p=L.begin();
    while( p!=L.end() && !isLess(e,*p)) ++p;
    L.insert(p,e);
    Position pos;
    pos.q= --p;
    return pos;
}
template<typename E,typename C>
void AdaptPriorityQueue<E,C>::remove(const Position& p){
    L.erase(p,q);
}
template<typename E,typename C>
typename AdaptPriorityQueue<E,C>::Position
AdaptPriorityQueue<E,C>::replace(const Position& p, const E& e){
    L.erase(p,q);
    return insert(e);
}