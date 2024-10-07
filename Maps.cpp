#include <iostream>
#include <map>
#include <iterator>

using namespace std;

template<typename K,typename V>
class Entry{
    public:
        Entry(const K& k=K(), const V& v=V()): _key(k),_value(v){}
        const K& key() const {return _key;}
        const V& value() const {return _value;}
        void setKey(const K& k) { _key=k;}
        void setValue(const V& v) {_value=v;}
    private:
        K _key;
        V _value;
};
template<typename K,typename V>
class Map{
    public:
        class Entry;
        class Iterator;

        int size() const;
        bool empty() const;
        Iterator find(const K& k) const;
        Iterator put(const K& k,const V& v);
        void erase(const K& k);
        void erase(const Iterator& p);
        Iterator begin();
        Iterator end();
};

int main()
{
    map<string,int> myMap;
    map<string,int>::iterator p;
    myMap.insert(pair<string,int>("Rob",28));
    myMap["joe1"]=38;
    myMap["joe"]=50;
    myMap["Sue"] = 75;
    p=myMap.find("joe");
    cout<<p->second<<endl;
    if(p==myMap.end()) cout<<"End";
    for(p=myMap.begin(); p!=myMap.end();++p)
      cout<< p->first <<" :" << p->second << endl;
    
    return 0;
}