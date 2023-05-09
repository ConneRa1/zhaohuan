#include "Cost.h"
Cost::Cost() {

}
Cost::Cost(int n, pair<ElementType, int>p...) {
	for (int i = 0; i < n; i++) {
		m.insert((&p)[i]);
	}
}

Cost::Cost(const Cost& c) {
	m = c.m;
}
Cost::Cost(map<ElementType, int> map) {
	m = map;
}

Cost Cost:: operator-(Cost c) {
	map<ElementType, int>temp = this->m;
	for (auto it = c.m.begin(); it != c.m.end(); it++) {
		temp[(*it).first] -= (*it).second;
		/*if ((*it).first != ElementType::cai) {
			if (temp[(*it).first] >= (*it).second) {
				temp[(*it).first] -= (*it).second;
			}
			else if (temp[(*it).first] + temp[ElementType::cai] >= (*it).second) {
				temp[ElementType::cai] -= (*it).second - temp[(*it).first];
				temp[(*it).first] = 0;
			}
		}*/
	}
	/*int n = c.m[ElementType::cai];
	for (auto it = temp.begin(); it != temp.end(); it++) {
		if ((*it).second > n)
			(*it).second -= n;
		else
			(*it).second = 0;
		n -= (*it).second;
		if (n <= 0)
			break;
	}*/
	Cost r(temp);
	return r;
}

Cost Cost:: operator+(Cost c) {
	map<ElementType, int>temp = this->m;
	for (auto it = c.m.begin(); it != c.m.end(); it++) {
		temp[(*it).first] += (*it).second;
	}
	/*for (auto it = temp.begin(); it != temp.end(); it++) 
	{
		for (auto i = c.m.begin(); i != c.m.end(); i++)
		{
			if ( (*it).first ==(*i).first)
			{
				(*it).second += (*i).second;
				(*i).second = 0;
			}
		}
	}*/
	Cost r(temp);
	return r;
}


bool Cost:: operator>=(Cost c) {
	map<ElementType, int>temp = this->m;
	for (auto it = c.m.begin(); it != c.m.end(); it++) {
		if ((*it).first != ElementType::cai) {
			if (temp[(*it).first] >= (*it).second)
				temp[(*it).first] -= (*it).second;
			else if (temp[(*it).first] + temp[ElementType::cai] >= (*it).second) {
				temp[(*it).first] = 0;
				temp[ElementType::cai] -= (*it).second - temp[(*it).first];
			}
			else
				return false;
		}
	}
	int n = c.m[ElementType::cai];
	for (auto it = temp.begin(); it != temp.end(); it++) {
		n -= (*it).second;
		if (n <= 0)
			return true;
	}
	return false;
}

int Cost::getSize()
{
	map<ElementType, int>temp = this->m;
	int count = 0;
	for (auto it = temp.begin(); it != temp.end(); it++)
	{
		count += (*it).second;
	}
	return count;
}