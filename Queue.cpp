
#include <iostream>
#include "RuntimeException.h"


using namespace std;

class QueueEmpty : public RuntimeException {
    public:
        QueueEmpty(const string& err) : RuntimeException(err) { }
};

class QueueFull : public RuntimeException {
    public:
        QueueFull(const string& err) : RuntimeException(err) { }
};

typedef string Elem;

class CNode{
    private:
        Elem elem;
        CNode *next;
        friend class CircleList;
};

class CircleList{
    public:
        CircleList();
        ~CircleList();
        bool empty() const;
        const Elem& front() const;
        const Elem& back() const;
        void advance();
        void add(const Elem& e);
        void remove();
        void printList();
    private:
        CNode *cursor;
};

CircleList::CircleList(): cursor(NULL) {}
CircleList::~CircleList(){
    while(!empty()) remove();
}
bool CircleList::empty() const{
    return cursor==NULL;
}
const Elem& CircleList::front() const{
    return cursor->next->elem;
}
const Elem& CircleList::back() const{
    return cursor->elem;
}
void CircleList::advance(){
    cursor=cursor->next;
}
void CircleList::add(const Elem& e){    //add after cursor
    CNode *temp=new CNode;
    temp->elem=e;
    if(cursor==NULL){
        temp->next=temp;
        cursor=temp;
    }
    else{
        temp->next=cursor->next;
        cursor->next=temp;
        cursor=temp;
    }
}
void CircleList::remove(){    //remove after cursor
    CNode *old=cursor->next;
    if(old==cursor){
        cursor=NULL;
    }
    else{
        cursor->next=old->next;
        delete old;
    }
}

void CircleList::printList(){
    CNode *curr=cursor;
    while(curr->next!=cursor){
        cout<< curr->elem<<endl;
        curr=curr->next;
    }
    cout<<curr->elem<<endl;
}


typedef string Elem;
class LinkedQueue{
    public:
        LinkedQueue();
        int size() const;
        bool empty() const;
        const Elem& front() const ;//throw(QueueEmpty);
        void enqueue(const Elem& e);
        void dequeue();// throw(QueueEmpty);
        void printlist();
    private:
        CircleList C;
        int n;
};

LinkedQueue::LinkedQueue(): C(),n(0) {}
int LinkedQueue::size() const{
    return n;
}
bool LinkedQueue::empty() const{
    return n==0;
}
const Elem& LinkedQueue::front() const {
    //if(empty()) throw QueueEmpty("front of empty queue");
    return C.front();
}
void LinkedQueue::enqueue(const Elem& e){
    C.add(e);
    C.advance();
    n++;
}
void LinkedQueue::dequeue(){
    //if(empty()) throw QueueEmpty(" dequeue of empty queue");
    C.remove();
    n--;
}
void LinkedQueue::printlist(){
    C.printList();
}
int main(void){
    LinkedQueue L;

    L.enqueue("hello");
    L.enqueue("philip");
    L.enqueue("morning");
    L.printlist();
}