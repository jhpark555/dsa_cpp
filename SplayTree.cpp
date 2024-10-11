#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>
#include <cstdlib> // exit()

using namespace std;

template<typename T>
class SplayingNode
{
    public:
        SplayingNode() : left(NULL),right(NULL),parent(NULL) {}
        SplayingNode(const T& el, SplayingNode *l=NULL,
            SplayingNode *r=NULL, SplayingNode *p=NULL)
        {
            info=el;
            left=l;
            right=r;
            parent=p;
        }
        T info;
        SplayingNode *left,*right, *parent;

};

template<typename T>
class SplayTree
{
    public:
        SplayTree() : root(NULL) {}
        void inorder(){
            inorder(root);
        }
        T *search(const T&);
        void insert(const T&);

    protected:
        SplayingNode<T> *root;
        void rotateR(SplayingNode<T>* p);
        void rotateL(SplayingNode<T>* p);
        void continueRotation(SplayingNode<T>* gr, SplayingNode<T>* par,
         SplayingNode<T>* ch, SplayingNode<T>* desc);
        void semisplay(SplayingNode<T>* p);
        void inorder(SplayingNode<T>* p);
        void virtual visit(SplayingNode<T>*) {}
};

template<typename T>
void SplayTree<T>::continueRotation(SplayingNode<T>* gr, SplayingNode<T>* par,
         SplayingNode<T>* ch, SplayingNode<T>* desc)
{
    if(gr!=NULL){
        if(gr->right==ch->parent)
            gr->right=ch;
        else gr->left=ch;
    }
    else root=ch;

    if(desc!=NULL)
        desc->parent=par;
    par->parent=ch;
    ch->parent=gr;
}
template<typename T>
void SplayTree<T>::rotateR(SplayingNode<T> *p)
{
    p->parent->left=p->right;
    p->right= p->parent;
    continueRotation(p->parent->parent,p->right,p,p->right->left);
}
template<class T>
void SplayTree<T>::rotateL(SplayingNode<T>* p) {
    p->parent->right = p->left;
    p->left = p->parent;
    continueRotation(p->parent->parent,p->left,p,p->left->right);
}

template<class T>
void SplayTree<T>::semisplay(SplayingNode<T>* p) 
{
    while (p != root) {
        if (p->parent->parent == 0) // if p’s parent is the root;
            if (p->parent->left == p)
                rotateR(p);
            else rotateL(p);
        else if (p->parent->left == p) // if p is a left child;
            if (p->parent->parent->left == p->parent) {
                rotateR(p->parent);
                p = p->parent;
            }
            else {
                rotateR(p); // rotate p and its parent;
                rotateL(p); // rotate p and its new parent;
            }
        else // if p is a right child;
            if (p->parent->parent->right == p->parent) {
                rotateL(p->parent);
                p = p->parent;
            }
            else {
                rotateL(p); // rotate p and its parent;
                rotateR(p); // rotate p and its new parent;
            }
        if (root == 0) // update the root;
            root = p;
        }
}
template<class T>
T* SplayTree<T>::search(const T& el) 
{
    SplayingNode<T> *p = root;
    while (p != 0)
        if (p->info == el) { // if el is in the tree,
            semisplay(p); // move it upward;
            return &p->info;
        }
        else if (el < p->info)
            p = p->left;
        else p = p->right;
    return 0;
}
template<class T>
void SplayTree<T>::insert(const T& el) 
{
    SplayingNode<T> *p = root, *prev = 0, *newNode;
    while (p != 0) { // find a place for inserting a new node;
        prev = p;
        if (el < p->info)
        p = p->right;
    }
    if ((newNode = new SplayingNode<T>(el,0,0,prev)) == 0) {
        cerr << "No room for new nodes\n";
        exit(1);
    }
    if (root == 0) // the tree is empty;
        root = newNode;
    else if (el < prev->info)
        prev->left = newNode;
    else prev->right = newNode;
}
template<class T>
void SplayTree<T>::inorder(SplayingNode<T> *p) 
{
    if (p != 0) {
        inorder(p->left);
        visit(p);
        inorder(p->right);
    }
}

class Word 
{
    public:
        Word() {
            freq = 1;
        }
        int operator== (const Word& ir) const {
            return strcmp(word,ir.word) == 0;
        }
        int operator< (const Word& ir) const {
            return strcmp(word,ir.word) < 0;
        }
    private:
        char *word;
        int freq;
        friend class WordSplay;
        friend ostream& operator<< (ostream&,const Word&);
};

class WordSplay : public SplayTree<Word> 
{
    public:
        WordSplay() {
            differentWords = wordCnt = 0;
        }
        void run(ifstream&,char*);
    private:
        int differentWords, // counter of different words in a text file;
        wordCnt; // counter of all words in the same file;
        void visit(SplayingNode<Word>*);
};

void WordSplay::visit(SplayingNode<Word> *p) 
{
    differentWords++;
    wordCnt += p->info.freq;
}
void WordSplay::run(ifstream& fIn, char *fileName) 
{
    char ch = ' ', i;
    char s[100];
    Word rec;
    while (!fIn.eof()) {
        while (1)
            if (!fIn.eof() && !isalpha(ch)) // skip nonletters
                fIn.get(ch);
            else break;
        if (fIn.eof()) // spaces at the end of fIn;
            break;
        for (i = 0; !fIn.eof() && isalpha(ch); i++) {
            s[i] = toupper(ch);
            fIn.get(ch);
        }
        s[i] = '\0';
        if (!(rec.word = new char[strlen(s)+1])) {
            cerr << "No room for new words.\n";
            exit(1);
        }
        strcpy(rec.word,s);
        Word *p = search(rec);
        if (p == 0)
            insert(rec);
        else p->freq++;
    }
    inorder();
    cout << "\n\nFile " << fileName
        << " contains " << wordCnt << "words among which "
        << differentWords << " are different\n";
}

int main(int argc, char* argv[]) 
{
    char fileName[80];
    WordSplay splayTree;
    if (argc != 2) {
    cout << "Enter a file name: ";
    cin >> fileName;
    }
    else strcpy(fileName,argv[1]);
    ifstream fIn(fileName);
    if (fIn.fail()) {
        cerr << "Cannot open " << fileName << endl;
        return 0;
    }
    splayTree.run(fIn,fileName);
    fIn.close();
    return 0;
}