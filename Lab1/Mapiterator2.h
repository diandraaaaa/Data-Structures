#pragma once
#include "Map.h"
class MapIterator2
{
	//DO NOT CHANGE THIS PART
	friend class Map;
private:
	const Map& map;
    int index;

	MapIterator2(const Map& m, int arg);
public:
	void first2();
	void next2(int arg);
	TElem getCurrent2();
	bool valid2() const;
    void previous2(int arg);
};


