#include "headers.hpp"

template<typename T>
class Node {
    T value;
    std::unique_ptr<Node<T> > next;

    public:
    Node():value(T()), next(nullptr){}
    Node(T&& value);
    Node(T&& value, std::unique_ptr<Node<T> > next);

    /* Move operations */
    Node(Node<T>&& rhs);
    Node<T>& operator=(Node<T>&& rhs);    

};


template<typename T>
class DLLNode_CRTP : Node<DLLNode_CRTP<T> > {

};

template<typename T, typename U>
class DLLNode_Mixin : public T {
    // static_assert(std::is_base_of<Node<U>, T>::value, "Template argument must be a Node<T>");
    std::unique_ptr<DLLNode_Mixin<T, U> > prev;
};

template<typename T>
class DLLNode {
    T value;
    std::unique_ptr<DLLNode<T> > next;
    std::unique_ptr<DLLNode<T> > prev;

public:
    DLLNode();
    DLLNode(const T& value);
    DLLNode(const T& value, std::unique_ptr<DLLNode<T> >& next, std::unique_ptr<DLLNode<T> >& prev);

    /* Move operations */
    DLLNode(DLLNode<T>&& rhs);
    DLLNode& operator=(DLLNode<T>&& rhs);

};