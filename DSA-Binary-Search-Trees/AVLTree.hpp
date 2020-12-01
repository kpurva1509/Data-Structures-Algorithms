#include "headers.hpp"
#include "AVLNode.hpp"

template<typename T>
class AVLTree{

    std::shared_ptr<AVLNode<T> > tree;

public:
    AVLTree();
    AVLTree(std::shared_ptr<AVLNode<T> > tree);
    ~AVLTree();
    std::shared_ptr<AVLNode<T> > insertNode(std::shared_ptr<AVLNode<T> > node, const T& value);
    std::shared_ptr<AVLNode<T> > deleteNode(std::shared_ptr<AVLNode<T> > node, const T& value);

private:
    int getHeight(const std::shared_ptr<AVLNode<T> >& current);
    void rebalance(std::shared_ptr<AVLNode<T> >& current);
    void rebalanceLL(std::shared_ptr<AVLNode<T> >& current);
    void rebalanceLR(std::shared_ptr<AVLNode<T> >& current);
    void rebalanceRL(std::shared_ptr<AVLNode<T> >& current);
    void rebalanceRR(std::shared_ptr<AVLNode<T> >& current);
    signed int getBalanceFactor(const std::shared_ptr<AVLNode<T> >& current);
    std::shared_ptr<AVLNode<T> > predecessor(std::shared_ptr<AVLNode<T> > current);
    std::shared_ptr<AVLNode<T> > successor(std::shared_ptr<AVLNode<T> > current);

};