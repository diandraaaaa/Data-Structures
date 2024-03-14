#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

/*
 * WC: Theta(1)
 * BC: Theta(1)
 * Avg: Theta(1)
 */
SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
    current = bag.head;
}

/*
 * WC: Theta(1)
 * BC: Theta(1)
 * Avg: Theta(1)
 */
TComp SortedBagIterator::getCurrent() {
    if (valid()) {
        return current->data;
    } else
        throw exception();
}
/*
 * WC: Theta(1)
 * BC: Theta(1)
 * Avg: Theta(1)
 */
bool SortedBagIterator::valid() {
    if (current != nullptr)
        return true;
	return false;
}

/*
 * WC: Theta(1)
 * BC: Theta(1)
 * Avg: Theta(1)
 */
void SortedBagIterator::next() {
    if (valid())
        current = current->next;
    else
        throw exception();

}

/*
 * WC: Theta(1)
 * BC: Theta(1)
 * Avg: Theta(1)
 */
void SortedBagIterator::first() {
    current = bag.head;
}

/*
 * WC: Theta(1)
 * BC: Theta(1)
 * Avg: Theta(1)
 */
/*
 * pre cond: sortedbag, current valid
 * post cond: sortedbag, element current sters
 */
void SortedBagIterator::deleteCurrent() {
    // Check if the iterator is valid
    if (!valid())
        throw exception();
    else
    {
        // Get pointers to the previous and next nodes
        Node* prev_node = this->current->prev;
        Node* next_node = this->current->next;
        // Update the previous node's "next" pointer to skip the current node
        if (prev_node != nullptr) {
            prev_node->next = next_node;
        }
        // If the current node is the head of the list, update the head pointer
//       else
//            bag.head = next_node;
        // Update the next node's "prev" pointer to skip the current node
        if (next_node != nullptr)
            next_node->prev = prev_node;
        // If the current node is the tail of the list, update the tail pointer
//        else
//            bag.tail = prev_node;

        // Delete the current node and update the iterator to point to the next node
        delete this->current;
        this->current = next_node;
          }

    }

