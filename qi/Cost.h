#pragma once
#include "base.h"

class Cost {
public:
	Cost();
	Cost(int n, pair<ElementType, int>p...);
	Cost(map<ElementType, int> map);
	Cost(const Cost& c);
	Cost operator-(Cost c);
	Cost operator+(Cost c);
	bool operator>=(Cost c);
	map<ElementType, int> m;
	int getSize();
};