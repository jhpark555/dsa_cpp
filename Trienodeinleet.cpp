#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

struct TrieNode
{
    unordered_map<char,TrieNode *> children;
    bool word=false;
};

class WordDictionary
{
    TrieNode *trie;
public:
    WordDictionary() { trie= new TrieNode() ;}

    void addWord(string word)
    {
        TrieNode* node = trie;
        for(char ch: word)
        {
            if(!node->children.count(ch))
                node->children[ch]=new TrieNode();
            node= node->children[ch];
        }
        node->word= true;
    }
    bool searchInNode(string word, TrieNode* node)
    {
        for(int i=0;i< word.length(); ++i)
        {
            char ch=word[i];
            if(!node->children.count(ch))
            { 
                if(ch=='.'){
                    for(auto x: node->children)
                    {
                        TrieNode *child = x.second;
                        if(searchInNode(word.substr(i+1),child)){
                            return true;
                        }
                    }
                }
                return false;
            }
            else{
                node= node->children[ch];
            }
        }
        return node->word;
    }
    bool search(string word){
        return searchInNode(word,trie);
    }
};

int main()
{
    WordDictionary word;
    word.addWord("bad");
    word.addWord("dad");
    word.addWord("mad");
    cout<<word.search("pad")<<"\n"; // false
    cout<<word.search("bad")<<"\n"; // true
    cout<<word.search(".ad")<<"\n"; // true
    cout<<word.search("b..")<<"\n"; // true
    
    return 0;

}