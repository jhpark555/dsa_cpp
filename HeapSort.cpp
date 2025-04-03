#include <iostream>
#include <vector>

using namespace std;

template <typename Comparable>
void percDown(vector<Comparable> &a, int i, int n);

template <typename Comparable>
void heapsort(vector<Comparable> &a)
{
    for(int i=a.size()-1; i>=0; --i)     //build heap
       percDown(a, i, a.size());

    for(int j=a.size()-1; j>0; --j)
    {
        swap(a[0],a[j]);       //delete  max
        percDown(a,0,j);
    }
}

int leftChild(int i)
{
    return 2*i+1;
}

template<typename Comparable>
void percDown(vector<Comparable> &a, int i, int n)
{
    int child;
    Comparable tmp;

    for( tmp= a[i]; leftChild(i)< n; i=child)
    {
        child = leftChild(i);
        if( child !=n-1 && a[child]< a[child+1])   //max heap
            ++child;
        if(tmp< a[child])
           a[i]=a[child];
        else
           break;
    }
    a[i]=tmp;

}

int main()
{
  vector<int> arr={1,10,4,13,22,51};

  heapsort(arr);

  for(auto &i: arr)
     cout<<i<<" ";

}