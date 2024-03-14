#include "SortedBag.h"
#include "SortedBagIterator.h"

/*
 * WC: Theta(1)
 * BC: Theta(1)
 * Avg: Theta(1)
 */
SortedBag::SortedBag(Relation r) {
    relation = r;
    head = nullptr;
    tail = nullptr;
}

/*
 * WC: Theta(n)
 * BC: Theta(1)
 * Avg: Theta(n)
 */
void SortedBag::add(TComp e) {
    Node *newNode = new Node;
    newNode->data = e;
    newNode->prev = nullptr;
    newNode->next = nullptr;

    // If the sorted bag is empty, add the new node as the head
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    } else {
        // Traverse the sorted bag to find the position where the new element should be inserted
        Node *current = head;
        while (current != nullptr && relation(current->data, e)) {
            current = current->next;
        }
        // Insert the new node before the current node
        if (current == head) {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        } else if (current == nullptr) {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        } else {
            newNode->prev = current->prev;
            newNode->next = current;
            current->prev->next = newNode;
            current->prev = newNode;
        }
    }
}

/*
 * WC: Theta(n)
 * BC: Theta(1)
 * Avg: Theta(n)
 */
bool SortedBag::remove(TComp e) {
    Node* current = head;

    // Traverse the sorted bag to find the node containing the given element
    while (current != nullptr && current->data != e) {
        current = current->next;
    }

    if (current == nullptr) {
        // The element was not found in the sorted bag
        return false;
    }
    else {
        if (current == head && current == tail) {
            // Case 1: The sorted bag contains only one node, which is the one to be removed
            delete current;
            head = nullptr;
            tail = nullptr;
        }
        else if (current == head) {
            // Case 2: The node to be removed is the head of the sorted bag
            head = head->next;
            head->prev = nullptr;
            delete current;
        }
        else if (current == tail) {
            // Case 3: The node to be removed is the tail of the sorted bag
            tail = tail->prev;
            tail->next = nullptr;
            delete current;
        }
        else {
            // Case 4: The node to be removed is in the middle of the sorted bag
            current->prev->next = current->next;
            current->next->prev = current->prev;
            delete current;
        }
        return true;
    }
}
/*
 * WC: Theta(n)
 * BC: Theta(1)
 * Avg: Theta(n)
 */
bool SortedBag::search(TComp elem) const {
    Node* current = head;
	while (current != nullptr) {
            if(current->data == elem)
                return true;
            current = current->next;
        }
	return false;
}

/*
 * WC: Theta(n)
 * BC: Theta(n)
 * Avg: Theta(n)
 */
int SortedBag::nrOccurrences(TComp elem) const {
    int occurr=0;
    Node* current = head;
    while (current != nullptr) {
        if(current->data == elem)
            occurr++;
        current = current->next;
    }
    return occurr;
}

/*
 * WC: Theta(n)
 * BC: Theta(n)
 * Avg: Theta(n)
 */
int SortedBag::size() const {
    int nr_elem=0;
    Node* current = head;
    while (current != nullptr) {
        nr_elem++;
        current = current->next;
    }
    return nr_elem;
}

/*
 * WC: Theta(1)
 * BC: Theta(1)
 * Avg: Theta(1)
 */
bool SortedBag::isEmpty() const {
    return head == nullptr;
}

/*
 * WC: Theta(1)
 * BC: Theta(1)
 * Avg: Theta(1)
 */
SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}

/*
 * WC: Theta(n)
 * BC: Theta(1)
 * Avg: Theta(n)
 */
SortedBag::~SortedBag() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}
