#include "headers.hpp"
#include "Node.hpp"
#include "GenericLinkedList.hpp"

template<typename T>
class DoublyLinkedList: public GenericLinkedList<T> {

    std::shared_ptr<DLLNode<T> > head;
    std::shared_ptr<DLLNode<T> > tail;
    std::size_t count;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), count(0) {}
    DoublyLinkedList(std::shared_ptr<DLLNode<T> > &head);
    DoublyLinkedList(std::shared_ptr<DLLNode<T> > &head, std::shared_ptr<DLLNode<T> > &tail);
    DoublyLinkedList(std::shared_ptr<DLLNode<T> > &head, std::shared_ptr<DLLNode<T> > &tail, int &&count);

    DoublyLinkedList(DoublyLinkedList<T> &&rhs);
    DoublyLinkedList &operator=(DoublyLinkedList<T> &&rhs);

    virtual void insertAtHead(T &&value) override;
    virtual void insertAtTail(T &&value) override;
    virtual void deleteHead() override;
    virtual void deleteTail() override;
    virtual std::shared_ptr<DLLNode<T> > &findTarget(T &&value) override;
    virtual void deleteTarget(T &&value) override;

    /* constexpr function cannot be virtual */
    /* constexpr */ int getSize() const;
    /* constexpr */ bool empty() const;

    virtual void accept(GenericListVisitor<T> *listVisitor) const override;

    /* Nested iterator */
    class iterator;

    iterator begin();
    iterator end();
    iterator find(iterator first, iterator last, const T &value);

    /* External iterator class */
    friend class iterator;
};