#include <iostream>
#include <vector>

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
