#include "SinglyLinkedList.hpp"

/* method implementations */

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(std::shared_ptr<Node<T> >& head){
    this->head = head;
}

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(std::shared_ptr<Node<T> >& head, std::shared_ptr<Node<T> >& tail){
    this->head = head;
    this->tail = tail;
}

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(std::shared_ptr<Node<T> >& head, std::shared_ptr<Node<T> >& tail, int &&count) {
    this->head = head;
    this->tail = tail;
    this->count = count;
}

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(SinglyLinkedList<T> &&rhs){
    this->head = std::move(rhs.head);
    this->tail = std::move(rhs.tail);
    this->count = std::move(rhs.count);

}

template <typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(SinglyLinkedList<T> &&rhs)
{
    // static_assert(this != &rhs);
    this->head.reset();
    this->tail.reset();
    this->count = 0;
    this->head = std::move(rhs.head);
    this->tail = std::move(rhs.tail);
    this->count = std::move(rhs.count);
    return *this;
}

template <typename T>
void SinglyLinkedList<T>::insertAtHead(T &&value){
    Node<T> new_node = std::make_shared<Node<T> >(value);
    if(count==0) {
        head = tail = new_node;
    } else {
        /* convert the current head from shared to unique next pointer of new head */
        new_node->next = std::move(head);
        head.reset(new_node);
    }
    count++;
}

template <typename T>
void SinglyLinkedList<T>::insertAtTail(T &&value){
    Node<T> new_node = std::make_shared<Node<T> >(value);
    if(count==0){
        head = tail = new_node;
    }else {
        tail->next = new_node;
        tail = new_node;
    }
    count++;
}

template <typename T>
void SinglyLinkedList<T>::deleteHead(){
    if(count == 1) {
        head.reset();
    } else {
        head = std::move(head->next);
    }
    count--;
}

template <typename T>
void SinglyLinkedList<T>::deleteTail(){
    if(count == 1) head.reset();
    else {
        Node<T>* current = head.get();
        while(current->next->next != nullptr) {
            current = current->next;
        }
        tail.reset(current);
    }
    count--;
}

template <typename T>
std::shared_ptr<Node<T> > &SinglyLinkedList<T>::findTarget(T &&value){
    std::shared_ptr<Node<T> > result = std::make_shared<Node<T> >();
    if(head->value == value) return head;
    if(tail->value == value) return tail;
    Node<T>* current = head.get()->next;
    while(current->next!=nullptr) {
        if(current->value == value) break;
        current = current->next;
    }
    if(current) return result.reset(current);
    else return result;
}

template <typename T>
void SinglyLinkedList<T>::deleteTarget(T &&value){
    if(head->value == value){
        deleteHead();
        return;
    } else if(tail->value == value) {
        deleteTail();
        return;
    }else {
        std::shared_ptr<Node<T> > node_to_delete(findTarget(value));
        if(node_to_delete) {
            Node<T>* current = head.get();
            while(current->next != node_to_delete){
                current = current->next;
            }
            current->next = node_to_delete->next;
            node_to_delete.reset(nullptr);
            count--;  
        } else return;
    }
    
}

template <typename T>
/* constexpr */ int SinglyLinkedList<T>::getSize() const {
    return count;
}

template <typename T>
/* constexpr */ bool SinglyLinkedList<T>::empty() const {
    return (count==0);
}

template <typename T>
void SinglyLinkedList<T>::accept(GenericListVisitor<T> *listVisitor) const {
    listVisitor->visit(this);
}

/* Nested class implementation 
template<typename T>
class SinglyLinkedList<T>::iterator {

};*/