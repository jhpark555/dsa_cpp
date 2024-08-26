#include <iostream>
#include <vector>
#include "stackEmptyException.h"

using namespace std;

template<typename E>
class ArrayStack{
    enum {DEF_CAPACITY = 100};
    public:
        ArrayStack(int cap = DEF_CAPACITY);
        int size() const;
        bool empty() const;
        const E& top() const ;//throw(StackEmpty);
        void push(const E& e) ;//throw(StackFull);;
        void pop() ;//throw(StackEmpty);
    private:
        E* S;
        int capacity;
        int t;     //top of stack index
};

template<typename E>
ArrayStack<E>::ArrayStack(int cap): 
    S(new E[cap]), capacity(cap), t(-1){}

template<typename E>
int ArrayStack<E>::size() const{
    return t+1;
}

template<typename E>
bool ArrayStack<E>::empty() const{
    return (t< 0);
}
template<typename E>
const E& ArrayStack<E>:: top() const /*throw(StackEmpty)*/{
    //if( empty() )throw StackEmpty("Top of empty stack");
    return S[t];
}

template<typename E>
void ArrayStack<E>:: push(const E& e) /*throw(StackFull)*/{
    //if( size()==capacity) throw StackFull("Push to full stack");
    S[++t]=e;
}

template<typename E>
void ArrayStack<E>:: pop() /*throw(StackEmpty)*/{
    //if(empty()) throw StackEmpty("Pop from empty stack");
    --t;
}



template<typename E>
void reverse(vector<E>& V){
    ArrayStack<E> S(V.size());
    for(int i=0;i< V.size();i++){
        S.push(V[i]);
    }
    for(int i=0;i< V.size();i++){
        V[i]=S.top(); S.pop();
    }    
    
}

int main(void){

    ArrayStack<int> A;

    A.push(7);
    A.push(13);
    cout<<A.top()<<endl; A.pop();
    A.push(9);
    cout << A.top() << endl; // A = [7, 9*], outputs: 9
    cout << A.top() << endl; A.pop(); // A = [7*], outputs: 9

    ArrayStack<string> B(10); // B = [ ], size = 0

    B.push("Bob"); // B = [Bob*], size = 1
    B.push("Alice"); // B = [Bob, Alice*], size = 2
    cout << B.top() << endl; B.pop(); // B = [Bob*], outputs: Alice
    B.push("Eve");

    cout<<"________________"<<"\n";
    vector<string> V={"Jack", "Kate", "Hurley", "Jin", "Michael"};
    reverse(V);
    for(int i=0;i<V.size(); i++){
        cout<<V[i] <<endl;
    }
    return 0;
}