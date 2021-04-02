#ifndef NODE_H
#define NODE_H
#include <string>
using namespace std;

struct Node
{
	string m_data;
	Node* m_next;
	int m_offset;
	int offset() { return m_offset; };
	string data() { return m_data; };
	Node* next() { return m_next; };
};

#endif