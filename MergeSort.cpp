#include <iostream>
#include <vector>

using namespace std;



template<typename Comparable>
void merge(vector<Comparable>& a, vector<Comparable> &tmpArray,
    int leftPos, int rightPos, int rightEnd)
{
    int leftEnd= rightPos-1;
    int tmpPos=leftPos;
    int numElements= rightEnd-leftPos+1;

    while(leftPos<= leftEnd && rightPos<=rightEnd)
    {
        if(a[leftPos]< a[rightPos]) tmpArray[tmpPos++]=a[leftPos++];
        else    tmpArray[tmpPos++]= a[rightPos++];
    }
    while(leftPos<=leftEnd)
        tmpArray[tmpPos++]= a[leftPos++];
    while(rightPos<=rightEnd)
        tmpArray[tmpPos++]= a[rightPos++];

    for(int i=0; i< numElements; i++, --rightEnd)
      a[rightEnd]= tmpArray[rightEnd];

}

template<typename Comparable>
void mergeSort(vector<Comparable>& a, vector<Comparable> & tmpArray, int left,int right)
{
    if(left< right)
    {
        int center= ( left + right) /2;
        mergeSort(a,tmpArray,left,center);
        mergeSort(a,tmpArray,center+1,right);
        merge(a,tmpArray,left,center+1,right);
    }
}


template<typename Comparable>
void mergeSort(vector<Comparable>& a)
{
    vector<Comparable> tmpArray( a.size() );
    mergeSort(a, tmpArray, 0, a.size()-1);
}

int main()
{
   vector<int> arr={7,2,5,4,9,19,20,55,34};

   mergeSort(arr);

   for(auto &a: arr)
      cout<<a<<" ";

}