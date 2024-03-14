#include "Map.h"
#include "Mapiterator2.h"
#include <exception>

using namespace std;

/* WC: Theta(1)
 * BC: Theta(1)
 * Avg: Theta(1)
*/
MapIterator2::MapIterator2(const Map &d, int arg) : map(d) {
    this->index = arg;
}

/* WC: Theta(1)
 * BC: Theta(1)
 * Avg: Theta(1)
*/
void MapIterator2::first2() {
    this->index = 0;
}

/* WC: Theta(1)
 * BC: Theta(1)
 * Avg: Theta(1)
*/
void MapIterator2::next2(int arg) {
    if (!valid2())
        throw exception();
    this->index = index + arg;
}

/* WC: Theta(1)
 * BC: Theta(1)
 * Avg: Theta(1)
*/
TElem MapIterator2::getCurrent2() {
    if (valid2())
        return map.vector[index];
    throw exception();
}

/* WC: Theta(1)
 * BC: Theta(1)
 * Avg: Theta(1)
*/
bool MapIterator2::valid2() const {
    if (this->index < map.nr_elem and this->index >= 0)
        return true;
    return false;
}
/* WC: Theta(1)
 * BC: Theta(1)
 * Avg: Theta(1)
*/
void MapIterator2::previous2(int arg) {
    if (!valid2())
        throw exception();
    this->index = index - arg;
}


