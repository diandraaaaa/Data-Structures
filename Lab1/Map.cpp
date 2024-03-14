#include "Map.h"
#include "MapIterator.h"
#include "Mapiterator2.h"

/*
 * WC: Theta(1)
 * BC: Theta(1)
 * Avg: Theta(1)
 */
Map::Map() {
    this->nr_elem=0;
    this->cap=2;
    vector=new TElem[cap];
}

/*
 * BC: Theta(1)
 * WC: Theta(n)
 * Avg: O(n)
 */
TValue Map::add(TKey c, TValue v){
    TValue x;
    if(nr_elem == cap)
        resize();
    for(int i=0; i<nr_elem; i++){
        if(vector[i].first == c) {
            x = vector[i].second;
            vector[i].second = v;
            return x;
        }
    }
    vector[nr_elem].first=c;
    vector[nr_elem].second=v;
    nr_elem++;
	return NULL_TVALUE;
}

/*
 * BC: Theta(1)
 * WC: Theta(n)
 * Avg: O(n)
 */
TValue Map::search(TKey c) const{
    for(int i=0; i<nr_elem; i++){
        if(vector[i].first == c)
            return c;
    }
	return NULL_TVALUE;
}

/*
 * WC: Theta(n)
 * BC: Theta(1)
 * Avg: O(n)
 */
TValue Map::remove(TKey c){
    TValue x;
    for(int i=0; i<nr_elem; i++){
        if(vector[i].first == c) {
            x=vector[i].second;
            for (int j = i; j < nr_elem - 1; ++j) {
                vector[j] = vector[j + 1];
            }
            nr_elem--;
            return x;
        }
    }
	return NULL_TVALUE;
}

/*
 * WC: Theta(1)
 * BC: Theta(1)
 * Avg: Theta(1)
 */
int Map::size() const {
	return nr_elem;
}

/*
 * WC: Theta(1)
 * BC: Theta(1)
 * Avg: Theta(1)
 */
bool Map::isEmpty() const{
    if(nr_elem==0)
        return true;
	return false;
}

MapIterator Map::iterator() const {
	return MapIterator(*this);
}
MapIterator2 Map::iterator2() const {
	return MapIterator2(*this, 0);
}

Map::~Map() {
    delete[]vector;
}

/*
 * WC: Theta(n)
 * BC: Theta(n)
 * Avg: Theta(n)
 */
void Map::resize() {
    TElem *new_vector = new TElem[2 * cap];
    for (int i = 0; i < cap; ++i) {
        new_vector[i] = vector[i];
    }

    cap = 2 * cap;
    delete[] vector;
    vector = new_vector;
}