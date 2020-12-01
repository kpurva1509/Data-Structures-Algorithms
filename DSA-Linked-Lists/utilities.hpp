#include "headers.hpp"
#include "Node.hpp"
#include "GenericLinkedList.hpp"
#include "SinglyLinkedList.hpp"
#include "DoublyLinkedList.hpp"

/*******************************************************************/
// Operations
// https://www.geeksforgeeks.org/quicksort-for-linked-list/
// Union on LL -                unsorted and sorted w/ duplicates
// Intersection on LL -         unsorted and sorted w/ duplicates
// Difference A - B on LL -     unsorted and sorted w/ duplicates
// Concatenate on 2 LLs -       unsorted and sorted w/ duplicates
// Missing element in LL -      unsorted and sorted w/ duplicates
// Partitioning criteria on LL
// Rotate a linked list
// Left Shift/ Right Shift a LL
// Reverse a subrange
// Rotate a subrange
// Check if the list is sorted and rotated using Binary Search
// Convert to XOR LL
// To check if LL is a palindrome(extension of XOR)
// Find kth node from middle towards the head/tail
// Make middle as head
// Next greater element in LL
// Flatten a LL(in sorted manner)
// Swap Kth node from beginning with Kth node from end (SLL, DLL)
// Shuffle a linked list (Pseudo-random shuffle)
// Find length of loop in LL
// Swap nodes w/o swapping data ?????????????????????????????????????
// Intersection of 2 LL
// Segregate even and odd
// Reverse a LL in groups of N
// Polynomial Representation and evaluation using LL
// DLL from 2D Matrix
// Remove fibonacci # from DLL
// Find last 2 survivors in N persons standing in a circle after killing next to immediate neighbour
/*******************************************************************/

/*******************************************************************/
// Efficient Approaches -
// 1. Sorting and Binary Search
// 2. Hashing
/*******************************************************************/

template<typename T>
std::shared_ptr<Node<T> > unionSLL_UNSORTED(const SinglyLinkedList<T>& first, const SinglyLinkedList<T>& second) {

    // Hashing****
    std::unordered_map<T, int> hashmap; 
    std::shared_ptr<Node<T> > firstList = first->head;
    std::shared_ptr<Node<T>> secondList = second->head;
    std::shared_ptr<Node<T> > listUnion;

    if(firstList){
        ++hashmap[firstList->value];
        listUnion = firstList;
    }else if (secondList) return second;
    else return std::shared_ptr<Node<T> >();

    firstList = firstList->next;
    std::shared_ptr<Node<T> > listUnionHead = listUnion;

    while(firstList){
        // increment map's value for key == firstList->value
        ++hashmap[firstList->value];
        listUnion->next = firstList;
        firstList = firstList->next;
        listUnion = listUnion->next;
    }

    while(secondList) {
        if(hashmap.find(secondList->value)!= nullptr){
            --hashmap[secondList->value];
        } else {
            listUnion->next = secondList;
            listUnion = listUnion->next;
        }
        secondList = secondList->next;
    }
 
    return listUnionHead;
}

template <typename T>
std::shared_ptr<Node<T>> unionSLL_SORTED(const SinglyLinkedList<T> &first, const SinglyLinkedList<T> &second) {

    // Recursive Merging****
    std::shared_ptr<Node<T> > result;
    if(first == nullptr) return second;
    if(second == nullptr) return first;

    if(first->value == second->value){
        result = first;
        result->next = unionSLL_SORTED(first->next, second->next);
    } else if(first->value < second->value) {
        result = first;
        result->next = unionSLL_SORTED(first->next, second);
    } else {
        result = second;
        result->next = unionSLL_SORTED(first, second->next);
    }
    return result;
}

template <typename T>
std::shared_ptr<Node<T> > intersectionSLL_UNSORTED(const SinglyLinkedList<T> &first, const SinglyLinkedList<T> &second) {

    if (first == nullptr || second = nullptr) return std::shared_ptr<Node<T> >();

    std::unordered_map<T, int> hashmap;
    std::shared_ptr<Node<T> > firstList = first->head;
    std::shared_ptr<Node<T> > secondList = second->head;
    std::shared_ptr<Node<T> > listIntersection;


    ++hashmap[firstList->value];
    listIntersection = firstList;
    firstList = firstList->next;
    std::shared_ptr<Node<T>> result = listIntersection;

    while (firstList) {
        // increment map's value for key == firstList->value
        ++hashmap[firstList->value];
    }
    while (secondList){
        if (hashmap.find(secondList->value) != nullptr) {
            listIntersection->next = secondList;
            listIntersection = listIntersection->next;
            --hashmap[secondList->value];
        }
        secondList = secondList->next;
    }
    return result;
}

template <typename T>
std::shared_ptr<Node<T> > differenceSLL(const SinglyLinkedList<T> &first, const SinglyLinkedList<T> &second){
    if(first->head == nullptr) return std::shared_ptr<Node<T> >();
    if(second->head == nullptr) return first;

    std::shared_ptr<Node<T> > secondList = second->head;
    std::shared_ptr<Node<T> > firstList = second->head;
    std::shared_ptr<Node<T> > result;
    std::unordered_map<T, int> hashmap;

    ++hashmap[secondList->value];
    trackingList = secondList;
    secondList = secondList->next;

    while(secondList){
        ++hashmap[secondList->value];
    }

    while(firstList) {
        if(hashmap.find(firstList->value) == nullptr){
            result = firstList;
            result->next = result; // reverse order*****
        } else {
            --hashmap[firstList->value];
        }
        firstList = firstList->next;
    }
    return result;
}

template <typename T>
std::shared_ptr<Node<T> > concatenateSLL(const SinglyLinkedList<T> &first, const SinglyLinkedList<T> &second){

}

template <typename T>
std::shared_ptr<Node<T> > missingElementsSLL(const SinglyLinkedList<T> &first, const SinglyLinkedList<T> &second){

}

template <typename T>
std::shared_ptr<Node<T> > conditionalPartitioningSLL(const SinglyLinkedList<T> &first, const SinglyLinkedList<T> &second) {

}

template<typename T>
std::shared_ptr<Node<T> > rotateRangesSLL(SinglyLinkedList<T>& sll, const char& direction, const int& places) {
    if(sll->head == nullptr) return std::shared_ptr<Node<T> >();
    // std::shared_ptr<Node<T> > result;
    switch(direction){
        case 'r':
        {
            /* TO GET SECOND TO LAST POINTER W/O LINEAR TRAVERSAL */
            
        }
        break;
        case 'l':
        {
            while(places) {
                sll->tail->next = sll->head;
                sll->tail = sll->tail->next;
                sll->head = sll->head->next;
                sll->tail->next = nullptr;
                places--;
            }
        }
        break;
        default:
            std::cout << "Invalid direction, quitting....\n"; 
    }
    return sll->head;
}

// Reverse a subrange
// Rotate a subrange
// Check if the list is sorted and rotated (using Binary Search)
// Convert to XOR LL( SLL or DLL)
// To check if LL is a palindrome(extension of XOR)
// Find kth node from middle towards the head/tail
// Make middle as head
// Next greater element in LL
// Flatten a LL(in sorted manner)
// Swap Kth node from beginning with Kth node from end (SLL, DLL)
// Swap nodes in consecutive pairs

template<typename T> // ???????????????????????????? USE RECURSION!!!
void reverseSubrange(SinglyLinkedList<T>& sll, const int& start, const int& end) {

    if(!sll->head || start==end) return;

    std::shared_ptr<Node<T> > head = sll->head;
    std::shared_ptr<Node<T> > index_before_start;
    std::shared_ptr<Node<T> > index_at_start;
    std::shared_ptr<Node<T> > previous;
    std::shared_ptr<Node<T> > current;
    std::shared_ptr<Node<T> > next; 
    
    int i=0;
    while(i<=end){
        if(i == start - 1) {
            previous = head;
            index_before_start = head;
        }

        if(i == start){
            index_at_start = head;
            current = head;
            next = head->next;
        }

        if(i>start && i<= end){
            previous = current;
            current = next;
            next = next->next;
            current->next = previous;
        }

        head = head->next;
        i++;
    }
    index_before_start->next = current;
    index_at_start->next = next;

}

template<typename T>
void rotateSublist(SinglyLinkedList<T>& sll, const int& start, const int& end, const char& direction, const int& positions){

    if (direction != 'r' || direction != 'l') return;
    if (positions > (end - start + 1)) positions = positions % (end - start + 1);
    if (positions == 0 || positions == end - start + 1) return;

    std::shared_ptr<Node<T> > link;
    std::shared_ptr<Node<T> > previous;
    std::shared_ptr<Node<T> > current = sll->head;
    std::shared_ptr<Node<T> > finish;

    if(start == 1) link = sll->head;

    int i=0;
    int j = 0;

    switch(direction){
        case 'r':
        {
            // right rotation
            while(current != nullptr) {
                i++;
                if(i-1 == start){
                    previous = current;
                    link = current->next;
                }

                if(i == end - positions){
                    if(start == 1){
                        finish = current;
                        sll->head = current->next;
                    } else {
                        finish = current;
                        previous->next = current->next;
                    }
                }

                if(i  == end){
                    Node<T>* sll_node = current->next;
                    current->next = link;
                    finish->next = sll_node;
                    return;
                }
            }
        }
        break;

        case 'l':
        {
            // left rotation
            while(current != nullptr){
                j++;
                if(j - 1 == start){
                    previous = current;
                    link = current->next;
                }

                if(j == m + k - 1){
                    if(start == 1){
                        finish = current;
                        // sll->head = current->next;
                    } else {
                        finish = current; 
                        previous->next = current->next;
                    }
                }

                if(j == end){
                    Node<T> *sll_node = current->next;
                    finish->next = sll_node;
                    current->next = link;
                    return;
                }
            }
        }
        break;

        default:
        cout << "Invalid direction input, quitting...\n";
    }
}

template<typename T> // using binary search
bool isSortedRotated(const SinglyLinkedList<T>& sll) {

    std::shared_ptr<Node<T> > current = sll->head;
    bool flag = true;
    int count = 0; // rotated by (count+1)
    while(current->value < current->next->value){
        current = current->next;
        count++;
    }
    current = current->next;
    while(current){
        if(current->value > current->next->value) {
            flag = false;
            break;
        }
        current = current->next;
    }  
    return flag;
}

template<typename T>
void XOR_SLL(SinglyLinkedList<T>& sll, int& count) {

    if(!sll->head) return;
    std::shared_ptr<Node<T> > prev;
    std::shared_ptr<Node<T> > curr = sll->head;
    count = 0;
    // iterative XOR 
    while(curr){
        std::shared_ptr<Node<T> > curr_next = curr->next;
        curr->next = reinterpret_cast<shared_ptr<Node<T> > >(static_cast<intptr_t>(curr_next) ^ static_cast<intptr_t>(prev));
        prev = curr;
        curr = curr_next;
        count++;
    }
}
template <typename T>
void recover_XOR_SLL(SinglyLinkedList<T> &sll) {
    if (!sll->head) return;
    std::shared_ptr<Node<T> > prev;
    std::shared_ptr<Node<T> > curr = sll->head;

    while(curr){
        curr->next = reinterpret_cast<std::shared_ptr<Node<T> > >(static_cast<intptr_t>(prev) ^ static_cast<intptr_t>(curr->next));
        prev = curr;
        curr = curr->next;
    }
}

template<typename T>
bool isPalindrome(SinglyLinkedList<T>& sll) {
    
    // inital check for empty or single node
    if(!sll->head || !sll->head->next) return false;
    
    int node_count;
    XOR_SLL(sll, node_count);

    bool flag = true;

    std::shared_ptr<Node<T> > head = sll->head;
    std::shared_ptr<Node<T> > tail = sll->tail;
    std::shared_ptr<Node<T> > head_prev;
    std::shared_ptr<Node<T> > tail_next;

    // iterate through the LL for half the count
    for(int i=0; i<(node_count+1)/2; i++){
        if(head->value != tail->value){
            flag = false;
            break;
        }
        head_prev = reinterpret_cast<std::shared_ptr<Node<T> > >(static_cast<intptr_t>(head_prev) ^ static_cast<intptr_t>(head->next));  // gives next head
        tail_next = reinterpret_cast<std::shared_ptr<Node<T> > >(static_cast<intptr_t>(tail_next) ^ static_cast<intptr_t>(tail->next));  // gives next tail (--)
        std::swap(head, head_prev);          // swap with old head
        std::swap(tail, tail_next);          // swap with old tail
    }

    recover_XOR_SLL(sll);
    return flag;
}

template <typename T>
void recursiveMiddleUtil(std::shared_ptr<Node<T> >& head, int& count, std::shared_ptr<Node<T> >& result) {

    // terminating condition
    if(!head){
        count = count/2 + 1;
        return;
    }

    // recursive statement
    ++count;
    recursiveMiddleUtil(head->next, count, result);

    // return path operations
    if(count == 0){
        result = head;
    }
    count--;
}

template<typename T>
std::shared_ptr<Node<T> > middle(const SinglyLinkedList<T>& sll) {

    if(!sll && !sll->head->next) return std::shared_ptr<Node<T> >();
    std::shared_ptr<Node<T> > head = sll->head;
    int count = 0;
    std::shared_ptr<Node<T> > result;
    recursiveMiddleUtil(head, count, result);
    return result;
}

template<typename T>
void kFromMiddleUtil(std::shared_ptr<Node<T> >& head, int& count, int& length, std::shared_ptr<Node<T> >& result, int& position) {

    if(!head) return;

    ++count;
    ++length;
    kFromMiddleUtil(head->next, count, length, result, position);
    // (l/2)+1+k for k'th node from middle towards the end
    if((length/2)+1 - position == count){
        result = head;
    }
    count--;
}

template<typename T>
std::shared_ptr<Node<T> > kFromMiddle(const SinglyLinkedList<T>& sll, const int& position) {

    if(!sll && !sll->head->next) return std::shared_ptr<Node<T> >();
    int count = 0; 
    int length = 0;
    std::shared_ptr<Node<T> > result;
    kFromMiddleUtil(sll->head, count, length, result, position);

    return result;
}

/*******************************************************************/
                    /* FLATTEN A LINKED LIST */                     
               /* Implement 2D LL using std::map */
/*******************************************************************/

