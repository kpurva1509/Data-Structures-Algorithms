#include "headers.hpp"
#include "BinarySearchTree.hpp"
#include "AVLTree.hpp"
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <set>

/*******************************************************************/
// Operations
// https://www.geeksforgeeks.org/level-order-traversal-in-spiral-form-using-one-stack-and-one-queue/
// Custom iterator for a Binary Search tree
// Overload ++, --, <<, >>
// Generate BST from preorder
// Generate BST from postorder
// Generate balanced BST from inorder/SLL/DLL/array(sorted or unsorted)
// Serialize and Deserialize a BST
// Flatten a BST
// Print the BST in SPIRAL
// Invert a BST
// Diameter of a BST
// Lowest Common Ancestor(LCA) of a node
// All nodes k distance
// Count total unique BSTs - The nth Catalan #(Dynamic Programming)
// Test if the tree is SYMMETRIC
// Root to leaf path for all leaves (leaf to root alternative)
// Height balanced BST from a sorted array/SLL/DLL
// Floor and ceil in BST
// Distance between nodes in Binary tree
// CARTESIAN TREE????????????
// INVERT ALTERNATE LEVELS OF Binary Tree
// Coin distirbution in a BST
// Right/left view of a tree
// XOR Tree
// Vertically print the columns in a tree
// Cousins of a node
// Convert to DLL
// Double ended priority queue using self balancing BST
// Merge 2 BSTs with LIMITED EXTRA SPACE
// Find pair with given sum in BST
// IN PLACE conversion of sorted DLL to balanced BST
// Convert BST to Min-Heap / Max-Heap
// Swapping nodes in BST
// Threaded Binary Tree (Techie Delight)
// HUFFMAN CODING USING BINARY TREES
// OPTIMAL BINARY SEARCH TREES (DYNAMIC PROGRAMMING)
// MERKLE TREE(BLOCKCHAIN LIKE IMPLEMENTATION)
/*******************************************************************/

/*******************************************************************/
// Efficient approaches 
// 1. Recursion
// 2. Hashing
// 3. Iteration
// 4. Backtracking
/*******************************************************************/

/* Generate BST from preorder sequence - ITERATIVE */
template<typename T, size_t size>
std::shared_ptr<BinarySearchTree<T> > generateBSTfromPreorder(const T (&preorder)[size], int N) {
    
    /* passing an array by const reference to the function */
    std::stack<std::shared_ptr<BSTNode<T> > > backtrack;
    std::shared_ptr<BSTNode<T> > root = std::make_shared<BSTNode<T> >(preorder[0]);
    std::shared_ptr<BSTNode<T> > parent = root;
    std::shared_ptr<BinarySearchTree<T> > tree;
    tree->setRoot(root);
    int i = 1;
    while(i < N){
        T current = preorder[i];
        if(current < parent->value){
            std::shared_ptr<BSTNode<T> > new_node = std::make_shared<BSTNode<T> >(preorder[i++]);
            parent->left = new_node;
            backtrack.push(parent);
            parent = new_node;
        } else if(current > parent->value && current < backtrack.top()->value){
            std::shared_ptr<BSTNode<T> > new_node = std::make_shared<BSTNode<T> >(preorder[i++]);
            parent->right = new_node;
            parent = new_node;   
        } else {
            parent = backtrack.top();
            backtrack.pop();
        }
    }
    return tree;
}

/* Generate BST from preorder - RECURSIVE */
template<typename T>
std::shared_ptr<BSTNode<T> >& generateBSTfromPreorderRecursiveUtil(std::vector<T>& preorder_sequence, int&  start, int& end) {

    if(start > end) return std::shared_ptr<BSTNode<T> >();

    std::shared_ptr<BSTNode<T> > current = preorder_sequence[start];

    int i = start + 1;
    while(preorder_sequence[i] < current->value) i++;

    current->right = generateBSTfromPreorderRecursiveUtil(preorder_sequence, i, end);
    current->left = generateBSTfromPreorderRecursiveUtil(preorder_sequence, start+1, i-1);

    return current;    
}

template<typename T>
std::shared_ptr<BSTNode<T> >& generateBSTfromPreorderRecursive(std::vector<T>& preorder_sequence) {

    /* base condition check */
    if(preorder_sequence.empty()) return std::shared_ptr<BSTNode<T> >();

    /* give the min and the max index range */
    std::shared_ptr<BSTNode<T> > root = generateBSTfromPreorderRecursiveUtil(preorder_sequence, 0, preorder_sequence.size() - 1);
 
    return root;
}

template<typename T, size_t size>
void recursiveUtil(const T (&preorder)[size],  int start, int end){
    
    if(start>end) return;

    std::shared_ptr<BSTNode<T> > root = std::make_shared<BSTNode<T> >(preorder[end]);

    int i = end;
    while(preorder[i] > root->value){
        i--;
    }
    root->left = std::make_shared<BSTNode<T> >(preorder[i]);
    recursiveUtil<T, i-start>(preorder, start, i);
    root->right = std::make_shared<BSTNode<T> >(preorder[end-1]);
    recursiveUtil<T, end-i-1>(preorder, i+1, end-1);
}

// function template partial specialization is not allowed
// template <typename T>
// void recursiveUtil<0>(const T (&preorder)[],  int start, int end) {}

template<typename T, size_t size>
std::shared_ptr<BinarySearchTree<T> > generateBSTfromPostorder(const T (&preorder)[size], int N) {

    // std::shared_ptr<BSTNode<T> > root = std::make_shared<BSTNode<T> >(preorder[N-1]);
    int start = 0;
    int end = N-1;
    size_t size_inner = end - start +1;
    recursiveUtil<T, size_inner>(preorder, start, end);
}

template<typename T>
void printSpiral(const std::shared_ptr<BSTNode<T> >& treeRoot){

    std::stack<std::shared_ptr<BSTNode<T> > > evenLevelNodes;
    std::stack<std::shared_ptr<BSTNode<T> > > oddLevelNodes;
    std::cout << treeRoot->value << " ";
    evenLevelNodes.push(treeRoot);
    bool ltr = false; // true for even, false for odd level
    while(!evenLevelNodes.empty() || !oddLevelNodes.empty()){
        if(!ltr){
            while(!evenLevelNodes.empty()){
                std::shared_ptr<BSTNode<T> > current = evenLevelNodes.top();
                evenLevelNodes.pop();
                if(current->left) {
                    std::cout << current->left->value << " ";
                    oddLevelNodes.push(current->left);
                }
                if(current->right){
                    std::cout << current->right->value << " ";
                    oddLevelNodes.push(current->right);
                }
            }
        } else {
            while(!oddLevelNodes.empty()){
                std::shared_ptr<BSTNode<T> > current = oddLevelNodes.top();
                oddLevelNodes.pop();
                if(current->right) {
                    std::cout << current->right->value << " ";
                    evenLevelNodes.push(current->right);
                }
                if(current->left){
                    std::cout << current->left->value << " ";
                    evenLevelNodes.push(current->left);
                }
            }
        }
        ltr = !ltr;
    } 
}

template<typename T>
void printSpiralQueueStack(const std::shared_ptr<BSTNode<T> >& root){

    std::stack<std::shared_ptr<BSTNode<T> > > reverseprint;
    std::queue<std::shared_ptr<BSTNode<T> > > originalprint;
    std::cout << root->value << " ";
    originalprint.push(root);
    bool reverse = false;
    while(!originalprint.empty()) {

        int size = originalprint.size();

        while(size){
            std::shared_ptr<BSTNode<T> > current = originalprint.front();
            originalprint.pop();
            if(!reverse){
                if(current->left){
                    cout << current->left->value << " ";
                    originalprint.push(current->left);
                }
                if(current->right){
                    cout << current->right->value << " ";
                    originalprint.push(current->right);
                }
            } else {
                if(current->left){
                    // cout << current->left->value << " ";
                    originalprint.push(current->left);
                    reverseprint.push(current->left);
                }
                if(current->right){
                    // cout << current->right->value << " ";
                    originalprint.push(current->right);
                    reverseprint.push(current->right);
                }
            }
            size--;
        }
        if(reverse){
            while(!reverseprint.empty()){
                cout << reverseprint.top()->value << " ";
                reverseprint.pop();
            }
        }
        reverse = !reverse;
    }
}

/* generate BST from a sorted array */
/* array, and the start and end indices of the array */
template<typename T>
std::shared_ptr<BSTNode<T> > generateBSTfromArray(const T*& array, int start, int end){

    if(start>end) return std::shared_ptr<BSTNode<T> >();
    // if(start == end) return std::shared_ptr<BSTNode<T> >(array[start]);

    // prone to overflow
    // int mid = (end+start)/2;
    int mid = start + (end - start)/2;

    std::shared_ptr<BSTNode<T> > root(new BSTNode<T>(array[mid]));
    root->left = generateBSTfromArray(array, start, mid-1);
    root->right = generateBSTfromArray(array, mid+1,end);
    return root;
}

template<typename T>
void serializeUtil(std::vector<std::shared_ptr<BSTNode<T> > >& result, /*std::vector<std::shared_ptr<BSTNode<T> > >& backtrack,*/ std::shared_ptr<BSTNode<T> >& current){

    /* terminating recursion */
    if(!current){
        result.push_back(std::shared_ptr<BSTNode<T> >());
        return;
    }

    /* forward path */
    result.push_back(current);
    /* backtrack.push_back(current);*/
    serializeUtil(result, /*backtrack,*/ current->left);
    serializeUtil(result, /*backtrack,*/ current->right);

    /* return path, not required */
}

template<typename T>
std::vector<std::shared_ptr<BSTNode<T> > > serialize(const BinarySearchTree<T>& tree){

    /* prefix serialization via backtracking */
    std::shared_ptr<BSTNode<T> > root = tree.getRoot();
    std::vector<std::shared_ptr<BSTNode<T> > > serializedBST;
    std::vector<std::shared_ptr<BSTNode<T> > > backtrack;
    //serializedBST.push_back(root);
    recursiveUtil(serializedBST, /*backtrack,*/ root);

    return serializedBST;
}

template<typename T>
std::shared_ptr<BSTNode<T> > deserialize(std::vector<std::shared_ptr<BSTNode<T> > > serializedBST){

    if(serializedBST.empty()) return std::shared_ptr<BSTNode<T> >();
    if(serializedBST.front() == std::shared_ptr<BSTNode<T> >()) return std::shared_ptr<BSTNode<T> >();

    /* deserialize */    
    std::shared_ptr<BSTNode<T> > root = serializedBST.front();
    
    serializedBST.erase(serializedBST.begin());
    root->left = deserialize(serializedBST);
    
    serializedBST.erase(serializedBST.begin());
    root->right = deserialize(serializedBST);

    return root;

    // BinarySearchTree<T> bst;
    // bst.setRoot(root);
    // std::vector<std::shared_ptr<BSTNode<T> > > subvector(std::next(serializedBST.begin()), serializedBST.end());
    // typename std::vector<std::shared_ptr<BSTNode<T> > >::iterator it = std::next(serializedBST.begin());

}

template<typename T>
std::shared_ptr<BSTNode<T> > flattenBST_iterative(BinarySearchTree<T> bst) {
    
    std::shared_ptr<BSTNode<T> > root = bst->getRoot();
    std::shared_ptr<BSTNode<T> > parent = root;

    while(parent){
        if(parent->left){
            std::shared_ptr<BSTNode<T> > temp = parent->right;
            std::shared_ptr<BSTNode<T> > left = parent->left;
            while(left->right){
                left = left->right;
            }
            left->right = temp;
            parent->right = parent->left;
            parent->left = nullptr;
        }
        parent = parent->right;
    }
    return root;
}

template <typename T>
void flattenBST_recursive(BSTNode<T>& current){

    if(current == nullptr || (current->left == nullptr && current->right == nullptr)) return;

    if(current->left) {
        
        flattenBST_recursive(current->left);

        std::shared_ptr<BSTNode<T> > temp = current->right;
        current->right = current->left;
        current->left.reset();
        std::shared_ptr<BSTNode<T> > new_right = current->right;
        while(new_right->right){
            new_right = new_right->right;
        }
        new_right->right = temp;
    }

    flattenBST_recursive(current->right);

}

template<typename T>
int height(const BSTNode<T>& current, int& result){

    if(!current){
        result = 0;
        return 0;
    }
    int hl = height(current->left);
    int hr = height(current->right);

    result = std::max(result, hl+hr+1);

    return 1+std::max(hl,hr);
}

/**************RETURN THE END POINTS OF THE DIAMETER OF THE TREE**************/
/* Use a static diameter variable which compares value in recursive call to return max */
template<typename T>
int diameter(const BinarySearchTree<T>& bst) {
    int result = INT_MIN;
    int ht = height(bst->getRoot(), result);
    return result;
}

template<typename T>
void invertBST(std::shared_ptr<BSTNode<T> > root) {

    if(!root) return;

    std::swap(root->left, root->right);
    invertBST(root->left);
    invertBST(root->right);
    // std::swap(root->left, root->right);
}

template<typename T>
std::shared_ptr<BSTNode<T> > lowestCommonAncestor(const std::shared_ptr<BSTNode<T> >& current, const T& first, const T& second){

    if(!current) return std::shared_ptr<BSTNode<T> >();
    if(current->value == first || current->value == second) return current;

    std::shared_ptr<BSTNode<T> > leftSearch = lowestCommonAncestor(current->left, first, second);
    std::shared_ptr<BSTNode<T> > rightSearch = lowestCommonAncestor(current->right, first, second);

    if(leftSearch && !rightSearch){
        return leftSearch;
    } else if(!leftSearch && rightSearch){
        return rightSearch;
    } else if(leftSearch && rightSearch){
        return current;
    }
    return std::shared_ptr<BSTNode<T> >();
}

// Binary tree to undirected graph
// Binary tree with hashmap for fast lookup

template<typename T>
std::queue<std::shared_ptr<BSTNode<T> > > AllNodes_K_Distance(const std::shared_ptr<BSTNode<T> >& root, const std::shared_ptr<BSTNode<T> >& target, const int& distance){

    /* T should be comparable or have overloaded < operator */
    std::map<T, std::shared_ptr<BSTNode<T> > > parent;
    std::shared_ptr<BSTNode<T> > current = root;
    std::queue<std::shared_ptr<BSTNode<T> > > levelOrder;
    levelOrder.push(current);
    int node_count = 1;
    parent[root->value] = std::shared_ptr<BSTNode<T> >();

    while(!levelOrder.empty()){
        current = levelOrder.top();
        levelOrder.pop();
        /* parent[T] = std::shared_ptr<BSTNode<T> >(parent_node); */
        if(current->left){ 
            parent[current->left->value] = current;
            levelOrder.push(current->left);
            ++node_count;
        }
        if(current->right){
            parent[current->right->value] = current;
            levelOrder.push(current->right);
            ++node_count;
        }
    }

    int current_level = 0;
    bool visited[node_count];
    std::fill_n(visited, node_count, false);

    /* begin the level-order walkthrough from the target node */
    std::queue<std::shared_ptr<BSTNode<T> > > result;
    result.push(target);
    visited[target->value] = true;
    while(current_level != distance){
        /* to capture the size of each level */
        int size = result.size();
        while(size){
            current = result.top();
            result.pop();

            /* check for left child */
            if(current->left && !visited[current->left->value]){
                result.push(current->left);
                visited[current->left->value] = true;
            }

            /* check for right child */
            if(current->right && !visited[current->right->value]){
                result.push(current->right);
                visited[current->right->value] = true;
            }

            /* check for parent */
            if(parent.find(current->value) && !visited[parent[current->value]->value]){
                result.push(parent[current->value]);
                visited[parent[current->value]->value] = true;
            }

            --size;

        }
        ++current_level;
    }
    return result;
}

template<typename T>
void printPathsUtil(std::shared_ptr<BSTNode<T> >& current, int& pathLength, std::vector<T>& path){

    if(!current) return;

    if(current){
        path.push_back(current->value);
        pathLength++;
    }
    if(!current->left && !current->right){
        /* use reverse iterator(rbegin(), rend()) to print from leaf to root */
        for(typename std::vector<T>::iterator it = path.begin(); it!=path.end(); ++it){
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    } else {
        printPathsUtil(current->left, pathLength, path);
        printPathsUtil(current->right, pathLength, path);
    }
}

template<typename T>
void printPaths(const BinarySearchTree<T>& tree){

    std::shared_ptr<BSTNode<T> > root = tree.getRoot();
    int pathLength = 0;
    std::vector<T> path;
    printPathsUtil(root, pathLength, path);
}

template<typename T>
void printLeafToRootIterative(const std::shared_ptr<BSTNode<T> >& current, std::unordered_map<std::shared_ptr<BSTNode<T> >, std::shared_ptr<BSTNode<T> > > parent){
    std::shared_ptr<BSTNode<T> > leafNode = current;
    while(leafNode){
        std::cout << leafNode->value << " ";
        leafNode = parent[leafNode];
    }
}

template<typename T>
void iterativePostorder(const BinarySearchTree<T>& tree){

    std::shared_ptr<BSTNode<T> > current = tree->getRoot();
    std::stack<std::shared_ptr<BSTNode<T> > > track;
    std::stack<T> result;

    /* map to print leaf to root paths, ITERATIVELY */ 
    std::unordered_map<std::shared_ptr<BSTNode<T> >, std::shared_ptr<BSTNode<T> > > parent;
    parent[current] = std::shared_ptr<BSTNode<T> >();
    
    track.push(current);

    while(!track.empty()){
        current = track.top();
        track.pop();
        result.push(current->value);

        if(!current->left && !current->right) printLeafToRootIterative(current, parent);

        if(current->left){
            track.push(current->left);
            parent[current->left] = current;
        }
        if(current->right){ 
            track.push(current->right);
            parent[current->right] = current;
        }
    }

    /* Result to print the post-order traversal */
    while(!result.empty()){
        std::cout << result.top() << " ";
        result.pop();
    }
}

template<typename T>
int coinDistributionUtil(const std::shared_ptr<BSTNode<T> > current, int& ans){

    if(!current) return 0;

    /* postorder to process children then the current node */
    int left = coinDistributionUtil(current->left, ans);
    int right = coinDistributionUtil(current->right, ans);

    ans += abs(left) + abs(right);

    /* Every node returns an excess in its subtree rooted at current */
    return current->value + left + right - 1;
}

template<typename T>
int coinDistribution(BinarySearchTree<T>& tree){

    int ans = 0;
    coinDistributionUtil(tree->getRoot(), ans);
    return ans;
}

template<typename T>
int countChild(const std::shared_ptr<BSTNode<T> >& current){
    
    if(!current) return 0;

    int nodeCount = 0;
    int sum = 0;

    std::queue<std::shared_ptr<BSTNode<T> > > subTree;
    subTree.push(current);

    while(!subTree.empty()){

        std::shared_ptr<BSTNode<T> > curr = subTree.top();
        subTree.pop();
        nodeCount++;
        sum += curr->value;

        if(curr->left) subTree.push(curr->left);
        if(curr->right) subTree.push(curr->right);
    }
    return abs(nodeCount - sum);
}

template<typename T>
int coinDistributionIterative(const BinarySearchTree<T>& tree){

    std::shared_ptr<BSTNode<T> > root = tree.getRoot();
    if(!root) return 0;

    std::queue<std::shared_ptr<BSTNode<T> > > treeNodes;
    treeNodes.push(root);

    int moves = 0;

    while(!treeNodes.empty()){
        std::shared_ptr<BSTNode<T> > current = treeNodes.top();
        treeNodes.pop();

        moves += countChild(current->left);
        moves += countChild(current->right);

        if(current->left) treeNodes.push(current->left);
        if(current->right) treeNodes.push(current->right);

    }
    return moves;
}

/* Angled views of a Binary Tree(left, right, top, bottom) */
template<typename T>
void printBottomView(const BinarySearchTree<T>& tree){

    /* stores the final result in ordered fashion to be printed */
    std::map<int, std::shared_ptr<BSTNode<T> > > hashmap;
    hashmap[0] = tree.getRoot();

    /* stores the horizontal distance to iteratively assign to children */
    std::unordered_map<std::shared_ptr<BSTNode<T> >, int> hd;
    hd[tree->getRoot()] = 0;

    /* to traverse the tree in level order */
    std::queue<std::shared_ptr<BSTNode<T> > > treeNodes;
    treeNodes.push(tree->getRoot());

    while(!treeNodes.empty()){
        std::shared_ptr<BSTNode<T> > current = treeNodes.top();
        treeNodes.pop();

        if(current->left){
            hd[current->left] = hd[current] - 1;
            hashmap.insert_or_assign(hd[current->left], current->left);

            /* For top view, if we find an entry with given key in hashmap 
             * do not reassign the entry
             * 
             * if(!hashmap.find(hd[current->left])){
             *      hashmap[hd[current->left]] = current->left;
             * }
             * 
             */
        }

        if(current->right){
            hd[current->right] = hd[current] + 1;
            hashmap.insert_or_assign(hd[current->right], current->right);
        }
    }

    /* print ORDERED hashmap from left to right in increasing order of key */
    for(typename std::map<int, std::shared_ptr<BSTNode<T> > >::iterator it = hashmap.begin(); it!=hashmap.end(); ++it){
        std::cout << it->second->value << " ";
    }
    std::cout << std::endl;
}

template<typename T>
void printTopView(const BinarySearchTree<T>& tree) {

    std::shared_ptr<BSTNode<T> > root = tree.getRoot();
    if(!root) return;

    std::map<std::shared_ptr<BSTNode<T> >, int> hd_nodes;
    std::map<int, std::shared_ptr<BSTNode<T> > > horizontal_distance;

    hd_nodes[root] = 0;
    horizontal_distance[0] = root;

    std::queue<std::shared_ptr<BSTNode<T> > > treeNodes;
    treeNodes.push(root);

    while(!treeNodes.empty()) {
        std::shared_ptr<BSTNode<T> > current = treeNodes.top();
        treeNodes.pop();
        if(current->left){
            hd_nodes[current->left] = hd_nodes[current] - 1;
            if(horizontal_distance.find(hd_nodes[current->left]) == nullptr){
                horizontal_distance[hd_nodes[current->left]] = current->left;
            }
        }
        if(current->right){
            hd_nodes[current->right] = hd_nodes[current] + 1;
            if(horizontal_distance.find(hd_nodes[current->right]) == nullptr){
                horizontal_distance[hd_nodes[current->right]] = current->right;
            }
        }
    }
    
    /* print horizontal_distance map, least to greatest */
    for(typename std::map<int, std::shared_ptr<BSTNode<T> > >::iterator it = horizontal_distance.begin(); it != horizontal_distance.end(); ++it){
        std::cout << it->second->value << " ";
    }
}

template<typename T>
void printRightView(const BinarySearchTree<T>& tree){

    std::queue<std::shared_ptr<BSTNode<T> > > treeNodes;
    treeNodes.push(tree.getRoot());

    while(!treeNodes.empty()){

        int size = treeNodes.size();

        while(size){
            std::shared_ptr<BSTNode<T> > current = treeNodes.top();
            treeNodes.pop();

            /* size == 1 implies we are at the rightmost element */
            if(size == 1) std::cout << current->value << " ";

            if(current->left) treeNodes.push(current->left);
            if(current->right) treeNodes.push(current->right);

            size--;
        }
    }  
}

template<typename T>
void printLeftView(const BinarySearchTree<T>& tree){
    std::queue<std::shared_ptr<BSTNode<T> > > treeNodes;
    treeNodes.push(tree.getRoot());

    while(!treeNodes.empty()){

        int size = treeNodes.size();
        bool first = true;

        while(size){
            std::shared_ptr<BSTNode<T> > current = treeNodes.top();
            treeNodes.pop();

            /* first == true implies we are at the leftmost element */
            if(first){ 
                std::cout << current->value << " ";
                /* Set it to false for the remaining elements */
                first = false;
            }

            if(current->left) treeNodes.push(current->left);
            if(current->right) treeNodes.push(current->right);

            size--;
        }
    }
}

/* Print corners in all levels - combine left view and right view */
template<typename T>
void printCornerView(const BinarySearchTree<T>& tree){

    std::queue<std::shared_ptr<BSTNode<T> > > treeNodes;
    treeNodes.push(tree.getRoot());
    int level = 1;
    while(!treeNodes.empty()){
        
        std::cout << "Level " << level << " nodes: "; 
        int size = treeNodes.size();
        bool first = true;
        
        while(size){
            std::shared_ptr<BSTNode<T> > current = treeNodes.top();
            treeNodes.pop();

            if(first || size==1){
                std::cout << current->value << " ";
                first = false;
            }

            if(current->left) treeNodes.push(current->left);
            if(current->right) treeNodes.push(current->right);

            --size;
        }
        ++level;
    }
}

template<typename T>
void diagonalOrderTraversalUtil(std::shared_ptr<BSTNode<T> >& current, const int& diag, std::map<int, std::vector<std::shared_ptr<BSTNode<T> > > >& diagonal){

    if(!current) return;

    diagonal[diag].push_back(current);
    diagonalOrderTraversalUtil(current->left, diag, diagonal); /* for right diagonal, pass diag + 1 */
    diagonalOrderTraversalUtil(current->right, diag + 1, diagonal); /* for right diagonal, pass diag */
}

/* Diagonal traversal */
template<typename T>
void diagonalOrderTraversal(const BinarySearchTree<T>& tree){

    /* front-slash, right top to left bottom diagonal - LEFT DIAGONAL */
    std::map<int, std::vector<std::shared_ptr<BSTNode<T> > > > diagonal;
    diagonalOrderTraversalUtil(tree.getRoot(), 0, diagonal);

    /* print implementation */
    for (typename std::map<int, std::vector<std::shared_ptr<BSTNode<T> > > >::iterator it = diagonal.begin(); it != diagonal.end(); it++) {

        std::cout << "Elements of column " << it->first + 1 << " are: ";
        
        for(typename std::vector<std::shared_ptr<BSTNode<T> > >::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++){
            std::cout << it2->value << " ";
        }
        std::cout << std::endl;
    }
}

/* Vertical order traversal - using horizontal distance concept */
template<typename T>
void verticalOrderTraversal(const BinarySearchTree<T>& tree){

    std::queue<std::shared_ptr<BSTNode<T> > > treeNodes;
    treeNodes.push(tree.getRoot());
    std::map<int, std::vector<std::shared_ptr<BSTNode<T> > > > column_map;
    std::unordered_map<std::shared_ptr<BSTNode<T> >, int> hd;
    hd[tree.getRoot()] = 0;
    column_map[0].push_back(tree.getRoot());

    while(!treeNodes.empty()){
        std::shared_ptr<BSTNode<T> > current = treeNodes.top();
        treeNodes.pop();

        if(current->left){
            hd[current->left] = hd[current] - 1;
            column_map[hd[current->left]].push_back(current->left);
        }

        if(current->right){
            hd[current->right] = hd[current] + 1;
            column_map[hd[current->right]].push_back(current->right);
        }

    }

    /* printing the columns */
    int column_id = 1;
    for(typename std::map<int, std::vector<std::shared_ptr<BSTNode<T> > > >::iterator it = column_map.begin(); it!=column_map.end(); it++){
        
        std::cout << "Elements of column " << column_id << " are: ";
        
        for(typename std::vector<std::shared_ptr<BSTNode<T> > >::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++){
            std::cout << it2->value << " ";
        }
        ++column_id;
        std::cout << std::endl;
    }
}

/* Invert alternate levels */
template<typename T>
void invertAlternateLevels(BinarySearchTree<T>& tree){

    std::queue<std::shared_ptr<BSTNode<T> > > treeNodes;
    std::vector<std::shared_ptr<BSTNode<T> > > toBeinverted;
    treeNodes.push(tree.getRoot());
    bool invert = true;

    while(!treeNodes.empty()){
        
        int size = treeNodes.size();
        
        while(size){
            std::shared_ptr<BSTNode<T> > current = treeNodes.top();
            treeNodes.pop();

            if(invert){
                if(current->left){
                    treeNodes.push(current->left);
                    toBeinverted.push_back(current->left);
                }
                if(current->right){
                    treeNodes.push(current->right);
                    toBeinverted.push_back(current->right);
                }

            } else {
                if(current->left) treeNodes.push(current->left);
                if(current->right) treeNodes.push(current->right);
            }
            --size;
        }

        if(invert){
            for(typename std::vector<BSTNode<T> >::iterator start = toBeinverted.begin(), end = std::prev(toBeinverted.end()); start<end; ++start, --end){
                std::swap((*start)->value, (*end)->value);
            }
        }
        /* reset the vector*/
        toBeinverted.clear();

        /* flip the value of invert flag */
        invert = !invert;
    }
}

/* Print cousins of a node */
template<typename T>
void printNodeCousins(const BinarySearchTree<T>& tree, const std::shared_ptr<BSTNode<T> >& target){

    std::queue<std::shared_ptr<BSTNode<T> > > treeNodes;
    treeNodes.push(tree.getRoot());
    
    bool found = false;

    while(!treeNodes.empty() || !found){

        int size = treeNodes.size();

        while(size){
            std::shared_ptr<BSTNode<T> > current = treeNodes.top();
            treeNodes.pop();

            if(current->left == target || current->right == target) found = true;
            else {
                if(current->left) treeNodes.push(current->left);
                if(current->right) treeNodes.push(current->right);
            }
            size--;
        }
    }

    if(found){
        /* print the cousins from the treeNodes queue */
    } else std::cout << "Target not found...\n";
}

template<typename T>
bool isSibling(std::shared_ptr<BSTNode<T> >& parent, const std::shared_ptr<BSTNode<T> >& first, const std::shared_ptr<BSTNode<T> >& second) {

    if(!parent) return false;
    
    return ((parent->left == first && parent->right == second) ||
            (parent->right == first && parent->left == second) ||
            (isSibling(parent->left, first, second)) ||
            (isSibling(parent->right, first, second)));
}

template<typename T>
int level(std::shared_ptr<BSTNode<T> >& root, const std::shared_ptr<BSTNode<T> >& current, int& lev){
    if(!root) return 0;
    if(root == current) return lev;
    int left = level(root->left, current, lev+1);
    if(lev != 0) return lev;
    return level(root->right, current, lev);
}

/* to check if the two given nodes are cousins */
template<typename T>
bool areCousins(const BinarySearchTree<T>& tree, const std::shared_ptr<BSTNode<T> >& first, const std::shared_ptr<BSTNode<T> >& second) {

    /* The given nodes should be on the same level */
    /* The given nodes should not be siblings of each other */

    return(level(tree.getRoot(), first, 1) == level(tree.getRoot(),second,1) && !isSibling(tree.getRoot(), first, second));
}

/* count # of nodes in a tree rooted at the given node */
template<typename T>
int count(const std::shared_ptr<BSTNode<T> >& current){

    if(current) return count(current->left) + count(current->right) + 1;
    return 0;
}

/* return sum of elements in a tree rooted at the given node */
template<typename T>
int sum(const std::shared_ptr<BSTNode<T> >& current) {

    if(current) return current->value + sum(current->left) + sum(current->right);
    return 0;
}

/* Tilt of a Binary tree */
template<typename T>
int tilt(const std::shared_ptr<BSTNode<T> >& node) {

    static int sum = 0;

    /* if node is a null, or node is a leaf, return 0 */
    if(!node || (!node->left && !node->right)) return 0;

    /* Update sum in recursive calls */
    tilt(node->left);
    tilt(node->right);

    int leftSum = sum(node->left);
    int rightSum = sum(node->right);

    sum += abs(leftSum - rightSum);

    return sum;
}

template<typename T>
void boundaryTraversalLeft(const std::shared_ptr<BSTNode<T> >& current){

    /* if current is a null or current is a leaf(to avoid leaf duplication), return */
    if(!current || (!current->left && !current->right)) return;

    std::cout << current->value << " ";

    if(current->left) boundaryTraversalLeft(current->left);
    else if(current->right) boundaryTraversalLeft(current->right);

}

template<typename T>
void boundaryTraversalRight(const std::shared_ptr<BSTNode<T> >& current){

    if(!current || (!current->left && !current->right)) return;

    /* printing on return time for reverse order printing */
    if(current->right){
        boundaryTraversalRight(current->right);
        std::cout << current->value << " ";
    } else if(current->left){
        boundaryTraversalRight(current->left);
        std::cout << current->value << " ";
    }
}

template<typename T>
void boundaryTraversalLeaves(const std::shared_ptr<BSTNode<T> >& current){

    if(!current) return;

    boundaryTraversalLeaves(current->left);
    if(!current->left && !current->right) std::cout << current->value << " ";
    boundaryTraversalLeaves(current->right);
}

/* Boundary traversal in BST or BT - ANTICLOCKWISE MANNER */
template<typename T>
void boundaryTraversal(const BinarySearchTree<T>& tree){

    if(!tree.getRoot()) return;
    std::shared_ptr<BSTNode<T> > root = tree.getRoot();

    std::cout << root->value << " ";

    /* Left Boundary traversal */
    boundaryTraversalLeft(root->left);

    /* Print leaves on each level */
    boundaryTraversalLeaves(root->left);
    boundaryTraversalLeaves(root->right);

    /* Right boundary traversal */
    boundaryTraversalRight(root->right);

}

template<typename T>
void leftBoundary(const std::shared_ptr<BSTNode<T> >& current,  std::vector<std::shared_ptr<BSTNode<T> > >& boundaryNodes){

    if(!current) return;
    if(current) boundaryNodes.push_back(current);

    if(current->left){
        leftBoundary(current->left, boundaryNodes);
    } else if(current->right){
        leftBoundary(current->right, boundaryNodes);
    }
}

template<typename T>
void rightBoundary(const std::shared_ptr<BSTNode<T> >& current,  std::vector<std::shared_ptr<BSTNode<T> > >& boundaryNodes){

    if(!current) return;
    if(current) boundaryNodes.push_back(current);

    if(current->right){
        rightBoundary(current->right, boundaryNodes);
    } else if(current->left){
        rightBoundary(current->left, boundaryNodes);
    }
}

template<typename T>
T internalNodeSum(const std::shared_ptr<BSTNode<T> >& root, std::vector<std::shared_ptr<BSTNode<T> > >& boundaryNodes) {

    if(!root) return 0;

    T result = 0;
    std::queue<std::shared_ptr<BSTNode<T> > > treeNodes;
    treeNodes.push(root);

    while(!treeNodes.empty()){
        std::shared_ptr<BSTNode<T> > current = treeNodes.top();
        treeNodes.pop();

        if(!std::find(boundaryNodes.begin(), boundaryNodes.end(), current)){
            result += current->value;
        }

        if(current->left) treeNodes.push(current->left);
        if(current->right) treeNodes.push(current->right);
    }
    return result;
}

/* Sum of covered and uncovered nodes in BT */
template<typename T>
bool sumCoveredUncovered(const BinarySearchTree<T>& tree){

    if(!tree.getRoot()) return false;

    std::vector<std::shared_ptr<BSTNode<T> > > boundaryNodes;
    boundaryNodes.push_back(tree.getRoot());
    leftBoundary(tree.getRoot()->left, boundaryNodes);
    rightBoundary(tree.getRoot()->right, boundaryNodes);

    /* using template lambda for summation */
    T sumBoundaryNodes = accumulate(boundaryNodes.begin(), boundaryNodes.end(), 0,
                        [&]<typename T>(T value, const std::shared_ptr<BSTNode<T> >& current){
                            return value + current->value;
                        });
    
    T sumInternalNodes = internalNodeSum(tree.getRoot(), boundaryNodes);

    return (sumBoundaryNodes == sumInternalNodes);
}

/* Minimum # of cameras required to monitor all nodes in BT */
/* Leaf to Root - Bottom Up Approach */
template<typename T>
int minCameras(const BinarySearchTree<T>& tree){

    if(!tree.getRoot()) return 0;

    int count = 0;

    /* TO DO */ /* TO DO */ /* TO DO */ /* TO DO */

    return count;

}

/*******************************************************************/
// BST Questions
// Find k'th smallest and k'th largest in a binary tree
// Removing nodes from BST outside the given range
// Removing nodes from a BST from the given range
// Find pair with given sum in BST
// BST to DLL
// Merge 2 BST's into sorted DLL
// Find triplet with given sum
// BST to Min-heap
// Update every node in BST to contain sum of all greater elements
// Sums of nodes, traversals, etc
// Minimum swaps to convert BT to BST
// Skew in BT
// Unbalanced to balanced BST
// Distance between 2 nodes
// Width of a level in the tree
// Print path to a node in a BT
// Construct BT from Ancestor Matrix
// BST TO SLL in spiral level order
// Max-weight independent set in a tree (MWIS - DP)
// Max depth of BT
/*******************************************************************/

/* Find k'th smallest and k'th largest in a binary tree */
template<typename T>
T kthSmallestUtil(const std::shared_ptr<BSTNode<T> >& current, int& index, const int&k){

    if(!current) return INT_MAX;

    /* Recursive inorder traversal with index to track the element */
    T left = kthSmallestUtil(current->left, index,k);
    if(left != INT_MAX) return left;
   
    ++index;
    if(index == k) return current->value;

    return kthSmallestUtil(current->right, index, k);

}

template<typename T>
T kthSmallest(const BinarySearchTree<T>& tree, const int& k){
    int index = 0;
    return kthSmallestUtil(tree.getRoot(), index, k);
}

template<typename T>
T kthLargestUtil(const std::shared_ptr<BSTNode<T> >& current, int& index, const int& k){

    if(!current) return INT_MAX;

    /* Recursive reverse inorder from right to left  for k'th largest element */
    T right = kthLargestUtil(current->right, index, k);
    if(right != INT_MAX) return right;

    ++index;
    if(index == k) return current->value;

    return kthLargestUtil(current->left, index,k);
}

template<typename T>
T kthLargest(const BinarySearchTree<T>& tree, const int& k){
    int index = 0;
    return kthLargestUtil(tree.getRoot(), index, k);
}

/* Removing nodes from BST outside the given range */
template<typename T>
std::shared_ptr<BSTNode<T> > removeOutsideRange(std::shared_ptr<BSTNode<T> >& root, int min, int max){

    if(!root) return std::shared_ptr<BSTNode<T> >();

    /* postorder evaluation */
    root->left = removeOutsideRange(root->left, min, max);
    root->right = removeOutsideRange(root->right, min, max);

    if(root->value < min){
        std::shared_ptr<BSTNode<T> > right_child = root->right;
        root.reset();
        return right_child;
    }
    if(root->value > max){
        std::shared_ptr<BSTNode<T> > left_child = root->left;
        root.reset();
        return left_child;
    }
    return root;
}

/* Removing nodes from a BST from the given range */
template<typename T>
std::shared_ptr<BSTNode<T> > removeFromRange(std::shared_ptr<BSTNode<T> >& root, int min, int max){

    if(!root) return std::shared_ptr<BSTNode<T> >();

    root->left = removeFromRange(root->left, min, max);
    root->right = removeFromRange(root->righr, min, max);

    if(root->value >= min && root->value <= max){
        /* delete with inorder successor replacement */
    }
    return root;
}

/* Find pair with given sum in BST - by HASHING & INORDER Traversal */

template<typename T>
bool findPair(const std::shared_ptr<BSTNode<T> >& current, const T& target, std::unordered_set<T>& hash_set){

    if(!current) return false;
    
    if(findPair(current->left, target, hash_set)) return true;

    if(hash_set.find(target - current->value) != hash_set.end()) {
        std::cout << "Pair found for target: " << target << " as (" << current->value << ", " << target-current->value << ")\n";
        return true;
    }
    hash_set.insert(current->value);

    return findPair(current->right, target, hash_set);
}

template<typename T>
void inorderUtil(const std::shared_ptr<BSTNode<T> >& current, std::vector<std::shared_ptr<BSTNode<T> > >& inorder_sequence){

    if(!current) return;

    inorderUtil(current->left, inorder_sequence);
    inorder_sequence.push_back(current);
    inorderUtil(current->right, inorder_sequence);
}

/* Find triplet with given sum - Non Modifying BST */
template<typename T>
bool tripletSum_NonModifying_BST(const BinarySearchTree<T>& tree, const T& target) {

    if(!tree.getRoot()) return false;
    
    std::shared_ptr<BSTNode<T> > root = tree.getRoot();
    std::vector<BSTNode<T> > inorder_sequence;
    inorderUtil(root, inorder_sequence);

    int size = inorder_sequence.size();

    for(int i=0; i < size-2; i++){
        
        int low = i+1;
        int high = size - 1;
        
        /* using hashing in the inner loop */
        int k = target - inorder_sequence[i];
        
        while(low < high){
            if(inorder_sequence[low]+ inorder_sequence[high] < k) low++;
            else if(inorder_sequence[low]+ inorder_sequence[high] > k) high--;
            else {
                std::cout << "Found triplet with given sum " << target << " as " << inorder_sequence[i] << ", " << inorder_sequence[low] << ", " << inorder_sequence[high] << std::endl;
                return true;
            }
        }
    }
    return false;
}

/* BST to DLL */
template<typename T>
std::shared_ptr<BSTNode<T> > BSTtoDLLUtil(std::shared_ptr<BSTNode<T> >& current){

    if(!current) return std::shared_ptr<BSTNode<T> >();

    if(current->left){
        std::shared_ptr<BSTNode<T> > left = BSTtoDLLUtil(current->left);
        /* update right link of inorder predecessor */
        while(left->right) left = left->right;
        left->right = current;
        current->left = left;
    }
    if(current->right){
        std::shared_ptr<BSTNode<T> > right = BSTtoDLLUtil(current->right);
        /* update left link of inorder successor */
        while(right->left) right = right->left;
        right->left = current;
        current->right = right;
    }

    return current;
}

/* BT to DLL using previous and next pointers */
template<typename T>
void fixPrevPointer(std::shared_ptr<BSTNode<T> >& current) {

    if(!current) return;

    /* Static shared pointer to previous node, instatiated only once 
    Same prev will be used in recursive calls and updated
    */
    static std::shared_ptr<BSTNode<T> > prev;

    /* updating left link by keeping a tracking of previous using static variable */
    if(current){
        fixPrevPointer(current->left);
        current->left = prev;
        prev = current;
        fixPrevPointer(current->right);
    }

}

template<typename T>
std::shared_ptr<BSTNode<T> > fixNextPointer(std::shared_ptr<BSTNode<T> >& current) {

    /* updating right link */
    while(current && current->right) current = current->right;

    std::shared_ptr<BSTNode<T> > next;

    while(current && current->left){

        next = current;
        current = current->left;
        current->right = next;

    }
    return current;
}


template<typename T>
std::shared_ptr<BSTNode<T> > BSTtoDLL_Pointers(BinarySearchTree<T>& tree) {

    std::shared_ptr<BSTNode<T> > root = tree.getRoot();
    if(!root) return std::shared_ptr<BSTNode<T> >();

    fixPrevPointer(root);

    return fixNextPointer(root);

}

template<typename T>
std::shared_ptr<BSTNode<T> > BSTtoDLL(BinarySearchTree<T>& tree){
    
    std::shared_ptr<BSTNode<T> > root =  tree.getRoot();
    BSTtoDLLUtil(root);
   
    /* To get the head of the DLL */
    while(root->left) root = root->left;
   
    return root;
}

/* Find triplet with given sum - BST TO DLL - NO AUXILLARY SPACE */
template<typename T>
bool tripletSum_Modifying_BST(const std::shared_ptr<BSTNode<T> >& current, const T& target, std::unordered_set<T>& hash_set) {

}

template<typename T>
void postorderUtil(const std::shared_ptr<BSTNode<T> >& current, std::vector<std::shared_ptr<BSTNode<T> > >& postorder_sequence){

    if(!current) return;
    postorderUtil(current->left);
    postorderUtil(current->right);
    postorder_sequence.push_back(current);
}

/* Return max-weight independent set in a BT - ITERATIVE */
template<typename T>
void MWIS(const BinarySearchTree<T>& tree){

    std::shared_ptr<BSTNode<T> > root = tree.getRoot();
    if(!root) return;
    std::vector<std::shared_ptr<BSTNode<T> > > postorder_sequence;
    postorderUtil(root, postorder_sequence);

    int n = postorder_sequence.size();

    /*
    std::vector<int> MIS;
    MIS.reserve(n);
    std::fill_n(MIS.begin(), MIS.end(), 0);

    
    for(typename std::vector<std::shared_ptr<BSTNode<T> > >::iterator it = postorder_sequence.begin(); it != postorder_sequence.end(); ++it)

    for(int i=0; i<n; ++i){
        MIS[i] = std::max(

            (postorder_sequence[i]->left->value + postorder_sequence[i]->right->value),

            (postorder_sequence[i]->value + postorder_sequence[i]->left->left->value + postorder_sequence[i]->left->right->value + postorder_sequence[i]->right->left->value + postorder_sequence[i]->right->right->value)
            );
    }
    int max_weight = MIS.back(); 
    */

    std::unordered_set<std::shared_ptr<BSTNode<T> > > optimal_set;
    optimal_set.reserve(n);
    std::map<std::shared_ptr<BSTNode<T> >, int> MIS_MAP;

    for(int i = 0; i < n; i++) {

        int cost_without_i = MIS_MAP[postorder_sequence[i]->left] +
                             MIS_MAP[postorder_sequence[i]->right];

        int cost_with_i = postorder_sequence[i]->value + 
            MIS_MAP[postorder_sequence[i]->left->left] + 
            MIS_MAP[postorder_sequence[i]->left->right] + 
            MIS_MAP[postorder_sequence[i]->right->left] + 
            MIS_MAP[postorder_sequence[i]->right->right];
        

        MIS_MAP[postorder_sequence[i]] = fmax(cost_without_i,cost_with_i);

        if(cost_with_i > cost_without_i){
            /* push current node - postorder_sequence[i] */
            /* push grandchildren of current node */
            /* remove children of current node */
            optimal_set.insert(postorder_sequence[i]);
            if(postorder_sequence[i]->left->left) optimal_set.insert(postorder_sequence[i]->left->left);
            if(postorder_sequence[i]->left->right) optimal_set.insert(postorder_sequence[i]->left->right);
            if(postorder_sequence[i]->right->left) optimal_set.insert(postorder_sequence[i]->right->left);
            if(postorder_sequence[i]->right->right) optimal_set.insert(postorder_sequence[i]->right->right);
            if(postorder_sequence[i]->left) optimal_set.erase(postorder_sequence[i]->left);
            if(postorder_sequence[i]->right) optimal_set.erase(postorder_sequence[i]->right);
        } else {
            /* do not push current node - postorder_sequence[i] */
            /* push children of current node */
            /* remove grandchildren of current node from set */
            if(postorder_sequence[i]->left) optimal_set.insert(postorder_sequence[i]->left);
            if(postorder_sequence[i]->right) optimal_set.insert(postorder_sequence[i]->right);
            if(postorder_sequence[i]->left->left) optimal_set.erase(postorder_sequence[i]->left->left);
            if(postorder_sequence[i]->left->right) optimal_set.erase(postorder_sequence[i]->left->right);
            if(postorder_sequence[i]->right->left) optimal_set.erase(postorder_sequence[i]->right->left);
            if(postorder_sequence[i]->right->right) optimal_set.erase(postorder_sequence[i]->right->right);
        }
    }
    
    std::cout << "List of tree nodes forming an optimal Maximum Weight Independent Set(MWIS) are as follows: \n";
    for(typename std::unordered_set<std::shared_ptr<BSTNode<T> > >::iterator it = optimal_set.begin(); it != optimal_set.end(); ++it){
        std::cout << (*it)->value << " ";
    }

    int max_weight = MIS_MAP[root];

    std::cout << "\nWeight of the set is " << max_weight << "\n";
}

/* Return max-weight independent set in a BT - RECURSIVE */
template<typename T>
int MWIS_RECURSIVE(const std::shared_ptr<BSTNode<T> >& current) {

    /* if current is a nullptr */
    if(!current) return 0;

    /* if current is a leaf node */
    if(!current->left && !current->right) return current->value;

    int without_current = MWIS_RECURSIVE(current->left) + MWIS_RECURSIVE(current->right);

    int with_current = current->value;
    if(current->left) with_current += MWIS_RECURSIVE(current->left->left) + MWIS_RECURSIVE(current->left->right);
    if(current->right) with_current += MWIS_RECURSIVE(current->right->left) + MWIS_RECURSIVE(current->right->right);

    return fmax(without_current, with_current);
}

/* Binary Tree to DLL in Spiral Order */
template<typename T>
void BTtoDLL_Spiral(BinarySearchTree<T>& tree) {

    std::shared_ptr<BSTNode<T> > root = tree.getRoot();
    if(!root) return;

    std::map<int, std::vector<std::shared_ptr<BSTNode<T> > > > nodeLevels;
    std::queue<std::shared_ptr<BSTNode<T> > > treeNodes;
    treeNodes.push(root);
    int level = 0;

    /* creating a map with a vector of nodes at each level */
    while(!treeNodes.empty()){

        int size = treeNodes.size();
        while(size){
            std::shared_ptr<BSTNode<T> > current = treeNodes.top();
            treeNodes.pop();
            
            nodeLevels[level].push_back(current);

            if(current->left) treeNodes.push(current->left);
            if(current->right) treeNodes.push(current->right);
            size--;
        }
        ++level;
    }

    /* updating links in each level */
    for(typename std::map<int, std::vector<std::shared_ptr<BSTNode<T> > > >::iterator it = nodeLevels.begin(); it != nodeLevels.end();){
        
        /* process each level */
        bool reverse = (it->first % 2 == 0);
        
        typename std::vector<std::shared_ptr<BSTNode<T> > >::iterator it2 = it->second.begin();
        for(; it2 != it->second.end(); ++it2){
            if(reverse){
                (*it2)->left = *(std::next(it2));
                (*it2)->right = *(std::prev(it2));
            } else {
                (*it2)->right = *(std::next(it2));
                (*it2)->left = *(std::prev(it2));
            }
        }

        ++it;
        if(reverse){ /* Reversing on even levels */
            /* next of first node in even row points to first node in odd row */
            typename std::vector<std::shared_ptr<BSTNode<T> > >::iterator it2 = std::prev(it)->second.begin();
            (*it2)->right = *((*it)->second.begin());
            *((*it)->second.begin())->left = (*it2);
        } else { /* Not reversing on odd levels */
            *(std::prev(it2))->right = *(std::prev((*it)->second.end()));
            *(std::prev((*it)->second.end()))->left = *(std::prev(it2));
        }
    }
}

template<typename T>
inline bool isLeaf(const std::shared_ptr<BSTNode<T> >& current){
    return (current && !current->left && !current->right);
}

/* Minimum dominating set for trees - ITERATIVE */
template<typename T>
int MDS_DP(const BinarySearchTree<T>& tree) {

    std::shared_ptr<BSTNode<T> > root = tree.getRoot();
    if(!root) return 0;
    std::vector<std::shared_ptr<BSTNode<T> > > postorder_sequence;
    postorderUtil(root, postorder_sequence);

    int n = postorder_sequence.size();   

    /* Allocate array to store OPT(vi, pi, cp) values */
    /* OPT[BSTNODE_POINTER][pi][cp] */
    std::map<std::shared_ptr<BSTNode<T> >, std::map<std::pair<int, int>, int> > OPT;

    for(int i = 0; i < n; i++){

        std::shared_ptr<BSTNode<T> > current = postorder_sequence[i];
        
        if(isLeaf(current)){
            /* base case for leaf nodes */
            OPT[current][0][0] = 1;
            OPT[current][1][0] = 0;
            OPT[current][0][1] = 1;
        } else {
            /* DP equations */
            OPT[current][0][0] = min(1 + OPT[current->left][1][0] + OPT[current->right][1][0],
                                     min(OPT[current->left][0][1], OPT[current->right][0][1]) +
            ((OPT[current->left][0][1] < OPT[current->right][0][1]) ? OPT[current->right][0][0] : OPT[current->left][0][0]));
            
            OPT[current][1][0] = min(1 + OPT[current->left][1][0] + OPT[current->right][1][0],
                                    OPT[current->left][0][0] + OPT[current->right][0][0]);
           
            OPT[current][0][1] = 1 + OPT[current->left][1][0] + OPT[current->right][1][0];
        }
    }

    return min(OPT[root][0][0], min(OPT[root][0][1], OPT[root][1][0]));
}

/* Depth of a node in BT */
template<typename T>
int depthUtil(const std::shared_ptr<BSTNode<T> >& current, const T& target, int level){

    if(!current) return 0;

    if(current->value == target) return level;

    int leftLevel = depthUtil(current->left, target, level+1);
    if(leftLevel != 0) return leftLevel;

    return depthUtil(current->right, target, level+1);
}

template<typename T>
int depth(const BinarySearchTree<T>& tree, const std::shared_ptr<BSTNode<T> >& target) {

    std::shared_ptr<BSTNode<T> > root = tree.getRoot();
    if(!root) return -1;

    return depthUtil(root, target, 0);
}

/* Distance between 2 nodes in BT */
template<typename T>
int distance(const BinarySearchTree<T>& tree, const std::shared_ptr<BSTNode<T> >& first, const std::shared_ptr<BSTNode<T> >& second) {

    std::shared_ptr<BSTNode<T> > lca = lowestCommonAncestor(first, second);

    int firstDist = depthutil(lca, first, 0);
    int secondDist = depthUtil(lca, second, 0);

    return firstDist + secondDist;
}

/* Root to leaf path with given sum */
template<typename T>
void pathSumUtil(const std::shared_ptr<BSTNode<T> >& current, const int& sum, bool flag){

    if(!current){
        if(sum == 0) flag = true;
        return;
    }

    if(sum - current->value == 0 && isLeaf(current)) {
        flag = true;
        return;
    }

    pathSumUtil(current->left, sum - current->value, flag);
    pathSumUtil(current->right, sum - current->value, flag);
}

template<typename T>
bool pathSum(const BinarySearchTree<T>& tree, const int& sum){

    std::shared_ptr<BSTNode<T> > root = tree.getRoot();
    if(!root) return false;

    bool flag = false;
    pathSumUtil(root, sum, flag);
    return flag;
}

/* Print all paths with target sum from root */
template<typename T>
void allPathsWithTargetSumUtil(const std::shared_ptr<BSTNode<T> >& current, const int& target, int& trackingSum, std::vector<T>& path) {

    if(!current) return;

    trackingSum += current->value;
    path.push_back(current->value);
    if(trackingSum == target) {
        for(typename std::vector<T>::iterator it = path.begin(); it!=path.end(); ++it){
            std::cout << *it << " ";
        }
    }

    if(current->left) allPathsWithTargetSumUtil(current->left, target, trackingSum, path);
    if(current->right) allPathsWithTargetSumUtil(current->right, target, trackingSum, path);
}

template<typename T>
void allPathsWithTargetSum(const BinarySearchTree<T>& tree, const int& sum){
    
    std::shared_ptr<BSTNode<T> > root = tree.getRoot();
    if(!root) return;
    int trackingSum = 0;
    std::vector<T> path;
    path.reserve(100);
    allPathsWithTargetSumUtil(root, sum, trackingSum, path);
}

/* Print all paths with given target sum from any node to any node(top-down) */
template<typename T>
void printTopDownPathsutil(const std::shared_ptr<BSTNode<T> >& current, const int& target, int& trackingSum, std::vector<T>& path) {

    if(!current) return;

    trackingSum += current->value;
    path.push_back(current->value);
    if(trackingSum == target){
        for(typename std::vector<T>::iterator it = path.begin(); it!=path.end(); ++it){
            std::cout << *it << " ";
        }
    }

    if(current->left) printTopDownPathsutil(current->left, target, trackingSum, path);
    if(current->right) printTopDownPathsutil(current->right, target, trackingSum, path);

}

template<typename T>
void printTopDownPaths(const BinarySearchTree<T>& tree, const int& target) {

    std::shared_ptr<BSTNode<T> > root = tree.getRoot();
    if(!root) return;

    std::queue<std::shared_ptr<BSTNode<T> > > treeNodes;
    treeNodes.push(root);
    std::vector<T> path;
    path.reserve(100);

    while(!treeNodes.empty()){
        std::shared_ptr<BSTNode<T> > current = treeNodes.top();
        treeNodes.pop();

        int trackingSum = 0;
        printTopDownPathsUtil(current, target, trackingSum, path);
        path.clear();

        if(current->left) treeNodes.push(current->left);
        if(current->right) treeNodes.push(current->right);

    }
}

/* Subtree sum */
template<typename T>
int subtreeSumUtil(const std::shared_ptr<BSTNode<T> >& current, const int& target) {

    if(!current) return 0;

    int left = subtreeSumUtil(current->left, target);
    int right = subtreeSumUtil(current->right, target);

    int currentSum = current->value + left + right;
    if(currentSum == target) /*printSubtree(current);*/ std::cout << "Yes\n";
    
    return currentSum;
}

template<typename T>
void subtreeSum(const BinarySearchTree<T>& tree, const int& target) {

    std::shared_ptr<BSTNode<T> > root = tree.getRoot();
    if(!root) return;
    int trackingSum = 0;
    subtreeSumUtil(root, target);
}

/* Sum of nodes at the maximum level in a BT */
template<typename T>
void sumOfMaxDepthUtil(std::shared_ptr<BSTNode<T> >& current, const int& level, int& sum) {

    if(!current) return;

    static int max_level = INT_MIN;

    if(level > max_level){
        max_level = level;
        sum = current->value;
    }

    if(level == max_level) sum += current->value;

    if(current->left) sumOfMaxDepth(current->left, level+1, sum);
    if(current->right) sumOfMaxDepth(current->right, level+1, sum);

}

template<typename T>
void sumOfMaxDepth(const BinarySearchTree<T>& tree) {

    std::shared_ptr<BSTNode<T> > root = tree.getRoot();
    if(!root) return;
    int level = 0;

    sumOfMaxDepthUtil(root, level, sum);
}

/* Max spiral sum of a BT */
template<typename T>
int maxSpiralSum(const BinarySearchTree<T>& tree) {

    std::shared_ptr<BSTNode<T> > root = tree.getRoot();
    if(!root) return 0;

    std::stack<std::shared_ptr<BSTNode<T> > > evenLevelNodes;
    std::stack<std::shared_ptr<BSTNode<T> > > oddLevelNodes;
    std::vector<T> values;
    values.reserve(100);
    
    evenLevelNodes.push(root);
    bool reverse = false;
    
    while(!evenLevelNodes.empty() || !oddLevelNodes.empty()){

        if(!reverse){
            while(!evenLevelNodes.empty()){
                std::shared_ptr<BSTNode<T> > current = evenLevelNodes.top();
                evenLevelNodes.pop();
                values.push_back(current->value);

                if(current->left) oddLevelNodes.push(current->left);
                if(current->right) oddLevelNodes.push(current->right);
            }
        } else {
            while(!oddLevelNodes.empty()){
                std::shared_ptr<BSTNode<T> > current = oddLevelNodes.top();
                oddLevelNodes.pop();
                values.push_back(current->value);

                if(current->right) oddLevelNodes.push(current->right);
                if(current->left) oddLevelNodes.push(current->left);   
            }
        }
        reverse = !reverse;
    }

    /* Applying Kadane's Dynamic Programming Approach to get the max sum sub-array */
    std::vector<T> maxCurrentIndexSum;
    maxCurrentIndexSum.reserve(values.size());
    maxCurrentIndexSum.push_back(values.at(0));

    std::vector<T> backpointer_index;
    backpointer_index.reserve(values.size());
    /* if a new sequence starts @ current i, backpointer is -1 */
    backpointer_index[0] = -1;

    for(int i=1; i < values.size(); i++) {
        maxCurrentIndexSum[i] = std::max(values[i], maxCurrentIndexSum[i-1] + values[i]);
        backpointer_index[i] = (values[i] > maxCurrentIndexSum[i - 1] + values[i]) ? -1 : i-1;
    }

    // use a do while
    int max_value_index = std::distance(maxCurrentIndexSum.begin(), std::max_element(maxCurrentIndexSum.begin(), maxCurrentIndexSum.end()));
    int i = max_value_index +1;
    do {
        --i;
        std::cout << values[i] << " ";
        // i--;
    } while(backpointer_index[i] != -1);
    
}

/* Optimal COST to construct BST */
template<typename T>
int rangeSum(const std::vector<int>& frequency, int start, int end){

    int sum = 0;
    for(int i = start; i <= end; i++) sum += frequency[i];
    return sum;
}

template<typename T>
int optimalCost(const std::vector<T>& key, const std::vector<int>& frequency){

    /* declaring a nxn cost matrix */
    /* assuming the key vector is in a sorted order of the key values */
    int n = key.size();
    std::vector<std::vector<int> > cost(n, std::vector<int>(n, (int)0));

    for(int i=0; i<n; i++) cost[i][i] = frequency[i];

    /* Considering increasing length for each row */
    for(int L = 2; L <= n; L++){

        /* Initializing the row index in the memoization matrix */
        for(int row = 0; row < n - L + 1; row++){
            /* initializing the column for the length count */
            int col = row + L - 1;
            cost[row][col] = INT_MAX;
            /* Iterate and evaluate cost bby making each element as head */
            for(int k = row; k <= col; k++){
                int c = ((k > row) ? cost[row][k-1] : 0) + 
                        ((k < col) ? cost[k+1][col] : 0 )+ 
                        (rangeSum<T>(frequency, row, col));
                if(c < cost[row][col]) cost[row][col] = c;
            }
        }
    }
    return cost[0][n-1];
}

/* Construct optimal BST by bactracking on solution space */

/* Sum of nodes at minimum level */
template<typename T>
int minLevelSum(const BinarySearchTree<T>& tree) {

    std::shared_ptr<BSTNode<T> > root = tree.getRoot();
    if(!root) return -1;

    std::queue<std::shared_ptr<BSTNode<T> > > treeNodes;
    treeNodes.push(root);    
    bool found = false;
    int sum = 0;

    while(!treeNodes.empty() || !found) {
        
        int size = treeNodes.size();
        
        while(size){
            std::shared_ptr<BSTNode<T> > current = treeNodes.top();
            treeNodes.pop();

            if(!current->left && !current->right){
                found = true;
                sum += current->value;
            } else {
                if(current->left) treeNodes.push(current->left);
                if(current->right) treeNodes.push(current->right);
            }
            --size;
        }
    }
    return sum;
}

/* Level order traversal using Morris Preorder traversal */
template<typename T>
void preorderMorris(const std::shared_ptr<BSTNode<T> >& current, const int& level, std::map<int, std::vector<std::shared_ptr<BSTNode<T> > > >& treeNodes) {

    if(!current) return;

    treeNodes[level].push_back(current);
    preorderMorris(current->left, level + 1, treeNodes);
    preorderMorris(current->right, level + 1, treeNodes);
}

template<typename T>
void levelOrderMorris(const BinarySearchTree<T>& tree) {

    std::shared_ptr<BSTNode<T> > root = tree.getRoot();
    if(!root) return;

    std::map<int, std::vector<std::shared_ptr<BSTNode<T> > > > treeNodes;
    // treeNodes[0].push_back(root);
    int level = 0;
    preorderMorris(root, level, treeNodes);

    for (typename std::map<int, std::vector<std::shared_ptr<BSTNode<T> > > >::iterator it = treeNodes.begin(); it != treeNodes.end(); it++) {

        std::cout << "Elements of level " << it->first + 1 << " are: ";
        
        for(typename std::vector<std::shared_ptr<BSTNode<T> > >::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++){
            std::cout << it2->value << " ";
        }
        std::cout << std::endl;
    }
}

/*********************************************************/
/*        MORRIS TRAVERSAL & THREADED BINARY TREES       */
/*********************************************************/


template<typename T>
struct SingleThreadedBSTNode {

    T value;
    std::shared_ptr<SingleThreadedBSTNode<T> > left;
    std::shared_ptr<SingleThreadedBSTNode<T> > right;

    /* used to indicate if the right pointer is a threaded 
     * link to sucessor or a normal right pointer 
     */
    bool isThreaded;
};

template<typename T>
std::shared_ptr<SingleThreadedBSTNode<T> > leftMost(std::shared_ptr<SingleThreadedBSTNode<T> >& current){

    while(current && current->left) current = current->left;
    return current;
}

template<typename T>
std::shared_ptr<SingleThreadedBSTNode<T> > createSingleThreadedBST(std::shared_ptr<SingleThreadedBSTNode<T> >& current) {

    /* Base case if root is nullptr or only single node exists */
    if(!current) return std::shared_ptr<SingleThreadedBSTNode<T> >();
    if(!current->left && !current->right) return current;

    /* Recursively process the nodes in INORDER fashion */

    if(current->left){
        std::shared_ptr<SingleThreadedBSTNode<T> > l = createSingleThreadedBST(current->left);
        if(l){
            l->right = current;
            l->isThreaded = true;
        }
    }
    if(!current->right) return current;
    return createSingleThreadedBST(current->right);
}

template<typename T>
void inorderTraversalThreadedBST(const std::shared_ptr<SingleThreadedBSTNode<T> >& current) {

    if(!current) return;

    std::shared_ptr<SingleThreadedBSTNode<T> > left = leftMost(current);
    while(current){
        std::cout << current->value << " ";
        if(current->isThreaded) current = current->right; /* implies leaf node */
        else {
            current = leftMost(current->right);
        }
    }
}

template <typename T>
struct DoubleThreadedBSTNode
{

    T value;
    std::shared_ptr<DoubleThreadedBSTNode<T> > left;
    std::shared_ptr<DoubleThreadedBSTNode<T> > right;

    /* used to indicate if the left and right pointers are 
     * threaded link to sucessor or a normal right pointer 
     */
    bool isLeftThreaded;
    bool isRightThreaded;
};

template<typename T>
std::shared_ptr<DoubleThreadedBSTNode<T> > createDoubleThreadedBST(std::shared_ptr<DoubleThreadedBSTNode<T> >& current) {

    /* Base case(s) */
    if(!current) return std::shared_ptr<DoubleThreadedBSTNode<T> >();
    if(!current->left && !current->right) return current;

    /* value is updated once for all in the deepest LHS recursive call */
    static bool firstLeft = true;
    static bool lastRight = true;

    /* Inorder sequence for updating links in the original BST */
    if(current->left){
        std::shared_ptr<DoubleThreadedBSTNode<T> > left = createDoubleThreadedBST(current->left);
        if(firstLeft){
            firstLeft = false;
            left->isLeftThreaded = false;
            left->isRightThreaded = true;
            left->right = current;
        } else {
            left->isRightThreaded = true;
            left->right = current;
        }
    }

    if(!current->right) return current;

    /* TO DO - TO DO - TO DO - TO DO - TO DO - TO DO - TO DO - TO DO */
    if(current->right){
        std::shared_ptr<DoubleThreadedBSTNode<T> > right = createDoubleThreadedBST(current->right);
        right->isLeftThreaded = true;
        right->left = current;
        return right;
    }
}

/* MORRIS - Inorder Tree Traversal without recursion and without stack */
template<typename T>
void MORRIS_INORDER_TRAVERSAL(BinarySearchTree<T>& tree) {

    std::shared_ptr<BSTNode<T> > root = tree.getRoot();
    if(!root) return;

    std::shared_ptr<BSTNode<T> > current = root;

    while(current){

        if(!current->left) {
            std::cout << current->value << " ";
            current = current->right;
        } else {
            std::shared_ptr<BSTNode<T> > previous = current->left;
            while(previous && previous->right && previous->right!=current) previous = previous->right;
            if(!previous->right){
                /* update right pointer of the leaf - inorder predecessor */
                previous->right = current;
                current = current->left;
            } else {
                /* retrieve right pointer of the leaf - inorder predecessor */
                previous->right = std::shared_ptr<BSTNode<T> >();
                std::cout << current->value << " ";
                current = current->right;
            }
        }
    }
}

/* MORRIS - Preorder Tree Traversal without recursion and without stack */
template<typename T>
void MORRIS_PREORDER_TRAVERSAL(BinarySearchTree<T>& tree) {

    std::shared_ptr<BSTNode<T> > root = tree.getRoot();
    if(!root) return;

    std::shared_ptr<BSTNode<T> > current = root;

    while(current) {

        if(!current->left){
            std::cout << current->value << " ";
            current = current->right;
        } else {
            std::shared_ptr<BSTNode<T> > pred = current->left;
            while(pred && pred->right && pred->right!=current){
                pred = pred->right;
            }
            if(!pred->right){
                pred->right = current;
                std::cout << current->data << " ";
                current = current->left;
            } else {
                pred->right = std::shared_ptr<BSTNode<T> >();
                current = current->right;
            }
        }
    }
}

/* Check if given keys represent the same BST without constructing the BST */
template<typename T>
bool isSameBST(std::vector<std::shared_ptr<BSTNode<T> > >& first, std::vector<std::shared_ptr<BSTNode<T> > >& second) {

    /* Base case(s) */

    /* if both are empty, return true */
    if(!first.size() && !second.size()) return true;

    /* if sizes are different, return false*/
    if(first.size() != second.size()) return false;

    /* if the first element is not the same, return false */
    if(first[0]->value != second[0]->value) return false;

    std::vector<std::shared_ptr<BSTNode<T> > > firstLower, firstUpper, secondLower, secondUpper;
    
    int n = first.size();

    for(int i = 1; i < n; i++) { 

        if(first[i]->value < first[0]->value) firstLower.push_back(first[i]);
        else firstUpper.push_back(first[i]);

        if(second[i]->value < second[0]->value) secondLower.push_back(second[i]);
        else secondUpper.push_back(second[i]);
    }

    /* if lower/upper sub-array sizes are not same, return false */
    if(firstUpper.size() != secondUpper.size()) return false;
    if(firstLower.size() != secondLower.size()) return false;

    return true;
}

/* Floor and Ceil in BST */
template<typename T>
void floorAndCeil(const BinarySearchTree<T>& tree, const T& target){

    std::shared_ptr<BSTNode<T> > root = tree.getRoot();
    std::shared_ptr<BSTNode<T> > floor, ceil;

    std::shared_ptr<BSTNode<T> > current = root;

    while(current){
        if(current->value == target){
            floor = ceil = target;
        } else if(current->value > target){
            ceil = current;
            current = current->left;
        } else {
            floor = current;
            current = current->right;
        }
    }

    std::cout << "Floor" << floor->value << "\n";
    std::cout << "Ceil" << ceil->value << "\n";

}

/* Replace every key in BST to contain sum of larger elements */
template<typename T>
T reverseInorderUtil(std::shared_ptr<BSTNode<T> >& current, T& trackingSum) {

    if(!current) return trackingSum;
    
    /* right recursion */
    T rightVal = reverseInorderUtil(current->right, trackingSum);
    
    /* current node */
    current->value += rightVal;
    trackingSum = current->value;

    /* left recursion */
    return reverseInorderUtil(current->left, trackingSum);
}

template<typename T>
void updateNodeSum(BinarySearchTree<T>& tree) {

    std::shared_ptr<BSTNode<T> > root = tree.getRoot();
    if(!root) return;

    /* performing reverse inorder traversal */
    reverseInorderUtil(root, 0);
}

/* Write an algoirthm to replace every element in an array with the least greater on its right */
template<typename T>
void insertionDecorator(BinarySearchTree<T>& tree, std::shared_ptr<BSTNode<T> >& current, T value, T& successor, void(BinarySearchTree<T>::*insertNode)(std::shared_ptr<BSTNode<T> >, T)) {

   (tree.*insertNode)(current, value);

}




template<typename T>
void leastGreaterRight(T arr[], int n) {

    BinarySearchTree<T> tree;
    tree.setRoot(std::make_shared<BSTNode<T> >());
    std::shared_ptr<BSTNode<T> > root = tree.getRoot();

    for(int i = n-1; i>=0; --i){

        int successor = -1;
        insertionDecorator(tree, root, arr[i], successor, &BinarySearchTree<T>::insertNode);
        arr[i] = successor;
    }
}

/* Merge 2 BSTs to sorted DLL */
template<typename T>
std::shared_ptr<BSTNode<T> > sortedMerge(std::shared_ptr<BSTNode<T> > first, std::shared_ptr<BSTNode<T> > second) {

    if(!first) return second;
    if(!second) return first;

    if(first->value < second->value){
        first->right = sortedMerge(first->right, second);
        first->right->left = first;
        // first->left = std::shared_ptr<BSTNode<T> >();
        return first;
    } else {
        second->right = sortedMerge(first, second->right);
        second->right->left = second;
        // second->left = std::shared_ptr<BSTNode<T> >();
        return second;
    }
}

template<typename T>
std::shared_ptr<BSTNode<T> > sortedBSTMergeDLL(BinarySearchTree<T>& firstTree, BinarySearchTree<T>& secondTree) {

    /* no auxillary space */
    std::shared_ptr<BSTNode<T> > firstDLL = BSTtoDLL(firstTree.getRoot());
    std::shared_ptr<BSTNode<T> > secondDLL = BSTtoDLL(secondTree.getRoot());

    std::shared_ptr<BSTNode<T> > resultDLL = sortedMerge(firstDLL, secondDLL);

    /* printing the resulting merged DLL */
    std::shared_ptr<BSTNode<T> > current = resultDLL;
    while(current){
        std::cout << current->value << " ";
        current = current->right;
    }
    return resultDLL;
}

/* Convert a BST to a minheap - using auxillary space */
template<typename T>
bool isComplete(const BinarySearchTree<T>& tree) {

    std::shared_ptr<BSTNode<T> > root = tree.getRoot();
    if(!root || (!root->left && !root->right)) return true;
    std::queue<std::shared_ptr<BSTNode<T> > > treeNodes;
    treeNodes.push(root);
    int currentLevel = 1;

    while(!treeNodes.empty()) {
        int size = treeNodes.size();
        if(size < (2<<(currentLevel-1))) return false;
        while(size){
            std::shared_ptr<BSTNode<T> > current = treeNodes.top();
            treeNodes.pop();
            if(current->left) treeNodes.push(current->left);
            if(current->right) treeNodes.push(current->right);
            --size;
        }
    ++currentLevel;
    }
    return true;
}

template<typename T>
void preorderReplacement(std::vector<std::shared_ptr<BSTNode<T> > >& inorder_sequence, std::shared_ptr<BSTNode<T> > current) {

    /* Base case */
    if(!current) return;

    // typename std::iterator_traits<>

    /* for max heap, update with last element */
    assert(!inorder_sequence.empty());
    current->value = inorder_sequence.front()->value;
    inorder_sequence.erase(inorder_sequence.begin());

    preorderReplacement(inorder_sequence, current->left);
    preorderReplacement(inorder_sequence, current->right);

}

template<typename T>
void constructCompleteMinheap(std::vector<std::shared_ptr<BSTNode<T> > >& inorder_sequence, std::shared_ptr<BSTNode<T> >& root) {

    /* for max heap, update with last element */
    assert(!inorder_sequence.empty());
    std::shared_ptr<BSTNode<T> > new_root = inorder_sequence.front();
    inorder_sequence.erase(inorder_sequence.begin());

    std::queue<std::shared_ptr<BSTNode<T> > > processQueue;
    processQueue.push(new_root);

    while(!inorder_sequence.empty()) {

        std::shared_ptr<BSTNode<T> > parent = processQueue.top();
        processQueue.pop();

        assert(!inorder_sequence.empty());
        parent->left = inorder_sequence.front();
        inorder_sequence.erase(inorder_sequence.begin());
        processQueue.push(parent->left);

        if(!inorder_sequence.empty()){
            parent->right = inorder_sequence.front();
            inorder_sequence.erase(inorder_sequence.begin());
            processQueue.push(parent->right);
        }
    }
    /* root node of the original tree is updated 
     * to point to root of the new heap
     */
    root = new_root;
}

template<typename T>
void heapifyBST(BinarySearchTree<T>& tree) {

    std::shared_ptr<BSTNode<T> > root = tree.getRoot();
    if(!root || (!root->left && !root->right) ) return;

    std::vector<std::shared_ptr<BSTNode<T> > > inorder_sequence;
    inorderUtil(root, inorder_sequence);

    /* We have 2 cases of the input BST -
     * 1. The BST is complete, height prop is satisfied 
     * 2. The BST is NOT complete, height to be adjusted
     */

    if(isComplete(tree)){
        preorderReplacement(inorder_sequence, root);
    } else {
        constructCompleteMinheap(inorder_sequence, root);
    }

    /* print minheap - level order - root is updated */
}

/* Link - https://www.geeksforgeeks.org/in-place-convert-bst-into-a-min-heap/ */
/* Convert a BST to a minheap - without auxillary space */
template<typename T>
void heapifyBST_inplace(BinarySearchTree<T>& tree) {

    /* Base case */
    std::shared_ptr<BSTNode<T> > root = tree.getRoot();
    if(!root) return;

    /* Head of the sorted linked list */
    std::shared_ptr<BSTNode<T> > list = BSTtoDLL(tree);

    /* Queue to keep track of parent pointers */
    std::queue<std::shared_ptr<BSTNode<T> > > processQueue;
    processQueue.push(list);

    /* head is used to traverse the list ahead of parent */
    std::shared_ptr<BSTNode<T> > head = list->right;

    while(head) {

        std::shared_ptr<BSTNode<T> > parent = processQueue.top();
        processQueue.pop();

        std::shared_ptr<BSTNode<T> > leftChild = head;
        head = head->right;
        leftChild->left = leftChild->right = std::shared_ptr<BSTNode<T> >();
        processQueue.push(leftChild);
        parent->left = leftChild;

        if(head){
            std::shared_ptr<BSTNode<T> > rightChild = head;
            head = head->right;
            rightChild->left = rightChild->right = std::shared_ptr<BSTNode<T> >();
            processQueue.push(rightChild);
            parent->right = rightChild;
        }
    }
    /* print level order starting from list pointer - list head */
}

// BT/BST Questions

/* Convert BT to BST using STL set */
/* Convert BT to height balanced BST using STL set */
/* Convert unbalanced BST to balanced BST */
/* Sorted merge 2 BSTs into single BST */
/* Split 2 BSTs based on value k */
/* All pairs from 2 BSTs whose sum = target */

/* Find the K'th ancestor of a node in BT */
/* Reverse a path in BST using a queue */
/* Find largest BST in BT */
/* Check if BT is BST */
/* Count subtrees of BT which are BST */
/* Count subtrees of BST whose nodes lie in range [m,n] */
/* Check if the given binary tree is a sum tree */
/* Combinations of words formed by replacing the given numbers with corresponding alphabets  */
/* Check if given BT is subtree of another BT */
/* Minimum # of swaps required to convert one BT to another BBT */
/* Given BT to full tree by removing half nodes */
/* Truncate given binary tree to remove nodes which lie on a path having sum less than K */
/* Build BT from parent array */
/* Maximum sum path between 2 leaves in a BT */
/* Construct a full binary tree from preorder sequence with leaf node information */
/* Calculate height of a binary tree with leaf nodes forming a circular doubly linked list */

/* Convert BT to BST using STL set */
template<typename T>
void setToBST(std::set<T>& s, std::shared_ptr<BSTNode<T> >& current) {

    if(!current) return;

    if(current->left) setToBST(current->left);

    current->value = *(s.begin());
    s.erase(s.begin());

    if(current->right) setToBST(current->right);
}

template<typename T>
void convertBTtoBST(BinarySearchTree<T>& tree) {

    std::shared_ptr<BSTNode<T> > root = tree.getRoot();
    if(!root) return;

    std::set<T> treeNodes;
    std::vector<std::shared_ptr<BSTNode<T> > > placeholder;
    inorderUtil(root, placeholder);

    /* save the values in increasing order in the set */
    std::transform(placeholder.begin(), placeholder.end(), std::back_inserter(treeNodes), 
    []<typename T>(const std::shared_ptr<BSTNode<T> >& node){
        return node->value;
    });

    setToBST(treeNodes, root);    
}

/* Convert unbalanced BST to balanced BST */
template<typename T>
std::shared_ptr<BSTNode<T> > getmid(std::shared_ptr<BSTNode<T> >& head, std::shared_ptr<BSTNode<T> >& frontRef, std::shared_ptr<BSTNode<T> >& backRef) {

    std::shared_ptr<BSTNode<T> > slow;
    std::shared_ptr<BSTNode<T> > fast;

    slow = head;
    fast = head->right;

    while(fast != nullptr && fast->right != nullptr){
        slow = slow->right;
        fast = fast->right->right;
    }

    frontRef = head;
    backRef = slow->right;

    /* updating links of slow( = mid) so that it is not a part of any list */
    slow->right = slow->left = std::shared_ptr<BSTNode<T> >();
    slow->left->right = slow->right->left = std::shared_ptr<BSTNode<T> >();

    return slow;
}

template<typename T>
std::shared_ptr<BSTNode<T> > DLLtoBSTUtil(std::shared_ptr<BSTNode<T> >& current) {

    if(!current) return std::shared_ptr<BSTNode<T> >();

    std::shared_ptr<BSTNode<T> > first_list;
    std::shared_ptr<BSTNode<T> > second_list;
    std::shared_ptr<BSTNode<T> > root = getmid(current, first_list, second_list);
    
    root->left = DLLtoBSTUtil(first_list);
    root->right = DLLtoBSTUtil(second_list);

    return root;
}

template<typename T>
void balanceBST_inplace(BinarySearchTree<T>& tree) {

    std::shared_ptr<BSTNode<T> > root = tree.getRoot();
    if(!root) return;

    std::shared_ptr<BSTNode<T> > list_head = BSTtoDLL(root);

    std::shared_ptr<BSTNode<T> > new_root = DLLtoBSTUtil(list_head);
    /* Print the balanced BST */

}

/* Height balanced merge of 2 BSTs - without duplicates */
template<typename T>
std::shared_ptr<BSTNode<T> > heightBalancedBSTMerge(BinarySearchTree<T>& firstTree, BinarySearchTree<T>& secondTree) {

    /* Base case(s) check */
    if(!firstTree.getRoot()) return secondTree.getRoot();
    if(!secondTree.getRoot()) return firstTree.getRoot();
    if(!firstTree.getRoot() && !secondTree.getRoot()) return std::shared_ptr<BSTNode<T> >();

    /* Perform a sorted merge on the 2 BSTs into a DLL - IN PLACE */
    std::shared_ptr<BSTNode<T> > merged_list = sortedBSTMergeDLL(firstTree, secondTree);
    /* Convert the DLL balanced BST - IN PLACE */
    std::shared_ptr<BSTNode<T> > new_root = DLLtoBSTUtil(merged_list);

    return new_root;
}

/* Split a BST into 2 BSTs based on 'k' */
template<typename T>
void splitBST_k_Node(BinarySearchTree<T>& tree, const T& k) {

    std::shared_ptr<BSTNode<T> > root = tree.getRoot();
    if(!root) return;

    std::vector<std::shared_ptr<BSTNode<T> > > inorder_sequence;
    inorderUtil(root, inorder_sequence);

    /* find iterator to the target, k */
    typename std::vector<std::shared_ptr<BSTNode<T> > >::iterator it = std::find_if(inorder_sequence.begin(), inorder_sequence.end(), [k]<typename T>(const std::shared_ptr<BSTNode<T> >& current) {
        return current->value == k;
    });

    /* if target not found */
    if(!it) return;

    /* get the index of target */
    int index = std::distance(inorder_sequence.begin(), it);

    /* pass the 2 arrays to generateBSTfromArray function 
     * and capture the 2 tree roots returned 
     */

}
 
/* All pairs from 2 BSTs with sum = target */
template<typename T>
void targetSum_2BST(BinarySearchTree<T>& firstTree, BinarySearchTree<T>& secondTree, const T& target) {

    if(!firstTree.getRoot() || !secondTree.getRoot()) return;

    std::shared_ptr<BSTNode<T> > root1 = firstTree.getRoot();
    std::shared_ptr<BSTNode<T> > root2 = secondTree.getRoot();

    std::vector<std::shared_ptr<BSTNode<T> > > inorder_sequence_1;
    std::vector<std::shared_ptr<BSTNode<T> > > inorder_sequence_2;

    /* ascending sequence */
    inorderUtil(root1,inorder_sequence_1);

    /* descending sequence */
    inorderUtil(root2, inorder_sequence_2);
    std::reverse(inorder_sequence_2.begin(), inorder_sequence_2.end());

    std::vector<std::pair<std::shared_ptr<BSTNode<T> >, std::shared_ptr<BSTNode<T> > > > result_pairs;

    while(!inorder_sequence_1.empty() && !inorder_sequence_2.empty()) {

        if(*(inorder_sequence_1.begin())->value + *(inorder_sequence_2.begin())->value == target){
            result_pairs.push_back(std::make_pair(*(inorder_sequence_1.begin())), *(inorder_sequence_2.begin()));
            inorder_sequence_1.erase(inorder_sequence_1.begin());
            inorder_sequence_2.erase(inorder_sequence_2.begin());
        } else if(*(inorder_sequence_1.begin())->value + *(inorder_sequence_2.begin())->value < target){
            inorder_sequence_1.erase(inorder_sequence_1.begin());
        } else if((inorder_sequence_1.begin())->value + *(inorder_sequence_2.begin())->value > target) {
            inorder_sequence_2.erase(inorder_sequence_1.begin());
        }
    }
    /* print results by iterating through result_pairs vector */
}

/* Construct ancestor matrix for a given BT */
template<typename T>
void constructAncestorMatrixUtil(const std::shared_ptr<BSTNode<T> >& current, const T& ancestor, std::vector<std::vector<int> >& ancestorMatrix) {

    /* Base case */
    if(!current) return;

    if(ancestor != -1) ancestorMatrix[ancestor][current->data] = 1;
    ancestor = current->data;

    constructAncestorMatrixUtil(current->left, ancestor, ancestorMatrix);
    constructAncestorMatrixUtil(current->right, ancestor, ancestorMatrix);
}

template<typename T>
void constructAncestorMatrix(const BinarySearchTree<T>& tree) {

    if(!tree.getRoot()) return;

    std::shared_ptr<BSTNode<T> > root = tree.getRoot();
    int nodes = count(tree.getRoot());
    std::vector<std::vector<int> > ancestorMatrix(nodes, std::vector<int>(nodes, 0));

    /* Constructs a matrix only with LCA - immediate ancestor */
    constructAncestorMatrixUtil(root, -1, ancestorMatrix);

    /* Applying transitive closure on the ancestor matrix */
    for(int k = 0; k < nodes; k++){
        for(int i = 0; i < nodes; i++){
            for(int j = 0; j < nodes; j++){
                ancestorMatrix[i][j] = ancestorMatrix[i][j] || (ancestorMatrix[i][k] && ancestorMatrix[k][j]);
            }
        }
    }
}

/* Construct BT from ancestor matrix - Iterative Bottom Up Approach */
template<typename T>
std::shared_ptr<BSTNode<T> > BTfromAncestorMatrix(const std::vector<std::vector<int> >& ancestorMatrix) {

    int nodes = ancestorMatrix.size();
    std::vector<bool> parent(nodes, false);
    std::multimap<T, T> childCount;

    /* Multimap will hold nodes in ascending order of the # of children they have */
    for(int i = 0; i < nodes; i++){
        int sum = 0;
        for(int j = 0; j < nodes; j++){
            sum += ancestorMatrix[i][j];
        }
        childCount.insert(std::pair<T, T>(sum, i));
    }

    std::vector<std::shared_ptr<BSTNode<T> > > nodePointers(nodes);
    std::shared_ptr<BSTNode<T> > root;

    for(typename std::multimap<T, T>::iterator it =  childCount.begin(); it != childCount.end(); ++it){

        /* create a new node and enter it into the vector of nodes */
        nodePointers[it->second] = std::make_shared<BSTNode<T> >(it->second);

        root = nodePointers[it->second];

        if(!it->first){
            for(int j = 0; j<nodes; j++){
                if(ancestorMatrix[it->second][j] && !parent[j]){
                    if (!nodePointers[it->second]->left){
                        nodePointers[it->second]->left = nodePointers[j];
                    } else nodePointers[it->second]->right = nodePointers[j];
                    parent[j] = true;
                }
            }
        }
    }
    /* the last entry in the multimap will be the root */
    return root;
}

/* Construct BT from ancestor matrix - Recursive Top Down Approach */
template<typename T>
int rootIndex(const std::vector<std::vector<int> >& ancestorMatrix) {

    int nodes = ancestorMatrix.size();
    int rootIdx;

    for(int j = 0; j < nodes; j++){
        int count = 0;
        for(int i = 0; i < nodes; ++i){
            if(ancestorMatrix[i][j] == 0) ++count;
        }

        if(count == nodes) {
            rootIdx = j;
            break;
        }
    }
    return rootIdx;
}

template<typename T>
std::shared_ptr<BSTNode<T> >& BTfromAncestorMatrixRecursiveUtil(const std::vector<std::vector<int> >& ancestorMatrix, int rootIdx) {

    std::shared_ptr<BSTNode<T> > root = std::make_shared<BSTNode<T> >(rootIdx);

    int left = 1;

    for(int j = 0; j < ancestorMatrix[rootIdx].size(); ++j){
        if(ancestorMatrix[rootIdx][j]){
            if(left == 1){
                root->left = BTfromAncestorMatrixRecursiveUtil<T>(ancestorMatrix, j);
            } else if(left == 2) {
                root->right = BTfromAncestorMatrixRecursiveUtil<T>(ancestorMatrix, j);
            }
            left++;
        }
    }
    return root;
}

template<typename T>
std::shared_ptr<BSTNode<T> >& BTfromAncestorMatrixRecursive(const std::vector<std::vector<int> >& ancestorMatrix) {

    int root = rootIndex<T>(ancestorMatrix);
    BTfromAncestorMatrixRecursiveUtil<T>(ancestorMatrix, root);
}

/* Find the K'th ancestor of a node in BT */
template <typename T>
std::shared_ptr<BSTNode<T> > kth_Ancestor_Util(const std::shared_ptr<BSTNode<T> >& current, const T& target, int& k, bool& flag){

    if(!current) return std::shared_ptr<BSTNode<T> >();

    auto left = kth_Ancestor_Util(current->left, target, k, flag);
    if(flag == false) auto right = kth_Ancestor_Util(current->right, target, k, flag);

    if(current->value == target) {
        flag = true;
        return current;
    }

    if(flag){
        if(k > 0){
            k--;
        }else if(k == 0){
            std::cout << k  << "th ancestor of the target node is " << current->value << std::endl;
            return std::shared_ptr<BSTNode<T> >();
        }
    }
    return current;
}

template <typename T>
std::shared_ptr<BSTNode<T> > kth_Ancestor(const BinarySearchTree<T> &tree, const T &target, const int &k)
{

    std::shared_ptr<BSTNode<T> > root = tree.getRoot();
    if(!root) return std::shared_ptr<BSTNode<T> >();

    bool flag = false;
    kth_Ancestor_Util(root, target, k, false);
}

/* Reverse a path in BT */
template<typename T>
void pathToTargetUtil(const std::shared_ptr<BSTNode<T> >& current, const T& target,  std::vector<std::shared_ptr<BSTNode<T> > >& result) {

    static bool found = false;

    if(!current || found) return;

    if(current) result.push_back(current);
    if(current->value == target) {
        found = true;
        return;
    }
    else {
        pathToTargetUtil(current->left, target, result);
        if(!found) pathToTargetUtil(current->right, target, result);
    }
    if(!found) result.pop_back();
}

template<typename T>
void reverBSTpathToTarget(BinarySearchTree<T>& tree, const T& target) {

    std::shared_ptr<BSTNode<T> > root = tree.getRoot();
    if(!root) return;

    std::vector<std::shared_ptr<BSTNode<T> > > targetPath;
    pathToTargetutil(root, target, targetPath);

    for (typename std::vector<BSTNode<T> >::iterator start = targetPath.begin(), end = std::prev(targetPath.end()); start < end; ++start, --end) {
        std::swap((*start)->value, (*end)->value);
    }
}

/* Reverse a path using recursion and backtracking */
template<typename T>
std::shared_ptr<BSTNode<T> >& reversePathUtil(std::shared_ptr<BSTNode<T> >& current, const T& target, std::map<int, T>& tracking, int level, int& nextPos) {

    if(!current) return std::shared_ptr<BSTNode<T> >();

    if(current->value == target){
        tracking.insert_or_assign(level, current->value);
        current->value = tracking[nextPos];
        nextPos++;
        return current;
    }

    tracking.insert_or_assign(level, current->value);

    std::shared_ptr<BSTNode<T> > left = reversePathUtil(current->left, target, tracking, level+1, nextPos);
    std::shared_ptr<BSTNode<T> > right;
    if(!left) right = reversePathUtil(current->right, target, tracking, level+1, nextPos);

    if(left || right) {
        current->value = tracking[nextPos];
        nextPos++;
        return current;
    }
    return std::shared_ptr<BSTNode<T> >();
}

template<typename T>
void reversePath(BinarySearchTree<T>& tree, const std::shared_ptr<BSTNode<T> >& target) {

    std::shared_ptr<BSTNode<T> > root = tree.getRoot();
    if(!root) return;

    int level = 0;
    int nextPos = 0;
    std::map<int, T> trackingMap;

    reversePathUtil(root, target->value, trackingMap, level, nextPos);

}

/* Check if BT is BST */
template<typename T>
bool isBST(const std::shared_ptr<BSTNode<T> >& current, int min, int max) {

    /* Base case */
    if(!current) return true;

    /* check current node */
    if(current->value < min || current->value > max) return false;

    return (isBST(current->left, min, current->value -1) && isBST(current->right, current->value+1, max));
}

/* Find size of the largest BST in BT */
template<typename T>
int largestBSTSize(const std::shared_ptr<BSTNode<T> >& root) {

    // std::shared_ptr<BSTNode<T> > root = tree.getRoot();
    if(!root) return 0;
    if(!root->left && !root->right) return 1;

    /* return number of elements in BBT rooted at current node */
    if(isBST(root)) return count(root);

    return max(largestBSTSize(root->left), largestBSTSize(root->right));

}

/* Count subtrees of BST whose nodes lie in range [m,n] */
template<typename T>
int countBSTRange(const std::shared_ptr<BSTNode<T> >& current, int min, int max) {

    static int count = 0;

    if(!current) return 0;

    count += countBSTRange(current->left, min, current->value - 1);
    count += countBSTRange(current->right, current->value + 1, max);

    if(current->value > min && current->value < max && isLeaf(current)) ++count; 

    return count;

}

/* Check if the given binary tree is a sum tree */
template<typename T>
bool isSumTreeUtil(const std::shared_ptr<BSTNode<T> >& current, bool& flag) {

    if(!current) return true;

    bool left = isSumTreeUtil(current->left, flag);
    if(left){
        bool right = isSumTreeUtil(current->right, flag);

        int childSum = sum(current->left) + sum(current->right);

        if(current->value == childSum || isLeaf(current)) return true;
    }

    return false;

}

template<typename T>
bool isSumTree(const BinarySearchTree<T>& tree){

    std::shared_ptr<BSTNode<T> > root = tree.getRoot();
    if(!root || isLeaf(root)) return true;
    bool flag = true;
    return isSumTreeUtil(root, false);

}

template<typename T>
void preorderUtil(const std::shared_ptr<BSTNode<T> >& current, std::vector<T>& preorder_sequence){
    if(!current) return;
    preorder_sequence.push_back(current->value);
    preorderUtil(current->left, preorder_sequence);
    preorderUtil(current->right, preorder_sequence);
}

/* Check if BT is subtree of other BT using preorder traversal */
template<typename T>
bool checksubtreeBT(const BinarySearchTree<T>& firstTree, const BinarySearchTree<T>& secondTree) {

    std::shared_ptr<BSTNode<T> > root1 = firstTree.getRoot(); /* firstTree == tree */
    std::shared_ptr<BSTNode<T> > root2 = secondTree.getRoot();/* secondTree == subtree */

    /* Base case - if either root is null, return true */
    if(!root2) return true;
    if(!root1) return false;

    /* Compare the preorder and inorder sequences of the BTs, 
     * as they uniquely represent the tree 
     * use KMP algorithm for pattern matching 
     */

    std::vector<T> inorder_sequence_first;
    std::vector<T> inorder_sequence_second;
    inorderUtil(root1, inorder_sequence_first);
    inorderUtil(root2, inorder_sequence_second);

    /* perform KMP comparison, or RK comparison */

    std::vector<T> preorder_sequence_first;
    std::vector<T> preorder_sequence_second;
    preorderUtil(root1, preorder_sequence_first);
    preorderUtil(root2, preorder_sequence_second);

    /* perform KMP comparison, or RK comparison */

    /* return true here as everything passes */
    return true;

}

/* Sum of nodes on longest path in BT */
template<typename T>
void longestPathSumUtil(const std::shared_ptr<BSTNode<T> >& current, std::vector<std::shared_ptr<BSTNode<T> > >& longestPath, int& maxSum, int& currentSum, int& maxLevel, int& currentLevel) {

    /* longest path - terminal condition */
    if(!current){
        if(maxLevel < currentLevel){
            maxLevel = currentLevel;
            maxSum = currentSum;
        } else if(maxLevel == currentLevel && maxSum < currentSum){
            maxSum = currentSum;
        }
        return;
    }

    /* recurring on left and right children */
    longestPathSumUtil(current->left, longestPath, maxSum, currentSum + current->value, maxLevel, currentLevel+1);
    longestPathSumUtil(current->right, longestPath, maxSum, currentSum + current->value, maxLevel, currentLevel+1);

}

template<typename T>
int longestPathSum(const std::shared_ptr<BSTNode<T> >& root) {

    if(!root) return -1;

    std::vector<std::shared_ptr<BSTNode<T> > > longestPath;
    int maxSum = INT_MIN;
    int currentSum = 0;
    int maxLevel = 0;
    int currentLevel = 0;

    longestPathSumUtil(root, longestPath, maxSum, currentSum, maxLevel, currentLevel);

    return maxSum;

}

/* Longest path in BT */
template<typename T>
std::vector<std::shared_ptr<BSTNode<T> > >& longestRootToLeafPath(const std::shared_ptr<BSTNode<T> >& root) {

    if(!root) return std::vector<std::shared_ptr<BSTNode<T> > >(); /* return {}; */

    /* postorder traversal from leaf to root; push nodes from leaf to root */
    std::vector<std::shared_ptr<BSTNode<T> > > rightVec = longestRootToLeafPath(root->right);
    std::vector<std::shared_ptr<BSTNode<T> > > leftVec = longestRootToLeafPath(root->left);

    if(rightVec.size() > leftVec.size()) {
        rightVec.push_back(root->value);
        return rightVec;
    }
    leftVec.push_back(root->data);
    return leftVec;

}

/* End point of diameter of a tree  */
template<typename T>
int heightUtil(const std::shared_ptr<BSTNode<T> >& current, int& result, std::shared_ptr<BSTNode<T> >& diameterRoot) {

    if(!current){
        result = 0;
        return 0;
    }

    int leftHeight = heightUtil(current->left);
    int rightHeight = heightUtil(current->right);

    if(result < leftHeight + rightHeight + 1){
        result = leftHeight + rightHeight + 1;
        diameterRoot = current;
    }

    /* return height of the current node, depending on children node height */
    return 1+std::max(leftHeight, rightHeight);
}

template<typename T>
std::shared_ptr<BSTNode<T> >& diameterUtil(const std::shared_ptr<BSTNode<T> >& current) {

    if(!current){
        return 0;
    }
    int result;
    std::shared_ptr<BSTNode<T> > diameterRoot;
    heightUtil(current, result, diameterRoot);
    return diameterRoot;
}

template<typename T>
std::pair<std::shared_ptr<BSTNode<T> >, std::shared_ptr<BSTNode<T> > > diameterEnds(const BinarySearchTree<T>& tree) {

    std::shared_ptr<BSTNode<T> > root = tree.getRoot();
    if(!root) return std::make_pair(std::shared_ptr<BSTNode<T> >(), std::shared_ptr<BSTNode<T> >());

    std::pair<std::shared_ptr<BSTNode<T> >, std::shared_ptr<BSTNode<T> > > nodePair;

    /* get root node on the path of the diameter */
    std::shared_ptr<BSTNode<T> > d_root = diameterUtil(root);

    /* get longest root to leaf path on left and right of this d_root */
    std::vector<std::shared_ptr<BSTNode<T> > > leftPath = longestRootToLeafPath(d_root->left);
    std::vector<std::shared_ptr<BSTNode<T> > > rightPath = longestRootToLeafPath(d_root->right);

    /* the first node in both the vectors will be the leaf node on LHS and RHS respectively */
    nodePair = std::make_pair(*leftPath.begin(), *rightPath.begin());
    
    return nodePair;
}

/* Combinations of words formed by replacing the given numbers with corresponding alphabets */

/* Minimum # of swaps required to convert one BT to another BT */

/* Given BT to full tree by removing half nodes */

/* Truncate given binary tree to remove nodes which lie on a path having sum less than K */

/* Build BT from parent array */

/* Maximum sum path between 2 leaves in a BT */

/* Construct a full binary tree from preorder sequence with leaf node information */

/* Calculate height of a binary tree with leaf nodes forming a circular doubly linked list */