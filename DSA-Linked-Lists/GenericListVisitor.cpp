#include "GenericListVisitor.hpp"

template<typename T>
struct ListPrinter : GenericListVisitor<T> {
    std::ostringstream oss;
    virtual void visit(SinglyLinkedList<T> *sll) override;
    virtual void visit(DoublyLinkedList<T> *dll) override;
    std::string str() const {
        return oss.str();
    }
};

template <typename T>
void ListPrinter<T>::visit(SinglyLinkedList<T> *sll) {
    Node<T>* current = sll->head;
    int count = 1;
    while(current!= nullptr) {
        oss << count << "count. " << current->value << ", " << current->next << "\n";
        current = current->next;
        count++;
    }
    delete current;
}

template <typename T>
void ListPrinter<T>::visit(DoublyLinkedList<T> *dll){
    DLLNode<T>* current = dll->head;
    while (current != nullptr) {
        oss << count << ". " << current->prev << ", " << current->value << ", " << dll->next << "\n";
        current = current->next;
        count++;
    }
    delete current;
}

/* Sorting Linked list of custom objects */
/* If a linked list of type T is created, and T is CUSTOM 
T needs to implement a custom comparator function (<) as well */
/* Merge Sort Implementation */
template<typename T>
struct ListSorter : GenericListVisitor<T> {

    virtual void visit(SinglyLinkedList<T> *sll) override;
    std::shared_ptr<Node<T> > recursiveSortingImplSLL(std::shared_ptr<Node<T>> &head);
    void splitHalf(std::shared_ptr<Node<T>> head, std::shared_ptr<Node<T>> &frontRef, std::shared_ptr<Node<T>> &backRef);
    std::shared_ptr<Node<T> > sortedMergeSLL(std::shared_ptr<Node<T>> frontRef, std::shared_ptr<Node<T>> backRef));

    virtual void visit(DoublyLinkedList<T> *dll) override;
    void recursiveSortingImplDLL();
};

template <typename T>
void ListSorter<T>::visit(SinglyLinkedList<T> *sll) {

    std::shared_ptr<Node<T> > head = sll->getHead();
    // std::shared_ptr<Node<T> > frontRef;
    // std::shared_ptr<Node<T> > backRef;
    head = recursiveSortingImplSLL(head);
}

template <typename T>
std::shared_ptr<Node<T> > ListSorter<T>::recursiveSortingImplSLL(std::shared_ptr<Node<T>> &head) {

    std::shared_ptr<Node<T> > frontRef;
    std::shared_ptr<Node<T> > backRef;

    /* base condition to terminate recursion */
    if(head == nullptr) return std::shared_ptr<Node<T> >();
    if(head->next == nullptr) return head;

    splitHalf(head, frontRef, backRef);
    recursiveSortingImplSLL(frontRef);
    recursiveSortingImplSLL(backRef);

    return sortedMergeSLL(frontRef, backRef);
}

template <typename T>
void ListSorter<T>::splitHalf(std::shared_ptr<Node<T> > head, std::shared_ptr<Node<T> > &frontRef, std::shared_ptr<Node<T> > &backRef) {

    Node<T>* slow;
    Node<T>* fast;

    slow = head;
    fast = head->next;
    while(fast!=nullptr && fast->next != nullptr){
        slow = slow->next;
        fast = fast->next->next;
    }

    frontRef = head; /* frontRef from start to slow */
    backRef = slow->next; /* backRef slow->next to end */
    slow->next = nullptr;
    // delete slow;
    // delete fast;
}

template<typename T>
std::shared_ptr<Node<T> > ListSorter<T>::sortedMergeSLL(std::shared_ptr<Node<T>> frontRef, std::shared_ptr<Node<T> > backRef) {

    std::shared_ptr<Node<T> > result;

    if(frontRef == nullptr) return backRef;
    if(backRef == nullptr) return frontRef;

    if(frontRef->value <= backRef->value) {
        result = frontRef;
        result->next = sortedMergeSLL(frontRef->next, backRef);
    } else {
        result = backRef;
        result->next = sortedMergeSLL(frontRef, backRef->next);
    }
    return result;
}

template <typename T>
struct ListSorterInsertion : GenericListVisitor<T>
{
    std::ostringstream oss;
    virtual void visit(SinglyLinkedList<T> *sll) override;
    void sortedInsertImplSLL(std::shared_ptr<Node<T>> &head, std::shared_ptr<Node<T> > current);

    virtual void visit(DoublyLinkedList<T> *dll) override;
};

template <typename T>
void ListSorterInsertion<T>::visit(SinglyLinkedList<T> *sll){

    std::shared_ptr<Node<T> > sorted;
    std::shared_ptr<Node<T> > head = sll->getHead();
    std::shared_ptr<Node<T> > current = sll->getHead();
    while(current) {
        sortedInsertImplSLL(sorted, current);
        current = current->next;
    }
    head = sorted;
}

template <typename T>
void ListSorterInsertion<T>::sortedInsertImplSLL(std::shared_ptr<Node<T>> &head, std::shared_ptr<Node<T>> current) {

    if(head == nullptr || current->value <= head->value){
        current->next = head;
        head = current;
    } else {
        Node<T>* new_node = head;
        while(new_node->next && new_node->value < current->value){
            new_node = new_node->next;
        }
        current->next = new_node->next;
        new_node->next = current;
    }
}

template <typename T>
struct ListSorterQuickSort : GenericListVisitor<T> {
   
    std::ostringstream oss;

    virtual void visit(SinglyLinkedList<T> *sll) override;
    std::shared_ptr<Node<T> > &recursiveSortingImplSLL(std::shared_ptr<Node<T> > &head, std::shared_ptr<Node<T> > &tail);
    std::shared_ptr<Node<T> > &getTail(std::shared_ptr<Node<T> >& current);
    std::shared_ptr<Node<T> > &partition(std::shared_ptr<Node<T> > &head, std::shared_ptr<Node<T> > &tail, std::shared_ptr<Node<T> > &new_head, std::shared_ptr<Node<T> > &new_tail);
   
    virtual void visit(DoublyLinkedList<T> *dll) override;
};

template<typename T>
std::shared_ptr<Node<T> > &getTail(std::shared_ptr<Node<T> >& current){
    while(current && current->next){
        current = current->next;
    }
    return current;
}

template<typename T>
std::shared_ptr<Node<T> > &partition(std::shared_ptr<Node<T> > &head, std::shared_ptr<Node<T> > &tail, std::shared_ptr<Node<T> > &new_head, std::shared_ptr<Node<T> > &new_tail) {
    
    std::shared_ptr<Node<T> > pivot = tail;
    std::shared_ptr<Node<T> > prev;
    std::shared_ptr<Node<T> > curr = head;
    std::shared_ptr<Node<T> > end = pivot;

    while(curr != pivot){
        if(curr->value < pivot->value){
            if(!new_head){
                new_head = curr;
            }
            prev = curr;
            curr = curr->next;
        } else {
            if(prev) prev->next = curr->next;
            std::shared_ptr<Node<T> > curr_next = curr->next;
            curr->next = nullptr;
            end->next = curr;
            end = curr;
            curr = curr_next;
        }
    }
    if(!new_head) new_head = pivot;
    new_tail = end;
    return pivot;
}

template <typename T>
std::shared_ptr<Node<T> > &ListSorterQuickSort<T>::recursiveSortingImplSLL(std::shared_ptr<Node<T> > &head, std::shared_ptr<Node<T> > &tail){

    // terminating recursion condition
    if(!head || head == tail) return head;
    std::shared_ptr<Node<T> > &new_head;
    std::shared_ptr<Node<T> > &new_tail;

    std::shared_ptr<Node<T> > pivot = partition(head, tail, new_head, new_tail);

    // left half
    if(new_head!=pivot){
        std::shared_ptr<Node<T> > temp = new_head;
        while(temp->next != pivot){
            temp = temp->next;
        }
        temp->next = nullptr;
        new_head = recursiveSortingImplSLL(new_head, temp);
        temp = getTail(new_head);
        temp->next = pivot;
    }

    // right half
    pivot->next = recursiveSortingImplSLL(pivot->next, new_tail);

    return new_head;
}

template <typename T>
void ListSorterQuickSort<T>::visit(SinglyLinkedList<T> *sll) {

    // head and tail of the original SLL
    std::shared_ptr<Node<T> > head = sll->getHead();
    std::shared_ptr<Node<T> > tail = sll->getTail();
    head = recursiveSortingImplSLL(head, tail);
}