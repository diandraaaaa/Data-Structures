#pragma once

#include "SortedMultiMap.h"


class SMMIterator{
	friend class SortedMultiMap;
private:
	//DO NOT CHANGE THIS PART
	const SortedMultiMap& map;
	explicit SMMIterator(const SortedMultiMap& map);
    int pos;
    TElem* mapElems;

public:
	void first();
	void next();
	bool valid() const;
   	TElem getCurrent() const;
};

