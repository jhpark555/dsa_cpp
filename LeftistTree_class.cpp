#include <iostream>

using namespace std;

template<typename Comparable>
class LeftistHeap
{
public:
    LeftistHeap();
    LeftistHeap(const LeftistHeap &rhs);
    LeftistHeap(LeftistHeap &&rhs);

    ~LeftistHeap();

    LeftistHeap & operator=(const LeftistHeap &rhs);
    LeftistHeap & operator=(LeftistHeap &&rhs);

    bool isEmpty() const;
    const Comparable &findMin() const;

    void insert(const Comparable &x);
    void insert(Comparable &&x);
    void deleteMin();
    void deleteMin(Comparable & minItem);
    void makeEmpty();
    void merge( LeftistHeap &rhs);
private:
    struct LeftistNode
    {
        Comparable element;
        LeftistNode *left;
        LeftistNode *right;
        int nlp;

        LeftistNode(const Comparable &e, LeftistNode *lt=nullptr,
        LeftistNode *rt=nullptr, int np=0)
        : element{e}, left{lt}, right{rt}, nlp{np} {}

        LeftistNode(Comparable &&e, LeftistNode *lt=nullptr,
        LeftistNode *rt=nullptr, int np=0)
        : element{ std::move(e) }, left{lt}, right{rt}, nlp{np} {}

    };
    LeftistNode *root;

    LeftistNode *merge(LeftistNode *h1, LeftistNode *h2);
    LeftistNode *merge1(LeftistNode *h1, LeftistNode *h2);

    void swapChildren(LeftistNode *t);
    void reclaimMemory(LeftistNode *t);
    LeftistNode *clone( LeftistNode *t) const;

};

int main()
{

    return 0;
}