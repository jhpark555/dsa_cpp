#include <iostream>

using namespace std;


typedef string Elem;
class DNode{
    private:
        Elem elem;
        DNode *prev;
        DNode *next;
        friend class DLinkedList;
};

class DLinkedList{
    public:
        DLinkedList();
        ~DLinkedList();
        bool empty() const;
        const Elem& front() const;
        const Elem& back() const;
        void addFront(const Elem& e);
        void addBack(const Elem& e);
        void removeFront();
        void removeBack();
        void printList();
    private:
        DNode *header;
        DNode *trailer;
    protected:
        void add(DNode *v,const Elem& e);
        void remove(DNode *v);
};

DLinkedList::DLinkedList(){
    header = new DNode;
    trailer= new DNode;
    header->next=trailer;
    trailer->prev=header;
}
DLinkedList::~DLinkedList(){
    while(!empty()) removeFront();
    delete header;
    delete trailer;
}

bool DLinkedList::empty() const{
    return header->next == trailer;
}

const Elem& DLinkedList::front() const{
    return header->next->elem;
}

const Elem& DLinkedList::back() const{
    return trailer->prev->elem;
}

void DLinkedList::add(DNode *v,const Elem& e){   //insert before v
    DNode *u= new DNode ;
    u->elem=e;
    u->next=v;
    u->prev=v->prev;
    v->prev->next=u;
    v->prev=u;
}

void DLinkedList::addFront(const Elem& e){
    add(header->next,e);
}

void DLinkedList::addBack(const Elem& e){
    add(trailer,e);
}

void DLinkedList::remove(DNode *v){
    DNode *u = v->prev;
    DNode *w=v->next;
    u->next=w;
    w->prev=u;
    delete v;
}

void DLinkedList::removeFront(){
    remove(header->next);
}

void DLinkedList::removeBack(){
    remove(trailer->prev);
}


void DLinkedList::printList(){
    DNode *curr=header->next;
   
    while(curr!=trailer){
        cout<<curr->elem<<endl;
        curr=curr->next;
    }
}

void listReverse(DLinkedList& L){
    DLinkedList T;

    while(!L.empty()){
        string s= L.front(); L.removeFront();
        T.addFront(s);
    }
    while(!T.empty()){
        string s=T.front(); T.removeFront();
        L.addBack(s);
    }
}

class LinkedDeque{
    public:
        LinkedDeque();
        int size() const;
        bool empty() const;
        const Elem& front() const;
        const Elem& back() const;
        void insertFront(const Elem& e);
        void insertBack(const Elem& e);
        void removeFront();
        void removeBack();
        void printlist();
    private:
        DLinkedList D;
        int n;
};

LinkedDeque::LinkedDeque(): D(),n(0) {}
int LinkedDeque::size() const{
    return n;
}
bool LinkedDeque::empty() const{
    return n==0;
}
const Elem& LinkedDeque::front() const{
     return D.front();
}
const Elem& LinkedDeque::back() const{
     return D.back();
}
void LinkedDeque::insertFront(const Elem& e){
    D.addFront(e);
    n++;
}
void LinkedDeque::insertBack(const Elem& e){
    D.addBack(e);
    n++;
}
void LinkedDeque::removeFront(){
    D.removeFront();
    n--;
}
void LinkedDeque::removeBack(){
    D.removeBack();
    n--;
}
void LinkedDeque::printlist(){
    D.printList();
}


class DequeStack{
    public:
        DequeStack();
        int size() const;
        bool empty() const;
        const Elem& top() const;
        void push(const Elem& e);
        void pop();
        void printlist();
    private:
        LinkedDeque D;

};

DequeStack::DequeStack(): D() {}
int DequeStack::size() const{
    return D.size();
}
bool DequeStack::empty() const{
    return D.empty();
}
const Elem& DequeStack::top() const{
    return D.front();
}
void DequeStack::push(const Elem& e){
    D.insertFront(e);
}
void DequeStack::pop(){
    D.removeFront();
}
void DequeStack::printlist(){
    D.printlist();
}

int main(void){
    LinkedDeque D;

    D.insertFront("hello");
    D.insertBack("Philip");
    D.insertBack("mom");
    D.insertFront("All");
    D.printlist();
cout<<"+++++++++++++++++"<<endl;
    DequeStack S;
    S.push("hello");
    S.push("philip");
    S.printlist();

    return 0;
}