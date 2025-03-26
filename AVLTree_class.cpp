#include <iostream>

using namespace std;

template<typename Comparable>
class BinarySearchTree
{
public:
    BinarySearchTree( ) { root= nullptr; }
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
    struct AvlNode
    {
        Comparable element;
        AvlNode *left;
        AvlNode *right;
        int height;

        AvlNode(const Comparable & ele, AvlNode *lt, AvlNode *rt, int h=0)
        : element{ele}, left{lt},right{rt}, height{h} {}
        AvlNode(Comparable&& ele,AvlNode *lt,AvlNode *rt, int h=0)
        : element{std::move(ele)},left{lt},right{rt} ,height{h} {}
    };

    AvlNode *root;

    int height(AvlNode *t) const
    {
        return t==nullptr? -1: t->height;
       //return t==nullptr? -1: 1+ max(height(t->left),height(t->right));
    }

    void insert(const Comparable &x, AvlNode * &t)
    {
        if(t==nullptr)
            t= new AvlNode{x,nullptr,nullptr};
        else if(x<t->element)
            insert(x,t->left);
        else if(x>t->element)
            insert(x,t->right);

        balance(t);
       
    }

    void insert(Comparable &&x,AvlNode *&t )
    {    
        if (t == nullptr)
            t = new AvlNode{std::move(x), nullptr, nullptr};
        else if (x < t->element)
            insert(std::move(x), t->left);
        else if (x > t->element)
            insert(std::move(x), t->right);
        
        balance(t);
    }


    static const int ALLOWED_IMBALANCE =1;

    void balance(AvlNode *&t)
    {
        if(t ==nullptr) 
            return;

        if(height(t->left)-height(t->right) > ALLOWED_IMBALANCE )    //2
            if( height(t->left->left) >=height(t->left->right)) 
                rotateWithLeftChild(t);
            else 
                doubleWithLeftChild(t);
        else
        if(height(t->right) - height(t->left) > ALLOWED_IMBALANCE )  //-2
            if(height(t->right->right)>= height(t->right->left))
                rotateWithRightChild(t);
            else 
                doubleWithRightChild(t);

        t->height = max( height(t->left), height(t->right)) +1;
        //std::cout<<t->height<<" ";
    }

    void rotateWithLeftChild(AvlNode *&k2)
    {
        AvlNode *k1 =k2->left;
        k2->left= k1->right;
        k1->right= k2;
        k2->height =max( height(k2->left), height(k2->right)) +1;
        k1->height =max( height(k1->left), height(k1->right)) +1;
        k2= k1;     //new root
    }
    void rotateWithRightChild(AvlNode *&k1)
    {
        AvlNode *k2=k1->right;
        k1->right=k2->left;
        k2->left=k1;
        k1->height= max(height(k1->left), height(k1->right)) +1;
        k2->height = max(height(k2->left), height(k2->left)) +1;
        k1= k2;
    }
    void doubleWithLeftChild(AvlNode *&k3)
    {
        rotateWithRightChild(k3->left);
        rotateWithLeftChild(k3);
    }
    void doubleWithRightChild(AvlNode *&k3)
    {
        rotateWithLeftChild(k3->right);
        rotateWithRightChild(k3);
    }

    void remove(const Comparable &x, AvlNode *&t)
    {
        
        if(t==nullptr)
            return;

        if( x< t->element)
            remove(x,t->left);
        else if( x> t->element)
            remove(x,t->right);
        else if( t->left!=nullptr && t->right !=nullptr)   //2 children to delete
        {
            AvlNode* temp = findMin(t->right);
            //std::cout<< "#"<<temp->element<<" ";
            t->element= temp->element;
            remove(temp->element,t->right);
           
        }
        else
        {
            AvlNode *oldNode =t;

            if( t->left!=nullptr)
                t=t->left;
            else
                t=t->right;

            delete oldNode;
            //std::cout << "@" << oldNode->element << " ";
        }

        balance(t);
    }
    AvlNode *findMin(AvlNode *t) const
    {
        if(t!=nullptr)
            while(t->left!=nullptr)
                t=t->left;        
        return t;
    }
    AvlNode *findMax(AvlNode *t) const
    {
        if(t!=nullptr)
            while(t->right!=nullptr)
                t=t->right;
        return t;
    }
    bool contains(const Comparable &x, AvlNode *t) const
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
    void makeEmpty(AvlNode* &t)
    {
        if(t!=nullptr)
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        t=nullptr;
    }
    void printTree(AvlNode *t, ostream& out) const
    {
        if(t!=nullptr)
        {
            printTree(t->left,out);
            out<<t->element<<"->";
            printTree(t->right,out);
        }
    }
    AvlNode *clone(AvlNode *t) const
    {
        if(t==nullptr)
            return nullptr;
        else
            return new AvlNode{t->element,clone(t->left),clone(t->right) };
    }
};

int main()
{
    BinarySearchTree<int> s;

    s.insert(5);
    s.insert(2);
    s.insert(1);
    s.insert(4);
    s.insert(7);
    s.insert(3);
    s.insert(6);
    s.insert(8);
    s.insert(9);
    s.insert(10);
    s.insert(13);
    s.insert(11);
    s.insert(12);
    s.insert(15);
    s.insert(14);
    s.insert(16);
    s.remove(11);
    s.printTree();
    return 0;
}