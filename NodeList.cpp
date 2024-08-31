#include <iostream>

using namespace std;
typedef int Elem;

class NodeList{
    private:
        struct Node{
            Elem elem;
            Node *prev;
            Node *next;
        };

    public:
        class Iterator{
            public:
                Elem& operator*();
                bool operator==(const Iterator& p) const;
                bool operator!=(const Iterator& p) const;
                Iterator& operator++();
                Iterator& operator--();
                friend class NodeList;
                friend class NodeSequence;
            private:
                Node *v;
                Iterator(Node* u);
        };

     public:
        NodeList();
        int size() const;
        bool empty() const;
        Iterator begin() const;
        Iterator end() const;
        void insertFront(const Elem& e);
        void insertBack(const Elem& e);
        void insert(const Iterator&p , const Elem& e);
        void eraseFront();
        void eraseBack();
        void erase(const Iterator& p);
        void printlist();
    private:
        int n;
        Node* header;
        Node *trailer;    
};

class NodeSequence:public NodeList{
    public:
        Iterator atIndex(int i) const;
        int indexOf(const Iterator& p) const;
        void printlist(NodeSequence& p);
};



NodeList::Iterator::Iterator(Node* u){
    v=u;
}
Elem& NodeList::Iterator::operator*(){
    return v->elem;
}
bool NodeList::Iterator::operator==(const Iterator& p) const{
    return v==p.v;
}
bool NodeList::Iterator::operator!=(const Iterator& p) const{
    return v !=p.v;
}
NodeList::Iterator& NodeList::Iterator::operator++(){
    v=v->next;
    return *this;
}
NodeList::Iterator& NodeList::Iterator::operator--(){
    v=v->prev;
    return *this;
}

NodeList::NodeList(){
    n=0;
    header=new Node;
    trailer= new Node;
    header->next=trailer;
    trailer->prev= header;
}
int NodeList::size() const{
    return n;
}
bool NodeList::empty() const{
    return n==0;
}
NodeList::Iterator NodeList::begin() const{
    return Iterator(header->next);
}
NodeList::Iterator NodeList::end() const{
    return Iterator(trailer);
}
void NodeList::insert(const NodeList::Iterator &p,const Elem &e){
    Node* w=p.v;
    Node *u=w->prev;
    Node* v=new Node;    
    v->elem=e;
    
    v->next=w;
    w->prev=v;
    v->prev=u;
    u->next=v;
    n++;    
}

void NodeList::insertFront(const Elem& e){
    insert(begin(),e);
}
void NodeList::insertBack(const Elem& e){
    insert(end(),e);
}
void NodeList::erase(const Iterator& p){
    Node* v=p.v;
    Node* w=v->next;
    Node* u=v->prev;
    u->next=w;
    w->prev=u;
    delete v;
    n--;
}
void NodeList::eraseFront(){
    erase(begin());
}
void NodeList::eraseBack(){
    erase(--end());
}
void NodeList::printlist(){
    Node *curr=header->next;
    while(curr!=trailer){
        cout<<curr->elem<<endl;
        curr=curr->next;
    }
}

NodeSequence::Iterator NodeSequence::atIndex(int i) const{
    Iterator p =begin();
    for (int j=0; j< i; i++) ++p;
    return p;
}

int NodeSequence::indexOf(const Iterator& p) const{
    Iterator q=begin();
    int j=0;
    while(q!=p){
        ++q;++j;
    }
    return j;
}

void NodeSequence::printlist(NodeSequence& S){
    int n=S.size();
    NodeSequence::Iterator prec = S.begin();
    for(int i=0;i< n; i++){
      cout<<*prec<<endl;;
      ++prec;
    }     
}

void bubbleSort1(NodeSequence& S){
    int n= S.size();
    cout<<"size="<<n;
    for(int i=0; i<n; i++)
     for(int j=1 ;j<n-i ; j++){
        NodeSequence::Iterator prec= S.atIndex(j-1);
        NodeSequence::Iterator succ= S.atIndex(j);
       
        if(*prec>*succ){
            int temp=*prec;
            *prec=*succ;
            *succ=temp;
        }
     }
}

void bubbleSort2(NodeSequence& S) { // bubble-sort by positions
    int n = S.size();
    for (int i = 0; i < n; i++) { // i-th pass
        NodeSequence::Iterator prec = S.begin(); // predecessor
        for (int j = 1; j < n-i; j++) { 
            NodeSequence::Iterator succ = prec;
            ++succ; // successor
            if (*prec > *succ) { // swap if out of order
                int tmp = *prec; *prec = *succ; *succ = tmp;
            }
            ++prec; // advance predecessor
        }
    }

}

int main(void){
    NodeList N;
    N.insertFront(10);
    N.insertFront(20);
    N.insertFront(30);
    N.insertBack(40);
    N.eraseBack();
    N.printlist();

#if 1
    NodeSequence M;
    M.insertFront(10);
    M.insertFront(20);
    M.insertFront(30);
    M.insertBack(40);
    
    bubbleSort2(M);
    M.printlist(M);
#endif
}