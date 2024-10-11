#include <iostream>

using namespace std;

template<typename Comparable>
class SplayTree;

template<typename Object>
class Cref
{
    public:
        Cref() : obj(NULL) {}
        explicit Cref(const Object &x): obj(&x) {}

        const Object& get() const{
            return *obj;
        }
        bool isNull() const
        { return obj==NULL ; }

    private:
        const Object *obj;

};


template <class Comparable>
class SplayTree;

template <class Comparable>
class BinaryNode
{
    Comparable  element;
    BinaryNode *left;
    BinaryNode *right;

    BinaryNode( ) : left( NULL ), right( NULL ) { }
    BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt )
      : element( theElement ), left( lt ), right( rt ) { }

    friend class SplayTree<Comparable>;
};


template <class Comparable>
class SplayTree
{
  public:
    SplayTree( );
    SplayTree( const SplayTree & rhs );
    ~SplayTree( );

    Cref<Comparable> findMin( );
    Cref<Comparable> findMax( );
    Cref<Comparable> find( const Comparable & x );
    bool isEmpty( ) const;

    void makeEmpty( );
    void insert( const Comparable & x );
    void remove( const Comparable & x );

    const SplayTree & operator=( const SplayTree & rhs );

  private:
    BinaryNode<Comparable> *root;
    BinaryNode<Comparable> *nullNode;

    Cref<Comparable> elementAt( BinaryNode<Comparable> *t ) const;

    void reclaimMemory( BinaryNode<Comparable> * t ) const;
    void printTree( BinaryNode<Comparable> *t ) const;
    BinaryNode<Comparable> * clone( BinaryNode<Comparable> *t ) const;

        // Tree manipulations
    void rotateWithLeftChild( BinaryNode<Comparable> * & k2 ) const;
    void rotateWithRightChild( BinaryNode<Comparable> * & k1 ) const;
    void splay( const Comparable & x, BinaryNode<Comparable> * & t ) const;
};

// Construct the tree.
template <class Comparable>
SplayTree<Comparable>::SplayTree( )
{
    nullNode = new BinaryNode<Comparable>;
    nullNode->left = nullNode->right = nullNode;
    root = nullNode;
}

// Copy constructor.
template <class Comparable>
SplayTree<Comparable>::SplayTree( const SplayTree<Comparable> & rhs )
{
    nullNode = new BinaryNode<Comparable>;
    nullNode->left = nullNode->right = nullNode;
    root = nullNode;
    *this = rhs;
}

// Destructor.
template <class Comparable>
SplayTree<Comparable>::~SplayTree( )
{
    makeEmpty( );
    delete nullNode;
}

// Insert x into the tree.
// Throws DuplicateItemException if x is already there.
template <class Comparable>
void SplayTree<Comparable>::insert( const Comparable & x )
{
    static BinaryNode<Comparable> *newNode = NULL;

    if( newNode == NULL )
        newNode = new BinaryNode<Comparable>;
    newNode->element = x;

    if( root == nullNode )
    {
        newNode->left = newNode->right = nullNode;
        root = newNode;
    }
    else
    {
        splay( x, root );
        if( x < root->element )
        {
            newNode->left = root->left;
            newNode->right = root;
            root->left = nullNode;
            root = newNode;
        }
        else
        if( root->element < x )
        {
            newNode->right = root->right;
            newNode->left = root;
            root->right = nullNode;
            root = newNode;
        }
       // else
        //    throw DuplicateItemException( );
    }
    newNode = NULL;   // So next insert will call new
}

// Remove x from the tree.
// Throws ItemNotFoundException if x is not in the tree.
template <class Comparable>
void SplayTree<Comparable>::remove( const Comparable & x )
{
    BinaryNode<Comparable> *newTree;

    //if( isEmpty( ) )
    //    throw ItemNotFoundException( );

      // If x is found, it will be at the root
    splay( x, root );
    //if( root->element != x )
    //    throw ItemNotFoundException( );

    if( root->left == nullNode )
        newTree = root->right;
    else
    {
          // Find the maximum in the left subtree
          // Splay it to the root; and then attach right child
        newTree = root->left;
        splay( x, newTree );
        newTree->right = root->right;
    }
    delete root;
    root = newTree;
}

// Internal method to wrap the element field in node t inside a Cref object.
template <class Comparable>
Cref<Comparable> SplayTree<Comparable>::elementAt( BinaryNode<Comparable> *t ) const
{
    if( t == NULL )
        return Cref<Comparable>( );
    else
        return Cref<Comparable>( t->element );
}

// Find the smallest item in the tree.
// Not the most efficient implementation (uses two passes), but has correct
//     amortized behavior.
// A good alternative is to first call find with parameter
//     smaller than any item in the tree, then call findMin.
// Return the smallest item in the tree wrapped in a Cref object.
template <class Comparable>
Cref<Comparable> SplayTree<Comparable>::findMin( )
{
    if( isEmpty( ) )
        return elementAt( NULL );

    BinaryNode<Comparable> *ptr = root;

    while( ptr->left != nullNode )
        ptr = ptr->left;

    splay( ptr->element, root );
    return elementAt( root );
}

// Find the largest item in the tree.
// Not the most efficient implementation (uses two passes), but has correct
//     amortized behavior.
// A good alternative is to first call Find with parameter
//     larger than any item in the tree, then call findMax.
// Return the largest item in the tree wrapped in a Cref object.
template <class Comparable>
Cref<Comparable> SplayTree<Comparable>::findMax( )
{
    if( isEmpty( ) )
        return elementAt( NULL );

    BinaryNode<Comparable> *ptr = root;

    while( ptr->right != nullNode )
        ptr = ptr->right;

    splay( ptr->element, root );
    return elementAt( root );
}

// Find item x in the tree.
// Return the matching item wrapped in a Cref object.
template <class Comparable>
Cref<Comparable> SplayTree<Comparable>::find( const Comparable & x )
{
    splay( x, root );
    if( isEmpty( ) || root->element != x )
        return elementAt( NULL );

    return elementAt( root );
}

// Make the tree logically empty.
template <class Comparable>
void SplayTree<Comparable>::makeEmpty( )
{
    findMax( );        // Splay max item to root
    while( !isEmpty( ) )
        remove( root->element );
}

// Test if the tree is logically empty.
// Return true if empty, false otherwise.
template <class Comparable>
bool SplayTree<Comparable>::isEmpty( ) const
{
    return root == nullNode;
}

// Deep copy.
template <class Comparable>
const SplayTree<Comparable> &
SplayTree<Comparable>::operator=( const SplayTree<Comparable> & rhs )
{
    if( this != &rhs )
    {
        makeEmpty( );
        root = clone( rhs.root );
    }

    return *this;
}

// Internal method to perform a top-down splay.
// The last accessed node becomes the new root.
// x is the target item to splay around.
// t is the root of the subtree to splay.
template <class Comparable>
void SplayTree<Comparable>::splay( const Comparable & x,
                                   BinaryNode<Comparable> * & t ) const
{
    BinaryNode<Comparable> *leftTreeMax, *rightTreeMin;
    static BinaryNode<Comparable> header;

    header.left = header.right = nullNode;
    leftTreeMax = rightTreeMin = &header;

    nullNode->element = x;   // Guarantee a match

    for( ; ; )
        if( x < t->element )
        {
            if( x < t->left->element )
                rotateWithLeftChild( t );
            if( t->left == nullNode )
                break;
              // Link Right
            rightTreeMin->left = t;
            rightTreeMin = t;
            t = t->left;
        }
        else if( t->element < x )
        {
            if( t->right->element < x )
                rotateWithRightChild( t );
            if( t->right == nullNode )
                break;
              // Link Left
            leftTreeMax->right = t;
            leftTreeMax = t;
            t = t->right;
        }
        else
            break;

    leftTreeMax->right = t->left;
    rightTreeMin->left = t->right;
    t->left = header.right;
    t->right = header.left;
}

// Rotate binary tree node with left child.
template <class Comparable>
void SplayTree<Comparable>::rotateWithLeftChild( BinaryNode<Comparable> * & k2 ) const
{
    BinaryNode<Comparable> *k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2 = k1;
}

// Rotate binary tree node with right child.
template <class Comparable>
void SplayTree<Comparable>::rotateWithRightChild( BinaryNode<Comparable> * & k1 ) const
{
    BinaryNode<Comparable> *k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1 = k2;
}

// Internal method to reclaim internal nodes in subtree t.
// WARNING: This is prone to running out of stack space.
template <class Comparable>
void SplayTree<Comparable>::reclaimMemory( BinaryNode<Comparable> * t ) const
{
    if( t != t->left )
    {
        reclaimMemory( t->left );
        reclaimMemory( t->right );
        delete t;
    }
}

// Internal method to clone subtree.
// WARNING: This is prone to running out of stack space.
template <class Comparable>
BinaryNode<Comparable> *
SplayTree<Comparable>::clone( BinaryNode<Comparable> * t ) const
{
    if( t == t->left )  // Cannot test against nullNode!!!
        return nullNode;
    else
        return new BinaryNode<Comparable>( t->element, clone( t->left ), clone( t->right ) );
}


// Test program
int main( )
{
    SplayTree<int> t;
    int NUMS = 10000;
    const int GAP  =   37;
    int i;

    cout << "Checking... (no more output means success)" << endl;

    for( i = GAP; i != 0; i = ( i + GAP ) % NUMS )
        t.insert( i );

    for( i = 1; i < NUMS; i+= 2 )
        t.remove( i );

    if( t.findMin( ).get( ) != 2 || t.findMax( ).get( ) != NUMS - 2 )
        cout << "FindMin or FindMax error!" << endl;

    for( i = 2; i < NUMS; i+=2 )
        if( t.find( i ).get( ) != i )
            cout << "Find error1!" << endl;

    for( i = 1; i < NUMS; i+=2 )
    {
        if( !t.find( i ).isNull( ) )
            cout << "Find error2!" << endl;
    }

    SplayTree<int> t2 = t;

    for( i = 2; i < NUMS; i+=2 )
        if( t2.find( i ).get( ) != i )
            cout << "Find error1!" << endl;

    for( i = 1; i < NUMS; i+=2 )
    {
        if( !t2.find( i ).isNull( ) )
            cout << "Find error2!" << endl;
    }

    return 0;
}