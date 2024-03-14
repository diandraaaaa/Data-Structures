#include "Map.h"
#include "MapIterator.h"
#include <exception>

using namespace std;


MapIterator::MapIterator(const Map &d) : map(d) {
    this->index = 0;
}


void MapIterator::first() {
    this->index = 0;
}


void MapIterator::next() {
    if (!valid())
        throw exception();
    this->index++;
}


TElem MapIterator::getCurrent() {
    if (valid())
        return map.vector[index];
    throw exception();
}


bool MapIterator::valid() const {
    if (this->index < map.nr_elem and this->index >= 0)
        return true;
    return false;
}



