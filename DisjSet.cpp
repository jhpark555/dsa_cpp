#include <iostream>
#include <vector>

using namespace std;

class DisjSets
{
  public:
    explicit DisjSets( int numElements)
    { s.assign(numElements,-1); }
    int find(int x) const
    {
        if(s[x]<0) return x;
        else 
            return find(s[x]);
    }
    //int find(int x);
    void unionSets(int root1, int root2)
    {
        if(s[root2]<s[root1])    // big (-) means height is deeper, so root2 is root 
           s[root1]=root2;
        else{
            if(s[root1] ==s[root2])
                --s[root1];
            s[root2]=root1;    
        }
    }
  private:
    vector<int> s;
};

int main()
{
    DisjSets d(8);

    d.unionSets(6, 7);
    d.unionSets(4, 5);
    d.unionSets(4, 6);
    d.unionSets(4, 3);

    int f=d.find(7);
    cout<<"root: "<<f;
    return 0;
}