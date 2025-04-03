#include <iostream>

using namespace std;

template<typename Comparable>
class LeftistHeap
{
public:
    LeftistHeap() { root= nullptr; }
    LeftistHeap(const LeftistHeap &rhs)
    {
        root=nullptr;
        *this =rhs;
    }
    LeftistHeap(LeftistHeap &&rhs)
    {
        root=nullptr;
        *this = std::move(rhs);
    }

    ~LeftistHeap() { makeEmpty(); }

    LeftistHeap & operator=(const LeftistHeap &rhs)
    {
        if(this != &rhs)
        {
            makeEmpty();
            root= clone(rhs.root);
        }
        return *this;
    }
    //LeftistHeap & operator=(LeftistHeap &&rhs);

    bool isEmpty() const
    {
        return root==nullptr;
    }
    const Comparable &findMin() const
    {
        return root->element;
    }

    void insert(const Comparable &x)
    {
        root= merge(new LeftistNode{x}, root);
    }
    void insert(Comparable &&x)
    {
        root = merge(new LeftistNode{std::move(x)}, root);
    }
    void deleteMin()
    {
        if(isEmpty())
            return;
        LeftistNode *oldRoot=root;
        root= merge(root->left, root->right);
       // cout<<"Min:"<<oldRoot->element;
        delete oldRoot;
    }
    void deleteMin(Comparable & minItem)
    {
        minItem =findMin();
        deleteMin();
    }
    void makeEmpty()
    {
        reclaimMemory(root);
        root=nullptr;
    }
    void merge( LeftistHeap &rhs)
    {
        if(this == &rhs)
            return;

        root= merge(root, rhs.root);
        rhs.root=nullptr;
    }
private:
    struct LeftistNode
    {
        Comparable element;
        LeftistNode *left;
        LeftistNode *right;
        int npl;

        LeftistNode(const Comparable &e, LeftistNode *lt=nullptr,
        LeftistNode *rt=nullptr, int np=0)
        : element{e}, left{lt}, right{rt}, npl{np} {}

        LeftistNode(Comparable &&e, LeftistNode *lt=nullptr,
        LeftistNode *rt=nullptr, int np=0)
        : element{ std::move(e) }, left{lt}, right{rt}, npl{np} {}

    };
    LeftistNode *root;

    LeftistNode *merge(LeftistNode *h1, LeftistNode *h2)
    {
        if(h1==nullptr)
            return h2;
        if(h2==nullptr)
            return h1;
        if(h1->element < h2->element)
            return merge1(h1,h2);
        else   
            return merge1(h2,h1);
    }
    LeftistNode *merge1(LeftistNode *h1, LeftistNode *h2)
    {
        if(h1->left==nullptr)
            h1->left = h2;
        else
        {
            h1->right =merge( h1->right,h2);
            if( h1->left->npl < h1->right->npl )
                swapChildren(h1);
            h1->npl = h1->right->npl +1;
        }
        return h1;
    }

    void swapChildren(LeftistNode *t)
    {
        swap(t->left,t->right);
        //LeftistNode *tmp=t->left;
        //t->left=t->right;
        //t->right= tmp;
    }
    LeftistNode *clone(LeftistNode *t) const
    {
        if(t==nullptr)
            return nullptr;
        else
        {
            return new LeftistNode(t->element,clone(t->left),clone(t->right),t->npl);
        }
    }
    
    void reclaimMemory(LeftistNode *t)
    {
        if(t!=nullptr)
        {
            reclaimMemory(t->left);
            reclaimMemory(t->right);
            delete t;
        }
    }

};

int main()
{
    LeftistHeap<int> h;
    LeftistHeap<int> h1;
    LeftistHeap<int> h2;
    int x;

    int arr[]={1,5,7,10,15};
    int arr1[]={22,75};
  
    for(int i=0; i< 5 ; i++)
      h.insert(arr[i]);
    for (int i = 0; i < 2; i++)
      h1.insert(arr1[i]);

    h.deleteMin(x);
    cout<<x <<" \n";
    h1.deleteMin(x);
    cout << x << " \n";

    h.merge(h1);
    h2=h;
    h2.deleteMin(x);
    cout << x << " ";
    return 0;
}