#include "utilities.hpp"

int main() {
    int preorder[] = {6,3,1,2,8,7,9};
    std::shared_ptr<BinarySearchTree<int> > treeFromPreorder = generateBSTfromPreorder<int, 7>(preorder, 7);
    treeFromPreorder->inorder(treeFromPreorder->getRoot());
    std::shared_ptr<BSTNode<int> > rootNode(new BSTNode<int>(6));
    BinarySearchTree<int> bst(rootNode);
    bst.insertNode(rootNode, 3);
    bst.insertNode(rootNode, 1);
    bst.insertNode(rootNode, 2);
    bst.insertNode(rootNode, 8);
    bst.insertNode(rootNode, 7);
    bst.insertNode(rootNode, 9);
    bst.insertNode(rootNode, 10);
    bst.inorder(rootNode);
}