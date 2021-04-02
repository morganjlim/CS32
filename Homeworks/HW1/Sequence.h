#ifndef SEQUENCE_H
#define SEQUENCE_H
#include <string>
using ItemType = unsigned long;
const int DEFAULT_MAX_ITEMS = 250;

class Sequence
{
public:

	Sequence();
	bool empty() const;
	int size() const;
	int insert(int pos, const ItemType& value);
	int insert(const ItemType value);
	bool erase(int pos);
	int remove(const ItemType& value);
	bool get(int pos, ItemType& value) const;
	bool set(int pos, const ItemType& value);
	int find(const ItemType& value) const;
	void swap(Sequence& other);
private:
	int m_size;
	ItemType s[DEFAULT_MAX_ITEMS];

};

#endif