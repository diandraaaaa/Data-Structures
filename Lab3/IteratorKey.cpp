#include "IteratorKey.h"
#include "SortedMultiMap.h"
#include <exception>


/*
 * WC: Theta(n^2)
 * BC: Theta(n^2)
 * Avg: Theta(n^2)
 */
SMMIteratorKey::SMMIteratorKey(const SortedMultiMap& d) : map(d) {
    // Allocate memory for an array to store the map keys
    mapKeys = new TKey[d._size];

    // Initialize the position to 0
    pos = 0;

    // Traverse the map's hash table and copy the keys into the array
    for (int currentBucket = 0; currentBucket < map.capacity; ++currentBucket) {
        if (map.table[currentBucket] == nullptr) {
            continue; // Skip empty buckets
        }

        // Start from the first node in the current bucket
        SortedMultiMap::Node* currentNode = map.table[currentBucket];
        while (currentNode != nullptr) {
            // Copy the key into the array
            mapKeys[pos++] = currentNode->key;
            currentNode = currentNode->next;
        }
    }

    // Sort the keys in ascending order based on the map's relation
    for (int i = 0; i < d._size - 1; ++i) {
        for (int j = i + 1; j < d._size; ++j) {
            // Check if the relation between the keys requires swapping
            if (!map.relation(mapKeys[i], mapKeys[j])) {
                // Swap the keys
                TKey aux = mapKeys[i];
                mapKeys[i] = mapKeys[j];
                mapKeys[j] = aux;
            }
        }
    }

    // Start the iterator at the first key
    first();
}

/*
 * WC: Theta(1)
 * BC: Theta(1)
 * Avg: Theta(1)
 */
/*
 * pre: container
 * post: index=0
 */
void SMMIteratorKey::first() {
    pos = 0;
}

/*
 * WC: Theta(1)
 * BC: Theta(1)
 * Avg: Theta(1)
 */
/*
 * pre: container, valid
 * post: index=index+1
 */
void SMMIteratorKey::next() {
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
/*
 * pre: container
 * post: true/false
 */
bool SMMIteratorKey::valid() const {
    if (map._size == 0)
        return false;

    return pos < map._size;
}

/*
 * WC: Theta(1)
 * BC: Theta(1)
 * Avg: Theta(1)
 */
/*
 * pre: container
 * post: index
 */
TKey SMMIteratorKey::getCurrent() const {
    // Check if the iterator is already at the end
    if (!valid()) {
        throw std::exception();
    }

    return mapKeys[pos];
}