#include "headers.hpp"
#include "Node.hpp"
#include "GenericLinkedList.hpp"
#include "SinglyLinkedList.hpp"
#include "DoublyLinkedList.hpp"

template<typename T>
struct GenericListVisitor{
    /* virtual destructor to ensure correct object destruction */
    virtual ~GenericListVisitor() = default;
    
    virtual void visit(SinglyLinkedList<T>* sll) = 0;
    virtual void visit(DoublyLinkedList<T>* dll) = 0;

};