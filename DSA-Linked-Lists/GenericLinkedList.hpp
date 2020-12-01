#include "headers.hpp"
#include "Node.hpp"
// #include "GenericListVisitor.hpp" causes inclusion of GenericLinkedList.hpp into itself
// Therefore, declare the class here, and define it in the file later
template <typename>struct GenericListVisitor;

    template <typename T>
    class GenericLinkedList
{

    /* std::shared_ptr<Node<T> > head; */
    /* std::shared_ptr<Node<T> > tail; */
    /* int count; */

public:
    GenericLinkedList(){}
    GenericLinkedList(std::shared_ptr<Node<T> > head);
    GenericLinkedList(std::shared_ptr<Node<T> > head, std::shared_ptr<Node<T> > tail);
    GenericLinkedList(std::shared_ptr<Node<T> > head, std::shared_ptr<Node<T> > tail, int&& count);

    GenericLinkedList(GenericLinkedList<T>&& rhs);
    GenericLinkedList& operator=(GenericLinkedList<T>&& rhs);

    virtual void insertAtHead(T&& value);
    virtual void insertAtTail(T&& value);
    virtual void deleteHead();
    virtual void deleteTail();
    virtual std::shared_ptr<Node<T> > &findTarget(T &&value);
    virtual void deleteTarget(T&& value);

    virtual ~GenericLinkedList() = default;
    virtual void accept(GenericListVisitor<T>* listVisitor) const = 0;
};