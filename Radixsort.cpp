#include <string>
#include <vector>
#include <iostream>

using namespace std;

void radixSortA(vector<string>& arr, int stringLen)
{
    const int BUCKETS =256;
    vector<vector<string>> buckets(BUCKETS);

    for(int pos= stringLen-1; pos>= 0; --pos)
    {
        for(string& s:arr){
           buckets[s[pos]].push_back(s);
           //cout<<s[pos]<<" \n";
        }
        int idx=0;
        for(auto & thisBucket : buckets)
        {
            for(string& s: thisBucket)
                arr[idx++]=s;
            thisBucket.clear();
        }

    }
}
int main()
{
    vector<string> arr = {"cpple", "aanana", "bherry","tttt"};        
        
    int max=0,i;
    for(i=0; i<arr.size(); i++){
        if( arr[i].length() >max )
            max=arr[i].length();
    }
    cout<<"max:"<<max<<"\n";
    radixSortA(arr, max);

    for(auto &s: arr)
       cout<<s<<" ";
}