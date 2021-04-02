#ifndef SEQUENCE_H
#define SEQUENCE_H
#include <string>
using ItemType = unsigned long;
const int DEFAULT_MAX_ITEMS = 250;

class Sequence
{
public:

	//Sequence();
	Sequence(int maxSize = DEFAULT_MAX_ITEMS);
	~Sequence();
	Sequence(const Sequence &other);
	Sequence& operator= (const Sequence& rhs);
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
	void dump();
private:
	int m_size = 0, m_maxSize;
	ItemType *s = nullptr;

};

#endif