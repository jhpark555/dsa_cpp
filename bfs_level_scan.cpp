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

void MorrisInorder(Node *root){
    Node *p=root, *tmp;

    while(p!=0){
        if(p->left==0){
            std::cout<<p->el<<" ";
            p=p->right;
        }
        else{
            tmp =p->left;
            while(tmp->right!=0 && tmp->right!=p)
                tmp=tmp->right;
            if(tmp->right==0){
                tmp->right=p;
                p=p->left;
            }
            else{
                std::cout<<p->el<<" ";
                tmp->right=0;
                p=p->right;
            }
        }
    }
}

void insert(Node **root,const int&el){
    Node *p=*root, *prev=0;

    while(p!=0){
        prev=p;
        if(el< p->el)
            p=p->left;
        else 
            p=p->right;
    }
  
    if(*root==0) *root= new Node(el);
    else if(el< prev->el){
        prev->left=new Node(el);
    }
    else {
        prev->right=new Node(el);
    }
   
}

Node *create(int e)
{
    Node *N= new Node(e);
    return N;
}

void deleteByCopying(Node *&node){
    Node *prev,*tmp=node;
    if(node->right ==0)
        node=node->left;
    else if(node->left==0)
        node=node->right;
    else{
        tmp=node->left;
        prev=node;
        while(tmp->right!=0){
            prev=tmp;
            tmp=tmp->right;
        }
        node->el=tmp->el;
        if(prev ==node)
            prev->left=tmp->left;
        else 
            prev->right=tmp->left;
    }
    delete tmp;
}


void deleteByMerging(Node *&node){
    Node *tmp=node;
    if(node !=0){
        if(!node->right)
            node=node->left;
        else if(node->left==0)
            node=node->right;
        else{
            tmp=node->left;
            while(tmp->right!=0)
                tmp=tmp->right;
            tmp->right=node->right;
            tmp=node;
            node=node->left;
        }
        delete tmp;
    }
}

void findAndDeleteByMerging(Node *root,const int&el){
    Node *node=root, *prev=0;
    while(node!=0){
        if(node->el ==el)   break;
        prev=node;
        if(el< node->el)
            node=node->left;
        else   
            node=node->right;
    }
    if(node!=0 && node->el==el){
        if(node ==root)
           // deleteByMerging(root);
           deleteByCopying(root);
        else if(prev->left==node)
          //  deleteByMerging(prev->left);
          deleteByCopying(prev->left);
        else 
          //  deleteByMerging(prev->right);
          deleteByCopying(prev->right);
    }
    else if(root!=0)
        std::cout<<"element" << el << "is not in the tree\n";
    else std::cout<<"the tree is empty\n";
}


int main()
{
#if 0
    Node *root= create(13);
    root->left=create(10);
    root->right=create(25);
    root->left->left=create(2);
    root->left->right=create(12);
    root->right->left=create(20);
    root->right->right=create(31);
    root->right->right->left=create(29);
#else
    Node *root=NULL;
   
     insert(&root,13);   
     insert(&root,10);   
     insert(&root,25);   
     insert(&root,2);   
     insert(&root,12);  
     insert(&root,20);   
     insert(&root,31);    
     insert(&root,29);
     insert(&root,33);
     insert(&root,1);
     insert(&root,4);
     insert(&root,3);
#endif
    
    bfs_levelorder(root);
    //bfs_preorder(root);
    //bfs_postorder(root);
    //bfs_inorder(root);
    //MorrisInorder(root);
   // thread_inorder(root);
    findAndDeleteByMerging(root,10);
    std::cout<<"\n";
    bfs_levelorder(root);

    return 0;
}