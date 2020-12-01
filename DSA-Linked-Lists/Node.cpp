#include "Node.hpp"

/* Method implementations */

template<typename T> Node<T>::Node(T&& value){
    this->value = value;
}

template <typename T> Node<T>::Node(T&& value, std::unique_ptr<Node<T> > next) {
    this->value = value;
    this->next = std::move(next);
}

template<typename T> Node<T>::Node(Node<T>&& rhs){
    this->value = std::move(rhs.value);
    this->next = std::move(rhs.next);
}

template <typename T>
Node<T>& Node<T>::operator=(Node<T>&& rhs) {
    if(this!=&rhs){
        next.reset();
        this->value = std::move(rhs.value);
        this->next = std::move(rhs.next);
        rhs.value = T();
        rhs.next = std::move(nullptr);
    }
    return *this;
}

template<typename T>
DLLNode<T>::DLLNode():value(T()), next(nullptr), prev(nullptr) {}

template <typename T>
DLLNode<T>::DLLNode(const T &value) : value(value), next(nullptr), prev(nullptr){}

template<typename T>
DLLNode<T>::DLLNode(const T &value, std::unique_ptr<DLLNode<T> > &next, std::unique_ptr<DLLNode<T> > &prev){
    this->value = value;
    this->next = std::move(next);
    this->prev = std::move(prev);
}

/* Move operations */
template <typename T>
DLLNode<T>::DLLNode(DLLNode<T> &&rhs){
    this->value = std::move(rhs.value);
    this->next = std::move(rhs.next);
    this->prev = std::move(rhs.prev);
}

template<typename T>
DLLNode<T>& DLLNode<T>::operator=(DLLNode<T> && rhs) {
    if(this!=&rhs) {
        this->value = std::move(rhs.value);
        this->next.reset(std::move(rhs.next));
        this->prev.reset(std::move(rhs.prev));
    }
    return *this;
}