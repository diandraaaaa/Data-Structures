
//25.ADT SortedMultiMap – repräsentiert mithilfe einer Hashtabelle mit unabhängiger Verkettung wo Paaren der Form
// (key, value) gespeichert werden. Wenn ein Schlüssel mehrere entsprechende Werte hat, dann kommt es in mehreren Paaren
// vor. In dem Constructor des Iterators erstelle ein sortiertes Array von Elementen und benutze es für die Iterierung.

#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include "IteratorKey.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

/*
 * WC: Theta(n)
 * BC: Theta(n)
 * Avg: Theta(n)
 */
SortedMultiMap::SortedMultiMap(Relation r) {
        // Set the relation
        relation = r;

        // Initialize the hash table variables
        capacity = INITIAL_CAPACITY;
        _size = 0;
        table = new Node*[capacity];

        // Initialize each bucket in the hash table to nullptr
        for (int i = 0; i < capacity; i++) {
            table[i] = nullptr;
        }
    }

/*
 * WC: Theta(n)
 * BC: Theta(1)
 * Avg: Theta(n)
 */
void SortedMultiMap::add(TKey c, TValue v) {

    // Compute the hash value
    int index = hash(c, capacity);

    // Create a new node
    Node* newNode = new Node;
    newNode->key = c;
    newNode->value = v;
    newNode->next = nullptr;

    // Check if the bucket is empty
    if (table[index] == nullptr) {
        // Insert the new node as the first element in the bucket
        table[index] = newNode;
    } else {
        // Find the appropriate position to insert the new node based on the relation
        Node* prev = nullptr;
        Node* curr = table[index];

        while (curr != nullptr && relation(curr->key, c)) {
            prev = curr;
            curr = curr->next;
        }

        // Insert the new node at the appropriate position
        if (prev == nullptr) {
            // Insert at the beginning of the bucket
            newNode->next = curr;
            table[index] = newNode;
        } else {
            // Insert in between two nodes or at the end of the bucket
            prev->next = newNode;
            newNode->next = curr;
        }
    }

    // Increase the size
    _size++;
    rehash();
}

/*
 * WC: Theta(n)
 * BC: Theta(1)
 * Avg: Theta(1)
 */
vector<TValue> SortedMultiMap::search(TKey c) const {
    vector<TValue> values;

    // Compute the hash value
    int index = hash(c, capacity) ;

    // Traverse the linked list at the bucket to find values with the given key
    Node* curr = table[index];
    while (curr != nullptr) {
        if (curr->key == c) {
            // Found a matching key, add the value to the result vector
            values.push_back(curr->value);
        }
        curr = curr->next;
    }
    return values;
}

/*
 * WC: Theta(n)
 * BC: Theta(1)
 * Avg: Theta(n)
 */
bool SortedMultiMap::remove(TKey c, TValue v) {
    // Compute the hash value
    int index = hash(c, capacity);

    // Check if the bucket is empty
    if (table[index] == nullptr) {
        return false;  // No elements with the given key
    }

    // Find the node to remove
    Node* prev = nullptr;
    Node* curr = table[index];

    while (curr != nullptr) {
        if (curr->key == c && curr->value == v) {
            // Found a matching key-value pair, remove the node
            if (prev == nullptr) {
                // Removing the first node in the bucket
                table[index] = curr->next;
            } else {
                prev->next = curr->next;
            }

            delete curr;
            _size--;
            rehash();
            return true;
        }

        prev = curr;
        curr = curr->next;
    }

    return false;  // No matching key-value pair found
}


/*
 * WC: Theta(1)
 * BC: Theta(1)
 * Avg: Theta(1)
 */
int SortedMultiMap::size() const {
	return _size;
}

/*
 * WC: Theta(1)
 * BC: Theta(1)
 * Avg: Theta(1)
 */
bool SortedMultiMap::isEmpty() const {
    return _size == 0;
}

/*
 * WC: Theta(1)
 * BC: Theta(1)
 * Avg: Theta(1)
 */
SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}

/*
 * WC: Theta(1)
 * BC: Theta(1)
 * Avg: Theta(1)
 */
SMMIteratorKey SortedMultiMap::iteratorKey() const {
	return SMMIteratorKey(*this);
}

/*
 * WC: Theta(n^2)
 * BC: Theta(n^2)
 * Avg: Theta(n^2)
 */
SortedMultiMap::~SortedMultiMap() {
    // Traverse each bucket and delete the nodes in each linked list
    for (int i = 0; i < capacity; i++) {
        Node* curr = table[i];
        while (curr != nullptr) {
            Node* next = curr->next;
            delete curr;
            curr = next;
        }
    }

    // Delete the table array
    delete[] table;
}

/*
 * WC: Theta(1)
 * BC: Theta(1)
 * Avg: Theta(1)
 */
int SortedMultiMap::hash(const int& key, int _capacity) {
    // Apply a basic modulo operation to the key to determine the bucket index
    return abs(key) % _capacity;
}


/*
 * WC: Theta(n^2)
 * BC: Theta(n^2)
 * Avg: Theta(n^2)
 */
void SortedMultiMap::rehash() {
    // Check if resizing is needed
    if (_size >= capacity * MAX_LOAD_FACTOR) {
        resize(capacity*2);
    }
    if (_size <= capacity/MAX_LOAD_FACTOR){
        resize(capacity/2);
    }
}

/*
 * WC: Theta(n^2)
 * BC: Theta(n^2)
 * Avg: Theta(n^2)
 */
void SortedMultiMap::resize(int newCapacity) {
    Node** newTable = new Node*[newCapacity]{};

    // Rehash all key-value pairs into the new table
    for (int i = 0; i < capacity; i++) {
        Node* current = table[i];
        while (current != nullptr) {
            Node* next = current->next;
            int index = hash(current->key, newCapacity);
            current->next = newTable[index];
            newTable[index] = current;
            current = next;
        }
    }

    // Free the memory allocated for the old table
    delete[] table;

    // Update the table and capacity to the new values
    table = newTable;
    capacity = newCapacity;
}


