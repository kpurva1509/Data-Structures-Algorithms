#include "headers.hpp"
#include "Node.hpp"
#include "GenericLinkedList.hpp"

template<typename T>
class SinglyLinkedList: public GenericLinkedList<T> {

    std::shared_ptr<Node<T> > head;
    std::shared_ptr<Node<T> > tail;
    int count;

public:

    SinglyLinkedList():head(nullptr), tail(nullptr), count(0) {}
    SinglyLinkedList(std::shared_ptr<Node<T> >& head);
    SinglyLinkedList(std::shared_ptr<Node<T> >& head, std::shared_ptr<Node<T> >& tail);
    SinglyLinkedList(std::shared_ptr<Node<T> >& head, std::shared_ptr<Node<T> >& tail, int &&count);

    SinglyLinkedList(SinglyLinkedList<T> &&rhs);
    SinglyLinkedList &operator=(SinglyLinkedList<T> &&rhs);

    virtual void insertAtHead(T &&value) override;
    virtual void insertAtTail(T &&value) override;
    virtual void deleteHead() override;
    virtual void deleteTail() override;
    virtual std::shared_ptr<Node<T> > &findTarget(T &&value) override;
    virtual void deleteTarget(T &&value) override;

    /* constexpr */ int getSize() const;
    /* constexpr */ bool empty() const;

    virtual void accept(GenericListVisitor<T>* listVisitor) const override;

    std::shared_ptr<Node<T> > getHead() {return this->head; }
    std::shared_ptr<Node<T> > getTail() {return this->tail; }

    std::shared_ptr<Node<T> >& middle(std::shared_ptr<Node<T> >& first, std::shared_ptr<Node<T> >& last) {
        std::shared_ptr<Node<T> > slow = first;
        std::shared_ptr<Node<T> > fast = first;
        while(fast && fast->next){
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }

    std::shared_ptr<Node<T> > binarySearch(const T& value, std::shared_ptr<Node<T> >& first, std::shared_ptr<Node<T> >& last) {
        std::shared_ptr<Node<T> > result;
        // sort the list in ascending or descending order first***********
        std::shared_ptr<Node<T> > middle = middle(first, last);
        if(value == middle->value) result = middle;
        else if(value < middle->value) binarySearch(first, middle);
        else binarySearch(middle->next, last); 
        return result;
    }

    /* Using hashing */
    void removeUnsortedDuplicates() {

        std::shared_ptr<Node<T> > current = head;
        std::shared_ptr<Node<T> > previous = head;
        std::unordered_set<T> seen; // used for hasing seen data
        
        while(current){
            if (typename std::unordered_set<T>::iterator it = std::find(seen.begin(), seen.end(), head->value); it != seen.end()) {
                previous->next = current->next;
                delete(current);
            }
            else
            {
                seen.insert(current->value);
                previous = current;
            }
            current = previous->next;
        }
    }

    /* using recursion */
    void recursiveRemoveSortedDuplicates(std::shared_ptr<Node<T> >& currentHead) {

        if(currentHead == nullptr) return;
        if(currentHead->value == currentHead->next->value){
            currentHead->next = currentHead->next->next;
            delete(currentHead->next);
            recursiveRemoveSortedDuplicates(currentHead);
        } else recursiveRemoveSortedDuplicates(currentHead->next);
    }

    void removeSortedDuplicates() {
        std::shared_ptr<Node<T> > current = head;
        recursiveRemoveSortedDuplicates(current);
    }

    void removeLoop() {
        std::shared_ptr<Node<T> > slow;
        std::shared_ptr<Node<T> > fast;

        slow = getHead()->next;
        fast = slow->next->next;

        /* Detecting a loop using 2 pointers, if loop exists.... */
        while(fast && fast->next){
            if(slow == fast) break;
            slow = slow->next;
            fast = fast->next->next;
        }
        
        /* Break the loop using 2 points moving at the same pace... */
        if(slow == fast){
            slow = getHead();
            while(slow->next != fast->next){
                slow = slow->next;
                fast = fast->next;
            }
            fast->next = nullptr;
        }

    }

    /* 
    Nested iterator 
    class iterator;

    iterator begin();
    iterator end();
    iterator find(iterator first, iterator last, const T& value);

    External iterator class
    friend class iterator;
    */

        using value_type = T;
    using reference_type = T&;
    using pointer_type = T*;
    using size_type = std::size_t;
    using const_reference_type = const T&;
    using const_pointer_type = const T*;

private:

    template<typename Iterator>
    using is_correct_type = std::enable_if<
        std::is_same<T, typename std::iterator_traits<Iterator>::value_type>::value &&
        std::is_same<std::input_iterator_tag,  typename std::iterator_traits<Iterator>::iterator_category>::value
    >;

public:

    class iterator : public std::iterator<std::forward_iterator_tag, T> {
    protected:
        Node<T>* node;
        friend class SinglyLinkedList<T>;
        iterator(Node<T>* node): node(node){}

    public:
        /* constexpr */ iterator() = default;
        /* constexpr */ iterator(const iterator&) = default;
        /* constexpr */ iterator& operator=(const iterator&) = default;
        /* constexpr */ iterator(iterator &&) /* noexcept */ = default;
        /* constexpr */ iterator &operator=(iterator &&) /* noexcept */ = default;

        bool operator!=(const iterator &rhs) /* noexcept */ { return node != rhs.node; }
        bool operator==(const iterator &rhs) /* noexcept */ { return node == rhs.node; }

        T& operator*(){ return node->value; }
        T* operator->(){ return &node->value; }
    };


};