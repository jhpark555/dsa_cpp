#include <iostream>

using namespace std;

typedef int Elem;
class ArrayVector{
    public:
        ArrayVector();
        int size() const;
        bool empty() const;
        Elem& operator[](int i);
        Elem& at(int i);
        void erase(int i);
        void insert(int i,const Elem& e);
        void reserve(int N);
        void printarray();
    private:
        int capacity;
        int n;
        Elem* A;
};

ArrayVector::ArrayVector(): A(NULL),capacity(0),n(0){}
int ArrayVector::size() const{
    return n;
}
bool ArrayVector::empty() const{
    return size()==0;
}
Elem& ArrayVector::operator[](int i){
    return A[i];
}
Elem& ArrayVector::at(int i){
    return A[i];
}
void ArrayVector::erase(int i){
    for(int j=i+1;j<n; j++){
        A[j-1]=A[j];
    }
    n--;
}
void ArrayVector::reserve(int N){
    if(capacity >=N ) return;
    Elem *B= new Elem[N];
    for( int j=0; j< n; j++)
        B[j]=A[j];
    if(A!=NULL) delete []A;
    A=B;
    capacity= N;
}
void ArrayVector::insert(int i, const Elem& e){
    if(n >=capacity) reserve(max(1,2*capacity));

    for( int j=n-1; j>= i; j--){
        A[j+1]=A[j];
    }
    A[i]=e;
    n++;
}
void ArrayVector::printarray(){
    for( int i=0;i<n ; i++)
        cout<<A[i]<<endl;
}

int main(void)
{
   ArrayVector A;
   A.insert(0,7);
   A.insert(0,4);
   A.at(1);
   A.printarray();

}