#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <exception>


/*
 * WC: Theta(n^2)
 * BC: Theta(n^2)
 * Avg: Theta(n^2)
 */
SMMIterator::SMMIterator(const SortedMultiMap &d) : map(d) {
    // Allocate memory for an array to store the map elements
    mapElems = new TElem[d._size];

    // Initialize the position to 0
    pos = 0;

    // Traverse the map's hash table and copy the elements into the array
    for (int currentBucket = 0; currentBucket < map.capacity; ++currentBucket) {
        if (map.table[currentBucket] == nullptr) {
            continue; // Skip empty buckets
        }

        // Start from the first node in the current bucket
        SortedMultiMap::Node *currentNode = map.table[currentBucket];
        while (currentNode != nullptr) {
            // Copy the key-value pair into the array
            mapElems[pos++] = {currentNode->key, currentNode->value};
            currentNode = currentNode->next;
        }
    }

    // Sort the elements in ascending order based on the map's relation
    for (int i = 0; i < d._size - 1; ++i) {
        for (int j = i + 1; j < d._size; ++j) {
            // Check if the relation between the keys requires swapping
            if (!map.relation(mapElems[i].first, mapElems[j].first)) {
                // Swap the elements
                TElem aux = mapElems[i];
                mapElems[i] = mapElems[j];
                mapElems[j] = aux;
            }
        }
    }

    // Start the iterator at the first element
    first();
}


/*
 * WC: Theta(1)
 * BC: Theta(1)
 * Avg: Theta(1)
 */
void SMMIterator::first() {
    pos = 0;
}

/*
 * WC: Theta(1)
 * BC: Theta(1)
 * Avg: Theta(1)
 */
void SMMIterator::next() {
    // Check if the iterator is already at the end
    if (!valid()) {
        throw std::exception();
    }

    ++pos;
}

/*
 * WC: Theta(1)
 * BC: Theta(1)
 * Avg: Theta(1)
 */
bool SMMIterator::valid() const {
    if(map._size==0)
        return false;

    return pos < map._size;
}

/*
 * WC: Theta(1)
 * BC: Theta(1)
 * Avg: Theta(1)
 */
TElem SMMIterator::getCurrent() const {
    // Check if the iterator is already at the end
    if (!valid()) {
        throw std::exception();
    }

    return mapElems[pos];
}



