#include "DoublyLinkedList.hpp"

/* method implementations */

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(std::shared_ptr<DLLNode<T> > &head)
{
    this->head = head;
}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(std::shared_ptr<DLLNode<T> > &head, std::shared_ptr<DLLNode<T> > &tail)
{
    this->head = head;
    this->tail = tail;
}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(std::shared_ptr<DLLNode<T> > &head, std::shared_ptr<DLLNode<T> > &tail, int &&count)
{
    this->head = head;
    this->tail = tail;
    this->count = count;
}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(DoublyLinkedList<T> &&rhs)
{
    this->head = std::move(rhs.head);
    this->tail = std::move(rhs.tail);
    this->count = std::move(rhs.count);
}

template <typename T>
DoublyLinkedList<T> &DoublyLinkedList<T>::operator=(DoublyLinkedList<T> &&rhs)
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
void DoublyLinkedList<T>::insertAtHead(T &&value)
{
    DLLNode<T> new_DLLNode = std::make_shared<DLLNode<T> >(value);
    if (count == 0)
    {
        head = tail = new_DLLNode;
    }
    else
    {
        /* convert the current head from shared to unique next pointer of new head */
        head->prev = new_DLLNode;
        new_DLLNode->next = head;
        head.reset(new_DLLNode);
    }
    count++;
}

template <typename T>
void DoublyLinkedList<T>::insertAtTail(T &&value)
{
    DLLNode<T> new_DLLNode = std::make_shared<DLLNode<T> >(value);
    if (count == 0)
    {
        head = tail = new_DLLNode;
    }
    else
    {
        tail->next = new_DLLNode;
        new_DLLNode->prev = tail;
        tail = new_DLLNode;
    }
    count++;
}

template <typename T>
void DoublyLinkedList<T>::deleteHead()
{
    if (count == 1)
    {
        head.reset();
    }
    else
    {
        head = std::move(head->next);
        head->prev = nullptr;
    }
    count--;
}

template <typename T>
void DoublyLinkedList<T>::deleteTail()
{
    if (count == 1)
        head.reset();
    else
    {
        tail = tail->prev;
        tail->next = nullptr;
    }
    count--;
}

template <typename T>
std::shared_ptr<DLLNode<T> > &DoublyLinkedList<T>::findTarget(T &&value)
{
    std::shared_ptr<DLLNode<T> > result = std::make_shared<DLLNode<T> >();
    if (head->value == value)
        return head;
    if (tail->value == value)
        return tail;
    DLLNode<T> *current = head.get()->next;
    while (current->next != nullptr)
    {
        if (current->value == value)
            break;
        current = current->next;
    }
    if (current)
        return result.reset(current);
    else
        return result;
}

template <typename T>
void DoublyLinkedList<T>::deleteTarget(T &&value)
{
    if (head->value == value)
    {
        deleteHead();
        return;
    }
    else if (tail->value == value)
    {
        deleteTail();
        return;
    }
    else
    {
        std::shared_ptr<DLLNode<T> > DLLNode_to_delete(findTarget(value));
        if (DLLNode_to_delete)
        {
            DLLNode<T> *current = head.get();
            while (current->next != DLLNode_to_delete)
            {
                current = current->next;
            }
            current->next = DLLNode_to_delete->next;
            DLLNode_to_delete.reset(nullptr);
            count--;
        }
        else
            return;
    }
}

template <typename T>
/* constexpr */ int DoublyLinkedList<T>::getSize() const
{
    return count;
}

template <typename T>
/* constexpr */ bool DoublyLinkedList<T>::empty() const
{
    return (count == 0);
}

template <typename T>
void DoublyLinkedList<T>::accept(GenericListVisitor<T> *listVisitor) const
{
    listVisitor->visit(this);
}

/* Nested class implementation 
template<typename T>
class DoublyLinkedList<T>::iterator {

};*/