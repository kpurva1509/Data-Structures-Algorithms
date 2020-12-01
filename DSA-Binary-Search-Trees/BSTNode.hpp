#include "headers.hpp"
#include "AbstractNode.hpp"

template<typename> class BinarySearchTree;

template<typename T>
class BSTNode {

    // std::forward for BST of custom objects
    T value;

    std::shared_ptr<BSTNode<T> > left;
    std::shared_ptr<BSTNode<T> > right;
    std::shared_ptr<BinarySearchTree<T> > tree;

public:
    BSTNode();
    BSTNode(const T& value);
    BSTNode(T&& _value);
    BSTNode(T&& _value, std::shared_ptr<BSTNode<T> > _left, std::shared_ptr<BSTNode<T> > _right);
    ~BSTNode();
    void setTree(std::shared_ptr<BinarySearchTree<T> > _tree);

    // to access private members of a node of a binary search tree
    friend class BinarySearchTree<T>;

    template<typename U, size_t size>
    friend std::shared_ptr<BinarySearchTree<U> > generateBSTfromPreorder(const U (&preorder)[size], int N);

    template<typename U, size_t size>
    friend std::shared_ptr<BinarySearchTree<U> > generateBSTfromPostorder(const U (&preorder)[size], int N);
};