#include <iostream>
#include <queue>
#include <stack>
#include <iterator>

using namespace std;


template<typename T>
class Queue: public queue<T>{
public:
    T dequeue(){
        T tmp= queue<T>::front();
        queue<T>::pop();
        return tmp;
    }
    void enqueue(const int &el){
        queue<T>::push(el);
    }
    
};

class Node{
public:
    Node() {left=right=NULL;}
    Node(const int &e, Node *l =0, Node *r=0){
        el=e; left=l, right=r; successor=0;
    }
    int el;
    Node *left, *right;
    unsigned int successor:1;
};

void bfs_levelorder(Node *root){
    
    //stack<Node*> q;
    Queue<Node *> q;
    Node *p= root;
    
    if(p!=NULL){
        
        q.push(p);
        
        while(!q.empty()){
           // p=q.top();// stack
            p=q.front();
            q.pop();
            std::cout<<p->el <<" ";
            
            if(p->left!=0) q.push(p->left);
            if(p->right!=0) q.push(p->right);
        }
    }
}

void bfs_preorder(Node *root){
    stack<Node *> s;
    Node *p=root;

    if(p!=0){
        s.push(p);
        while( !s.empty()){
            p=s.top(); s.pop();
            std::cout<<p->el<<" ";
            if(p->right)
                s.push(p->right);
            if(p->left)
                s.push(p->left);
        }
    }
}

void bfs_postorder(Node*root){
    stack<Node *> s;
    Node * p=root, *q=root;

    while(p!=0){
        for(; p->left!=0; p=p->left)
            s.push(p);
        //while(!s.empty()){
        //    Node *r= s.top();
        //    std::cout<<r->el<<" ";
        //    s.pop();
        //}
        while( p->right ==0 || p->right==q) {
            std::cout<<p->el<<" ";
            q=p;
            if(s.empty())  return;
            p= s.top(); s.pop();
        }
        s.push(p);
        p=p->right;
    }

}

void bfs_inorder(Node *root){
    stack<Node *> s;
    Node *p =root;
    while(p!=0){
        while(p!=0){
            if(p->right)
                s.push(p->right);
            s.push(p);
            p=p->left;
        }
        //while(!s.empty()){
        //    Node*r =s.top();
        //    s.pop();
        //    std::cout<<r->el<<" ";
        //}


        p=s.top(); s.pop();
        while(!s.empty() && p->right ==0){
            std::cout<<p->el<<" ";
            p=s.top(); s.pop();
        }
        std::cout<<"@"<<p->el<<" ";
        if(!s.empty()){
            p=s.top(); s.pop();
        }
        else p=0;

    }

}

void thread_inorder(Node *root){
    Node *prev, *p=root;
    if(p!=0){
        while(p->left!=0)
            p=p->left;
        while(p!=0){
            std::cout<<p->el<<" ";
            prev=p;
            p=p->right;
            if(p!=0 && prev->successor==0)
                while(p->left !=0)
                    p=p->left;
        }
    }

}
Node *create(int e)
{
    Node *N= new Node(e);
    return N;
}


int main()
{
    Node *root= create(13);
    root->left=create(10);
    root->right=create(25);
    root->left->left=create(2);
    root->left->right=create(12);
    root->right->left=create(20);
    root->right->right=create(31);
    root->right->right->left=create(29);
    
    //bfs_levelorder(root);
    //bfs_preorder(root);
    //bfs_postorder(root);
    bfs_inorder(root);
   // thread_inorder(root);
    

    return 0;
}