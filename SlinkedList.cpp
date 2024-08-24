#include <iostream>

using namespace std;


template <typename>class SLinkedList;

template<typename E>
class SNode {
    private:
        E ele;
        SNode<E>* next;
        friend class SLinkedList<E>;
};



template<typename E>
class SLinkedList{
    public:
        SLinkedList();
        ~SLinkedList();
        bool empty() const;
        const E& front() const;
        void addFront(const E& e);
        void removeFront();
        void printList();
    private:
        SNode<E>* head;
};

template<typename E>
SLinkedList<E>::SLinkedList()
 :head(NULL){}

template<typename E>
SLinkedList<E>::~SLinkedList(){
    while(!empty()) removeFront();
}

template<typename E>
bool SLinkedList<E>::empty() const{
    return head==NULL;
}
template<typename E>
const E& SLinkedList<E>::front() const{
    return head->ele;
}

template<typename E>
void SLinkedList<E>::addFront(const E& e){
    SNode<E>* v= new SNode<E>;
    v->ele=e;
    v->next=head;
    head=v;

}

template<typename E>
void SLinkedList<E>::removeFront(){
    SNode<E>* old=head;
    head=head->next;
    delete old;
}
template<typename E>
void SLinkedList<E>::printList(){
    SNode<E>* temp= head;
    
    while( temp!=NULL){
        cout<<temp->ele<<"\n";
        temp=temp->next;
    }
}

int main(void) {
    SLinkedList<int> b;
    b.addFront(10);
    b.addFront(12);
    b.addFront(13);

    b.printList();
    return 0;
}
