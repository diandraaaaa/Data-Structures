#include <exception>
#include "ListIterator.h"
#include "IteratedList.h"

using namespace std;

/*
 * WC: Theta(1)
 * BC: Theta(1)
 * Avg: Theta(1)
 */
IteratedList::IteratedList() {
    this->capacity = 10;
    this->elems = new TElem[this->capacity];
    this->next = new TElem[this->capacity];
    this->head = -1;
    this->firstEmpty = 0;
}

/*
 * WC: Theta(n)
 * BC: Theta(1)
 * Avg: Theta(n)
 */
int IteratedList::size() const {
    int count = 0;
    int current = this->head;
    while (current != -1) {
        count++;
        current = this->next[current];
    }
    return count;
}

/*
 * WC: Theta(1)
 * BC: Theta(1)
 * Avg: Theta(1)
 */
bool IteratedList::isEmpty() const {
    if (this->head == -1)
        return true;

    return false;
}

/*
 * WC: Theta(1)
 * BC: Theta(1)
 * Avg: Theta(1)
 */
ListIterator IteratedList::first() const {
    return ListIterator(*this);
}

/*
 * WC: Theta(1)
 * BC: Theta(1)
 * Avg: Theta(1)
 */
TElem IteratedList::getElement(ListIterator pos) const {
    if (pos.valid()) { // check if the iterator is valid
        return pos.getCurrent();
    } else {
        throw exception();
    }
}

/*
 * WC: Theta(n)
 * BC: Theta(1)
 * Avg: Theta(n)
 */
TElem IteratedList::remove(ListIterator &pos) {
    if (pos.valid() == false)
        throw exception();
    int current = this->head;
    int prev = -1;
    while (current != pos.currentElem) {
        prev = current;
        current = this->next[current];
    }
    if (prev == -1) {
        this->head = this->next[current];
    } else {
        this->next[prev] = this->next[current];
    }
    this->next[current] = this->firstEmpty;
    this->firstEmpty = current;
    pos.currentElem = this->next[current];
    return this->elems[current];

}

/*
 * WC: Theta(n)
 * BC: Theta(1)
 * Avg: Theta(n)
 */
ListIterator IteratedList::search(TElem e) const {

    int current = this->head;
    while (current != -1) {
        if (this->elems[current] == e) {
            return ListIterator(*this, current);
        }
        current = this->next[current];
    }
}

/*
 * WC: Theta(1)
 * BC: Theta(1)
 * Avg: Theta(1)
 */
TElem IteratedList::setElement(ListIterator pos, TElem e) {

    if (pos.valid() == false)
        throw exception();

    TElem old = pos.getCurrent();
    this->elems[pos.getCurrent()] = e;
    return old;
}

/*
 * WC: Theta(1)
 * BC: Theta(1)
 * Avg: Theta(1)
 */
void IteratedList::addToPosition(ListIterator &pos, TElem e) {
    if (pos.valid() == false)
        throw exception();


    this->elems[this->firstEmpty] = e;
    this->next[this->firstEmpty] = this->next[pos.];
    this->next[pos.getCurrent()] = this->firstEmpty;
    this->firstEmpty++;
    pos.next();
}


/*
 * WC: Theta(n)
 * BC: Theta(1)
 * Avg: Theta(n)
 */
void IteratedList::addToEnd(TElem e) {
    if (this->capacity == this->size()) {
        this->resize();
    }
    this->elems[this->firstEmpty] = e;
    this->next[this->firstEmpty] = -1;
    if (this->head == -1) {
        this->head = this->firstEmpty;
    } else {
        int current = this->head;
        while (this->next[current] != -1) {
            current = this->next[current];
        }
        this->next[current] = this->firstEmpty;
    }
    this->firstEmpty++;
    this->elems[this->firstEmpty] = e;
    this->next[this->firstEmpty] = -1;
    this->capacity++;

}

/*
 * WC: Theta(1)
 * BC: Theta(1)
 * Avg: Theta(1)
 */
void IteratedList::addToBeginning(TElem e) {
    if (this->capacity == 0) {
        this->capacity = 1;
        this->elems = new TElem[this->capacity];
        this->next = new TElem[this->capacity];
        this->head = -1;
        this->firstEmpty = 0;
    } else {
        this->elems[this->firstEmpty] = e;
        this->next[this->firstEmpty] = this->head;
        this->head = this->firstEmpty;
        this->firstEmpty++;
        this->capacity++;
    }
}

void IteratedList::resize() {
    TElem *newElems = new TElem[this->capacity * 2];
    TElem *newNext = new TElem[this->capacity * 2];
    for (int i = 0; i < this->capacity; i++) {
        newElems[i] = this->elems[i];
        newNext[i] = this->next[i];
    }
    for (int i = this->capacity; i < this->capacity * 2; i++) {
        newNext[i] = i + 1;
    }
    newNext[this->capacity * 2 - 1] = -1;
    delete[] this->elems;
    delete[] this->next;
    this->elems = newElems;
    this->next = newNext;
    this->capacity *= 2;
    this->firstEmpty = this->capacity / 2;
}

/*
 * WC: Theta(1)
 * BC: Theta(1)
 * Avg: Theta(1)
 */
IteratedList::~IteratedList() {

    delete[] this->elems;
    delete[] this->next;
}

IteratedList IteratedList::reverse() const {
    IteratedList reversedList;

    for (int i = 0; i < this->size(); i++) {
        reversedList.addToBeginning(this->elems[this->size() - i]);
    }

    return reversedList;
}