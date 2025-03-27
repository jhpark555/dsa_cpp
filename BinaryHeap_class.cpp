#include <iostream>
#include <vector>

using namespace std;

template<typename Comparable>
class BinaryHeap
{
public:
    explicit BinaryHeap(int capacity = 1): currentSize{capacity} {  }
    explicit BinaryHeap( const vector<Comparable>& items) 
     { array=items;  currentSize=array.size();  }

    bool isEmpty() const
    { return currentSize==0; }
    const Comparable& findMin() const;

    void insert(const Comparable &x)
    {
        if(currentSize ==array.size()-1)
            array.resize(array.size()*2);
            
        //percolate up
        int hole = currentSize++;
        Comparable copy =x;

        array[0]= std::move(copy);
        //for(; x< array[hole/2]; hole /=2) //go up to parent
        while (x < array[hole / 2]) 
        {
            array[hole] = std::move(array[hole / 2]); // swap with parent
            hole = hole / 2;
        }
        array[hole]=std::move(array[0]);
    }


    void insert(Comparable &&x)
    {
        if (currentSize == array.size() - 1)
            array.resize(array.size() * 2);

        // percolate up
        int hole = currentSize++;
        Comparable copy = std::move(x);
        //cout<<"insert "<<x <<" "<< hole<<" "<<currentSize;
        array[0] = std::move(copy);
        // for(; x< array[hole/2]; hole /=2) //go up to parent
        while (x < array[hole / 2])
        {
            array[hole] = std::move(array[hole / 2]); // swap with parent
            hole = hole / 2;
        }
        array[hole] = std::move(array[0]);
    }

    void deleteMin()
    {
        if(isEmpty())
            return ;
        cout << "Min:" << array[1] <<"\n";;
        array[1]=std::move(array[currentSize-1]);   // last one -> first one
        percolateDown(1);
        
    }

    // remove min and replace it with minItem
    void deleteMin(Comparable &minItem)
    {
        if(isEmpty())
            return;
        minItem =std::move(array[1]);
        array[1]= std::move(array[currentSize--]);
        percolateDown(1);
    }

    void makeEmpty();

private:
    int currentSize;
    vector<Comparable> array;

    void buildHeap();
    void percolateDown(int hole)
    {
        int child;
        Comparable tmp=std::move(array[hole]);
        
        while( hole*2<=currentSize )
        {
            child = 2*hole;
            if(child!= currentSize && array[child+1]< array[child])
                ++child;
            if(array[child] < tmp)
                array[hole]=std::move(array[child]);
            else
                break;
            hole =child;
        }
        array[hole]=std::move(tmp);
    }
};

int main()
{
    vector<int> v={-1,13, 21, 16, 24, 31, 19, 68, 65, 26, 32};
    BinaryHeap h(v);
 
    h.insert(14);
    h.deleteMin();
    h.deleteMin();
    h.deleteMin();
}