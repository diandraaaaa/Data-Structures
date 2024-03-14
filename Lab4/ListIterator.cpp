#include "ListIterator.h"
#include "IteratedList.h"
#include <exception>

/*
 * WC: Theta(1)
 * BC: Theta(1)
 * Avg: Theta(1)
 */
ListIterator::ListIterator(const IteratedList& list, int index) : list(list), currentElem(index) {}

/*
 * WC: Theta(1)
 * BC: Theta(1)
 * Avg: Theta(1)
 */
ListIterator::ListIterator(const IteratedList& list) : list(list) {
    this->currentElem = list.head;
}

/*
 * WC: Theta(1)
 * BC: Theta(1)
 * Avg: Theta(1)
 */
void ListIterator::first() {
    this->currentElem = list.head;
}

/*
 * WC: Theta(1)
 * BC: Theta(1)
 * Avg: Theta(1)
 */
void ListIterator::next() {
    if(!valid())
        throw std::exception();
    this->currentElem = list.next[currentElem];
}

/*
 * WC: Theta(1)
 * BC: Theta(1)
 * Avg: Theta(1)
 */
bool ListIterator::valid() const {
    if(this->currentElem != -1)
        return true;
    return  false;
}

/*
 * WC: Theta(1)
 * BC: Theta(1)
 * Avg: Theta(1)
 */
TElem ListIterator::getCurrent() const {
    if(!valid())
        throw std::exception();
    return list.elems[currentElem];
}



