#include <iostream>

using namespace std;

class StringNode{
    private:
        string ele;
        StringNode *next;

        friend class StringLinkedList;
};

class StringLinkedList{
    public:
        StringLinkedList();
        ~StringLinkedList();
        bool empty() const;
        const string& front() const;
        void addFront(const string& e);
        void removeFront();
        void printList() const;
    private:
        StringNode *head;
};

StringLinkedList::StringLinkedList():head(NULL) {}
StringLinkedList::~StringLinkedList(){
    while(!empty()){
        removeFront();
    }
}
bool StringLinkedList::empty() const{
    return head==NULL;
}
const string& StringLinkedList:: front() const{
    return head->ele;
}
void StringLinkedList::addFront(const string& e){
    StringNode *v= new StringNode;
    v->ele=e;
    v->next=head;
    head=v;
}
void StringLinkedList::removeFront(){
    StringNode *old=head;
    head = old->next;
    delete old;
}
void StringLinkedList::printList() const{
    if(head==NULL) cout<<"List is empty!"<<endl;

    StringNode *curr= head;
    

    while( curr!=NULL){
        cout<<curr->ele<<"\n";
        curr=curr->next;
    }
}

int main(void){
    StringLinkedList root;
    root.addFront("Arshad");
    root.addFront("Asifa");
    root.addFront("Afrid");
    root.printList();

    return 0;
}