#include <iostream>
#include <vector>
#include <list>

using namespace std;

typedef int Elem;

struct Node{
    Elem elt;
    Node* par;
    Node* left;
    Node* right;
    Node(): elt(),par(NULL),left(NULL),right(NULL){}
};

class Position {
    private:
        Node* v;
    public:
        Position(Node* _v=NULL): v(_v){}
        Elem& operator*(){
            return v->elt; 
        }
        Position left() const{
            return Position(v->left);
        }
        Position right() const{
            return Position(v->right);
        }
        Position parent() const{
            return Position(v->par);
        }
        bool isRoot() const{
            return v->par==NULL;
        }
        bool isExternal() const{
            return v->left==NULL && v->right==NULL;
        }
       
};

typedef list<Position> PositionList;

class BinaryTree{ // binary tree
    public: // public types
        class Position; // a node position
        class PositionList; // a list of positions
    public: // member functions
        int size() const; // number of nodes
        bool empty() const; // is tree empty?
        Position root() const; // get the root
        PositionList positions() const; // list of nodes
};

template<typename E, typename R>
class EulerTour{
    protected:
        struct result{
            R leftResult;
            R rightResult;
            R finalResult;
        };
        typedef BinaryTree<E> BinaryTree;
        typedef typename BinaryTree::Position Position;
    protected:
        const BinaryTree* tree;
    public:
        void initialize(const BinaryTree& T){
            tree= &T;
        }
    protected:
        int eulerTour(const Position& p) const;
        virtual void visitExternal(const Position& p, Result& r) const{}
        virtual void visitLeft(const Position& p, Result& r) const{}
        virtual void visitBelow(const Position& p, Result& r) const {}
        virtual void visitRight(const Position& p, Result& r) const{}
        Result initResult() const { return Result();}
        int result(const Result& r) const {return r.finalResult;}
};

template<typename E, typename R>
int EulerTour<E,R>::eulerTour(const Position& p) const{
    Result r=initResult();

    if(p.isExternal()){
        visitExternal(p,r);
    }
    else{
        visitLeft(p,r);
        r.leftResult = eulerTour(p.left());
        visitBelow(p,r);
        r.rightResult =eulerTour(p.right());
        visitRight(p,r);
    }
    return result(r);
}

template<typename E, typename R>
class EvaluateExpressionTour: public EulerTour<E,R>{
    protected:
        typedef typename EulerTour<E,R>::BinaryTree BinaryTree;
        typedef typename EulerTour<E,R>::Position Position;
        typedef typename EulerTour<E,R>::Result Result;
    public:
        void execute(const BinaryTree& T){
            initialize(T);
            std::cout<<"The value is:"<< eulerTour(T.root())<<"\n";
        }
    protected:
        virtual void visitExternal(const Position&p, Result& r) const{
            r.finalResult = (*p).value;
        }
        virtual void visitRight(const Position&p, Result& r) const{
            r.finalResult = (*p).operation(r.leftResult,r.rightResult);
        }
};

template<typename E,typename R>
class PrintExpressionTour: public EulerTour<E,R>{
    protected:
        typedef typename EulerTour<E,R>::BinaryTree BinaryTree;
        typedef typename EulerTour<E,R>::Position Position;
        typedef typename EulerTour<E,R>::Result Result;
    public:
        void execute(const BinaryTree& T){
            initialize(T);
            cout<<"Expression: "<<eulerTour(T.root())<<endl;
        }
    protected:
        virtual void visitExternal(const Position& p, Result& r) const{
            (*p).print();
        }
        virtual void visitLeft(const Position& p, Result* r) const{
            cout<<"(";
        }
        virtual void visitBelow(const Position& p, Result& r) const{
             (*p).print(); 
        } // right: close expression
        virtual void visitRight(const Position& p, Result& r) const {
             cout << ")"; 
        }

};