#include <iostream>
#include <queue>
#include <stack>

using namespace std;

template<typename T>
class Stack: public stack<T> 
{

};

template<typename T>
class Queue: public queue<T>
{
    public:
        T dequeue(){
            T tmp= queue<T>::front();
            queue<T>::pop();
            return tmp;
        }
        void enqueue(const T& el){
            push(el);
        }
};

template<typename T>
class BSTNode
{
    public:
        BSTNode(){
            left= right =NULL;
        }
        BSTNode(const T& e, BSTNode<T> *l=NULL, BSTNode<T> *r=NULL)
        : el(e), left(l), right(r)  {}

        T el;
        BSTNode<T> *left, *right;
};

template<typename T>
class BST
{
    public:
        BST() : root(NULL) {}
        ~BST() { clear(); }
        void clear(){
            clear (root); root=NULL;
        }
        bool isEmpty() const{
            return root==NULL;
        }
        void preorder(){
            preorder(root);
        }
        void inorder(){
            inorder(root);
        }
        void postorder() {
            postorder(root); 
        }
        T* search(const T& el) const {
            return search(root,el); 
        }
        void breadthFirst(); 
        void iterativePreorder(); 
        void iterativeInorder(); 
        void iterativePostorder(); 
        void MorrisInorder(); 
        void insert(const T&); 
        void deleteByMerging(BSTNode<T>*&); 
        void findAndDeleteByMerging(const T&); 
        void deleteByCopying(BSTNode<T>*&); 
        void balance(T*,int,int); 
        

    protected:
        BSTNode<T>* root;
        void clear(BSTNode<T>*);
        T* search(BSTNode<T>*, const T&) const; 
        void preorder(BSTNode<T>*); 
        void inorder(BSTNode<T>*); 
        void postorder(BSTNode<T>*); 
        virtual void visit(BSTNode<T>* p) {
            cout << p->el << ' ';
        }
};

template<typename T>
T* BST<T>::search(BSTNode<T> *p, const T& el) const 
{
    while(p != NULL){
        if(el ==p->el) return &p->el;
        else if (el <p->el)  p=p->left;
        else p=p->right;
    }
    return NULL;
}
template<typename T>
void BST<T>::clear(BSTNode<T>* p)
{
    delete(p);
}
template<typename T>
void BST<T>::breadthFirst()
{
    Queue<BSTNode<T>*> queue;
    BSTNode<T> *p=root;
    if(p!=NULL){
        queue.enqueue(p);
        while(!queue.empty()){
            p=queue.dequeue();
            visot(p);
            if(p->left) queue.enqueue(p->left);
            if(p->right) queue.enqueue(p->right);
        }
    }

}

template<typename T>
void BST<T>::inorder(BSTNode<T>* p)
{
    if(p!=NULL){
        inorder(p->left);
        visit(p);
        inorder(p->right);
    }
}
template<class T>
void BST<T>::preorder(BSTNode<T> *p) 
{
    if (p != 0) {
        visit(p);
        preorder(p->left);
        preorder(p->right);
    }
}

template<class T>
void BST<T>::postorder(BSTNode<T>* p) 
{
    if (p != 0) {
        postorder(p->left);
        postorder(p->right);
        visit(p);
    }
}

template<typename T>
void BST<T>::iterativePreorder()
{
    Stack<BSTNode<T>*> travStack;
    BSTNode<T> *p=root;

    if(p!=NULL){
        travStack.push(p);

        while(!travStack.empty()){
            p.travStack.pop();
            visit(p);
            if(p->right) travStack.push(p->right);
            if(p->left)  travStack.push(p->left);
        }

    }
}

template<typename T>
void BST<T>::iterativePostorder()
{
    Stack<BSTNode<T>*> travStack;
    BSTNode<T> *p =root, *q =root;

    while(p!=NULL){
        for(;p->left!=NULL; p=p->left)
            travStack.push(p);
        
        while(p->right ==NULL || p->right ==q){
            visit(p);
            q=p;
            if (travStack.empty()) return;
            p=travStack.pop();
        }
        travStack.push(p);
        p=p->right;
    }

}
template<typename T>
void BST<T>::iterativeInorder() 
{
    Stack<BSTNode<T>*> travStack;
    BSTNode<T> *p = root;
    while (p != NULL) {
        while (p != NULL) { // stack the right child (if any)
            if (p->right) // and the node itself when going
                travStack.push(p->right); // to the left;
            travStack.push(p);
            p = p->left;
        }
        p = travStack.pop(); // pop a node with no left child
        while (!travStack.empty() && p->right == 0) { // visit it
            visit(p); // and all nodes with no right
            p = travStack.pop(); // child;
        }
        visit(p); // visit also the first node with
        if (!travStack.empty()) // a right child (if any);
            p = travStack.pop();
        else p = 0;
    }
}

template<typename T>
void BST<T>::insert(const T& el)
{
    BSTNode<T> *p=root, *prev=NULL;
    while(p!=NULL){
        prev=p;
        if(el<p->el)
            p=p->left;
        else    
            p=p->right;
    }
    if(root==NULL)  
        root= new BSTNode<T> (el);
    else if(el< prev->el)
        prev->left=new BSTNode<T>(el);
    else 
        prev->right=new BSTNode<T>(el);
}
template<typename T>
void BST<T>::deleteByMerging(BSTNode<T>* & node)
{
    BSTNode<T> *tmp= node;

    if(node !=NULL){
        if(node->right==NULL)
            node=node->left;
        else if(node->left==NULL)
            node=node->right;
        else{
            tmp=node->left;
            while(tmp->right!=NULL)
                tmp=tmp->right;
            tmp->right=node->right;

            tmp=node;
            node=node->left;
        }
        delete tmp;
    }
}
template<typename T>
void BST<T>::findAndDeleteByMerging(const T& el)
{
    BSTNode<T> *node =root, *prev=NULL;

    while(node !=NULL){
        if(node->el==el)
            break;
        prev=node;
        if(el<node->el)
            node=node->left;
        else if(el> node->el)
            node=node->right;
    }
    if( node!=NULL && node->el ==el)
        if(node ==root)
            deleteByMerging(root);
        else if(prev->left==node)
            deleteByMerging(prev->left);
        else deleteByMerging(prev->right);
    else if (root!=NULL)
       cout << "element" << el << "is not in the tree\n";
    else  cout << "the tree is empty\n";

}

int main()
{
    BST<int> T;

    T.insert(15);
    T.insert(4);
    T.insert(20);
    T.insert(1);
    T.insert(5);
    T.insert(16);
    T.insert(25);

    T.findAndDeleteByMerging(15);
    T.inorder();
    cout<<endl;
    T.preorder();
    return 0;
}