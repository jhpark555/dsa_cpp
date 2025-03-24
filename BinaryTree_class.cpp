#include <iostream>

using namespace std;

template<typename Comparable>
class BinarySearchTree
{
public:
    BinarySearchTree() { root= nullptr; }
    BinarySearchTree( const BinarySearchTree& rhs)
    { root = clone(rhs.root); }
    BinarySearchTree(BinarySearchTree &&rhs);
    ~BinarySearchTree()
    { makeEmpty(); }

    const Comparable & findMin() const;
    const Comparable & findMax() const;
    bool contains( const Comparable &x) const
    { return contains(x,root); }
    bool isEmpty() const
    {  return root==nullptr; }
    void printTree(ostream& out =cout) const
    {  
        if(isEmpty())
            out<<"Empty tree"<<endl;
        else
            printTree(root,out);
     }

    void makeEmpty()
    { makeEmpty(root); }
    void insert(const Comparable &x)
    { insert(x,root);}
    void insert(Comparable &&x)
    { insert(std::move(x),root); }
    void remove(const Comparable &x)
    { remove(x,root); }

    BinarySearchTree& operator=(const BinarySearchTree &rhs);
    BinarySearchTree& operator=(BinarySearchTree &&rhs);

private:
    struct BinaryNode
    {
        Comparable element;
        BinaryNode *left;
        BinaryNode *right;

        BinaryNode(const Comparable & theElement, BinaryNode *lt, BinaryNode *rt)
        : element{theElement}, left{lt},right{rt} {}
        BinaryNode(Comparable&& theElement,BinaryNode *lt,BinaryNode *rt)
        : element{std::move(theElement)},left{lt},right{rt} {}
    };

    BinaryNode *root;

    void insert(const Comparable &x, BinaryNode * &t)
    {
        if(t==nullptr)
            t= new BinaryNode{x,nullptr,nullptr};
        else if(x<t->element)
            insert(x,t->left);
        else if(x>t->element)
            insert(x,t->right);
        else ;
       
    }

    void insert(Comparable &&x,BinaryNode *&t )
    {    
        if (t == nullptr)
            t = new BinaryNode{std::move(x), nullptr, nullptr};
        else if (x < t->element)
            insert(std::move(x), t->left);
        else if (x > t->element)
            insert(std::move(x), t->right);
        else ;    
    }
    void remove(const Comparable &x, BinaryNode *&t)
    {
        if(t==nullptr)
            return;
        if( x< t->element)
            remove(x,t->left);
        else if( x> t->element)
            remove(x,t->right);
        else if( t->left!=nullptr && t->right !=nullptr)   //2 children to delete
        {
            BinaryNode* temp = findMin(t->right);
            //std::cout<< "@"<<temp->element<<" ";
            t->element= temp->element;
            remove(temp->element,t->right);
           
        }
        else
        {
            BinaryNode *oldNode =t;
            if( t->left!=nullptr)
                t=t->left;
            else 
                t=t->right;
                
            delete oldNode;
           
        }
    }
    BinaryNode *findMin(BinaryNode *t) const
    {
        if(t!=nullptr)
            while(t->left!=nullptr)
                t=t->left;        
        return t;
    }
    BinaryNode *findMax(BinaryNode *t) const
    {
        if(t!=nullptr)
            while(t->right!=nullptr)
                t=t->right;
        return t;
    }
    bool contains(const Comparable &x, BinaryNode *t) const
    {
        if( t==nullptr)
            return false;
        else if(x< t->element)
            return contains(x,t->left);
        else if(t->element<x)
            return contains(x,t->right);
        else 
            return true; //match
    }
    void makeEmpty(BinaryNode* &t)
    {
        if(t!=nullptr)
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        t=nullptr;
    }
    void printTree(BinaryNode *t, ostream& out) const
    {
        if(t!=nullptr)
        {
            printTree(t->left,out);
            out<<t->element<<"->";
            printTree(t->right,out);
        }
    }
    BinaryNode *clone(BinaryNode *t) const
    {
        if(t==nullptr)
            return nullptr;
        else
            return new BinaryNode{t->element,clone(t->left),clone(t->right) };
    }
};

int main()
{
    BinarySearchTree<int> s;

    s.insert(10);
    s.insert(20);
    s.insert(5);
    s.insert(60);
    s.insert(90);
    s.insert(70);
    s.insert(80);
    s.insert(40);
    s.remove(60);   
    s.printTree();
    return 0;
}