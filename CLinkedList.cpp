#include <iostream>

using namespace std;

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

int main(void){
    //CircleList C;
    //C.add("one");
    //C.add("two");
    //C.add("Three");
    //C.add("Four");
    //C.printList();

    CircleList playList; // [ ]
    playList.add("Stayin Alive"); // [Stayin Alive*]
    playList.add("Le Freak"); // [Le Freak, Stayin Alive*]
    playList.add("Jive Talkin"); // [Jive Talkin, Le Freak, Stayin Alive*]
    playList.advance(); // [Le Freak, Stayin Alive, Jive Talkin*]
    playList.advance(); // [Stayin Alive, Jive Talkin, Le Freak*]
    playList.remove(); // [Jive Talkin, Le Freak*]
    playList.add("Disco Inferno"); // [Disco Inferno, Jive Talkin, Le Freak*]

    playList.printList();
    return 0;
}