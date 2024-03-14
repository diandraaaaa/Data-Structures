#pragma once

#include "SortedMultiMap.h"


class SMMIteratorKey{
    friend class SortedMultiMap;
private:
    //DO NOT CHANGE THIS PART
    const SortedMultiMap& map;
    SMMIteratorKey(const SortedMultiMap& map);
    TKey* mapKeys; // Array to store the keys
    int pos; // Current position in the array

public:
    void first();
    void next();
    bool valid() const;
    TKey getCurrent() const;
};

