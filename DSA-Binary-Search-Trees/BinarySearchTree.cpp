#include "BinarySearchTree.hpp"

template <typename T>
BinarySearchTree<T>::BinarySearchTree(){
    this->treeRoot = nullptr;
}

template <typename T>
BinarySearchTree<T>::BinarySearchTree(std::shared_ptr<BSTNode<T> > treeRoot){
    this->treeRoot.reset(treeRoot);
}

template <typename T>
BinarySearchTree<T>::~BinarySearchTree(){
    this->treeRoot.reset();
}

template <typename T>
std::shared_ptr<BSTNode<T> > BinarySearchTree<T>::insertNode(std::shared_ptr<BSTNode<T> > node, const T &value) {
    if(!node){
        node.reset(BSTNode<T>(value));
    } else if(value < node->value){
        node->left = insertNode(node->left, value);
    } else if(value > node->value){
        node->right = insertNode(node->right, value);
    } else if(value == node->value) 
        cout << "Key replication not permitted...\n";
    return node;
}

template <typename T>
std::shared_ptr<BSTNode<T> > BinarySearchTree<T>::deleteNode(std::shared_ptr<BSTNode<T> > node, const T &value){
    if(!node) return std::shared_ptr<BSTNode<T> >();
    if(value < node->value){
        node->left = deleteNode(node->left, value);
    } else if(value > node->value){
        node->right = deleteNode(node->right, value);
    } else if(value == node->value){
        if(height(node->left) > height(node->right)){
            std::shared_ptr<BSTNode<T> > pred = predecessor(node);
            node->value = pred->value;
            node->left = deleteNode(node->left, pred->value);
        } else {
            std::shared_ptr<BSTNode<T> > succ = successor(node);
            node->value = succ->value;
            node->right = deleteNode(node->right, succ->value);
        }
    }
    return node;
}

template <typename T>
void BinarySearchTree<T>::inorder(std::shared_ptr<BSTNode<T> > node){

    if(!node) return;

    inorder(node->left);
    std::cout << node->value << " ";
    inorder(node->right);
}

template <typename T>
void BinarySearchTree<T>::preorder(std::shared_ptr<BSTNode<T> > node){
    
    if(!node) return;

    std::cout << node->value << " ";
    preorder(node->left);
    preorder(node->right);
}

template <typename T>
void BinarySearchTree<T>::postorder(std::shared_ptr<BSTNode<T> > node){
    
    if(!node) return;

    postorder(node->left);
    postorder(node->right);
    std::cout << node->value << " ";
}

template <typename T>
void BinarySearchTree<T>::levelorder(std::shared_ptr<BSTNode<T> > node){
    std::queue<std::shared_ptr<BSTNode<T> > > treeNodes;
    std::cout << node->value << " ";
    treeNodes.push(node);
    while(!treeNodes.empty()){
        std::shared_ptr<BSTNode<T> > current = treeNodes.front();
        treeNodes.pop();
        if(current->left){
            std::cout << current->left << " ";
            treeNodes.push(current->left);
        }
        if(current->right){
            std::cout << current->right << " ";
            treeNodes.push(current->right);
        }
    }
}

template <typename T>
std::shared_ptr<BSTNode<T> > BinarySearchTree<T>::search(std::shared_ptr<BSTNode<T> > node, const T &value){
    if(!node) return std::shared_ptr<BSTNode<T> >();
    if(value == node->value) return node;
    else return (value < node->value ? search(node->left, value) : search(node->right, value) );
}

template <typename T>
int BinarySearchTree<T>::height(std::shared_ptr<BSTNode<T> > node){

    int x,y;
    if(!node) return 0;

    x = height(node->left);
    y = height(node->right);

    return (x>y) ? x+1 : y+1;

}

template <typename T>
int BinarySearchTree<T>::nodeCount(std::shared_ptr<BSTNode<T> > node) {

    int x,y;
    if(node){
        x = nodeCount(node->left);
        y = nodeCount(node->right);
        return x+y+1;
    }
    return 0;
}

template <typename T>
int BinarySearchTree<T>::internalNodeCount(std::shared_ptr<BSTNode<T> > node) {
    int x,y;
    if(node){
        x = nodeCount(node->left);
        y = nodeCount(node->right);
        return (node->left && node->right) ? x+y+1: x+y;
    }
    return 0;
}

template <typename T>
int BinarySearchTree<T>::leafCount(std::shared_ptr<BSTNode<T> > node){
     int x,y;
    if(node){
        x = nodeCount(node->left);
        y = nodeCount(node->right);
        return (!node->left && !node->right) ? x+y+1: x+y;
    }
    return 0;
}

template <typename T>
std::shared_ptr<BSTNode<T> > BinarySearchTree<T>::predecessor(std::shared_ptr<BSTNode<T> > current){
    current = current->left;
    while(current && current->right){
        current = current->right;
    }
    return current;
}

template <typename T>
std::shared_ptr<BSTNode<T> > BinarySearchTree<T>::successor(std::shared_ptr<BSTNode<T> > current){
    current = current->right;
    while(current && current->left){
        current = current->left;
    }
    return current;
}

template <typename T>
std::shared_ptr<BSTNode<T> > BinarySearchTree<T>::getRoot(){
    return this->treeRoot;
}

template<typename T>
void BinarySearchTree<T>::setRoot(std::shared_ptr<BSTNode<T> >& root){
    this->treeRoot = root;
}