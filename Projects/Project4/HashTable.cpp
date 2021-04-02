#include "HashTable.h"

HashTable::HashTable()
	:last(nullptr)
{
	for (int i = 0; i < NUM_BUCKETS; i++)
		m_arr[i] = nullptr;
}

//insert function
void HashTable::insert(int offset, string s)
{
	//set node data members
	Node p;
	p.m_data = s;
	p.m_next = nullptr;
	p.m_offset = offset;

	//determine hash value
	int arrVal = HashFunc(s);
	
	//if the bucket is empty create a new list there
	if (m_arr[arrVal] == nullptr)
	{
		m_arr[arrVal] = new list<Node>;
	}

	//add the list
	m_arr[arrVal]->push_back(p);

	//change the last node to most recently added node
	if (last != nullptr)
		last->m_next = &(m_arr[arrVal])->back();
	last = &(m_arr[arrVal])->back();
}

//destructor
HashTable::~HashTable()
{
	for (int i = 0; i < NUM_BUCKETS; i++)
	{
		if (m_arr[i] != nullptr)
			delete m_arr[i];
	}
}

//find function
bool HashTable::find(const string &s, Node *&p, int OffsetLast)
{
	//determine hash value
	int arrVal = HashFunc(s);
	if (m_arr[arrVal] == nullptr)
		return false;

	//look for match
	for (list<Node>::iterator i = m_arr[arrVal]->begin(); i != m_arr[arrVal]->end(); i++)
	{
		if ( (*i).m_data == s && (*i).m_offset > OffsetLast)
		{
			p = &(*i);
			return true;
		}
	}
	return false;
}

//hash functino to determine hash value
unsigned int HashTable::HashFunc(const string &s)
{
	hash<string> str_hash;
	unsigned int hashValue = str_hash(s);
	return hashValue % NUM_BUCKETS;
}