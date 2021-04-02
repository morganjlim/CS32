#ifndef HASH_H
#define HASH_H
#include <functional>
#include <vector>
#include <list>
#include "Node.h"
#define NUM_BUCKETS 1000
struct Node;

class HashTable
{
public:
	HashTable();
	~HashTable();
	void insert(int offset, string s);
	bool find(const string &s, Node *&p, int OffsetLast);
private:
	unsigned int HashFunc(const string &hashMe);
	list <Node>* m_arr[NUM_BUCKETS];
	Node* last;
};

#endif