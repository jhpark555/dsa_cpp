#include <iostream>

using namespace std;




template<typename K,typename V>
class Entry
{
    public:
        typedef K Key;
        typedef V Value;
    public:
        Entry(const K &k=K(), const V& v=V())
            : _key(k), _value(v)  {}
        const K& key() const {return _key;}
        const V& value() const { return _value;}
        void setKey(const K&k) { _key=k;}
        void setValue(const V&v) {_value=v;}
    private:
        K _key;
        V _value;
};

template< typename E>
class SearchTree
{
    public:
        typedef typename E::Key K;
        typedef typename E::Value V;
        class Iterator;
    public:
        SearchTree();
        int size() const;
        bool empty() const;
        Iterator find( const K& k);
        Iterator insert(const K& k, const V& v);
        void erase(const Iterator& p);
        Iterator begin();
        Iterator end();
    protected:
        typedef BinaryTree<E> BinaryTree;
        typedef typename BinaryTree::Position TPos;
        TPos root() const;
        TPos finder(const K& k, const TPos& v);
        TPos inserter(const K& k,const V& v);
        TPos eraser(TPos& v);
    private:
        BinaryTree T;
        int n;
    public:
        class Iterator 
        { // an iterator/position
        private:
            TPos v; // which entry
        public:
            Iterator(const TPos& vv) : v(vv) { } // constructor
            const E& operator*() const { return *v; } // get entry (read only)
            E& operator*() { return *v; } // get entry (read/write)
            bool operator==(const Iterator& p) const // are iterators equal?
            { return v == p.v; } Iterator& operator++(); // inorder successor
            friend class SearchTree; // give search tree access
        };

};