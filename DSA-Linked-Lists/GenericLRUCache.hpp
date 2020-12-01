#include "headers.hpp"
// #include "Node.hpp"
// #include "DoublyLinkedList.hpp"
// #include "GenericLinkedList.hpp"
// #include "GenericListVisitor.hpp"

template<typename K, typename V>
struct Node {
    K key;
    V value;
    Node<K,V>* next;
    Node<K,V>* prev;

    Node(){}
    Node(const K& _key, const V& _value): key(_key), value(_value), next(nullptr), prev(nullptr){}
};

template<typename K, typename V>
struct DLL {
    std::size_t size;
    Node<K,V>* head;
    Node<K,V>* tail;
    
    // DLL(){}
    DLL(size_t _size):size(_size){
        head->next = tail;
        tail->prev = head;
    }

    void addToList(Node<K,V>* node) {
        if(!head && !tail){
            head = tail = node;
        } else {
            node->next = head;
            head->prev = node;
            head = node;
        }
    }

    void removeFromList(Node<K,V>*& node) {
        tail = tail->prev;
        tail->next = nullptr;
        size--;
    }

    void moveToFront(Node<K,V>* node) {
        if(node == head) return;
        if(node == tail) {
            tail = tail->prev;
            tail->next = nullptr;
        } else {
            node->prev->next = node->next;
            node->next->prev = node->prev;
        }
        node->next = head;
        head->prev = node;
        head = node;
    }

    size_t getSize() const { return size; }

    Node<K,V>* getTail() {return tail; }

};

template<typename K, typename V>
class GenericLRUCache {

    int size, capacity;
    std::map<K, Node<K,V>*> hashmap;
    DLL<K,V>* DoublyLinkedList;

public:

    explicit GenericLRUCache(int _capacity): capacity(_capacity), size(0){
        hashmap = std::map<K, Node<K,V>*>();
        DoublyLinkedList = new DLL<K,V>();
    }

    V get(K key) {
        typename std::map<K, Node<K, V> *>::iterator it = std::find(hashmap.begin(), hashmap.end(), key);
        if(it == hashmap.end()){
            std::cout << "Key not found\n";
            return -1;
        } 
        V value = it->second->value;
        DoublyLinkedList->moveToFront(it->second);
        return value;
    }

    void put(K key, V val) {
        typename std::map<K, Node<K, V> *>::iterator it = std::find(hashmap.begin(), hashmap.end(), key);
        if(it!=hashmap.end()){
            it->second->value = val;
            DoublyLinkedList->moveToFront(it->second);
            return;
        } 
        if(size == capacity) {
            hashmap.erase(std::remove(hashmap.begin(), hashmap.end(), DoublyLinkedList->getTail()->key), hashmap.end());
            DoublyLinkedList->removeFromList(DoublyLinkedList->getTail());
        }
        Node<K,V>* new_node = new Node<K,V>(key, val);
        DoublyLinkedList->addToList(new_node);
        size++;
        hashmap[key] = new_node;
    }

    /* Print the DLL in order */
    void print() {
        Node<K,V>* current = DoublyLinkedList->head;
        std::cout << "Printing contents of LRU Cache as follows:\n";
        std::cout << "--------------------------------------------\n";
        while(current){
            std::cout << "Key: " << current->key << ", Value: " << current->value << ", Next: " << current->next << ", Previous: " << current->prev << std::endl;
            current = current->next;
        }
        std::cout << "--------------------------------------------\n";
        std::cout << "Done printing contents of LRU Cache\n";
    }
};