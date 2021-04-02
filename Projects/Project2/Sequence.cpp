#include "Sequence.h"
#include <iostream>


Sequence::Sequence()
	:m_size(0)
{
	m_head = new Node;
	m_head->m_prev = m_head;
	m_head->m_next = m_head;
}
Sequence::~Sequence()
{
	Node *p = m_head->m_next;
	Node *n = p;
	while(p!=m_head)
	{
		n = p->m_next;
		delete p;
		p = n;
	}
	delete m_head;
}
Sequence::Sequence(const Sequence& other)
	:m_size(0)
{
	if (other.empty())
	{
		m_head = new Node;
		m_head->m_prev = m_head;
		m_head->m_next = m_head;
	}
	else
	{
		m_head = new Node;
		m_head->m_prev = m_head;
		m_head->m_next = m_head;
		m_head->m_data = other.m_head->m_data;
		Node *p = other.m_head;
		for (int i = 0; i < other.m_size; i++)
		{
			p = p->m_next;
			addToBack(p->m_data);
		}

	}
	
}
Sequence& Sequence::operator=(const Sequence& other)
{
	if (this == &other)
		return *this;
	int size = other.m_size;
	Sequence temp;
	ItemType testValue;
	for (int k = 0; k < size; k++)
	{
		other.get(k, testValue);
		temp.insert(k, testValue);
	}
	swap(temp);
	return *this;
}
bool Sequence::empty() const
{
	if (m_size == 0)
		return true;
	else
		return false;
}
int Sequence::size() const
{
	return m_size;
}
int Sequence::insert(int pos, const ItemType& value)
{
	if (pos < 0 || pos > m_size)
		return -1;
	if (pos == 0 || m_size == 0)
	{
		addToFront(value);
		return 0;
	}
	if (pos == m_size)
		addToBack(value);
	else
	{
		Node *n = new Node;
		Node* p = m_head;
		for (int i = 0; i < pos; i++)
			p = p->m_next;
		//Node* prev = p->m_prev;
		//Node* next = p->m_next;
		n->m_data = value;
		n->m_prev = p->m_prev;
		n->m_next = p;
		p->m_prev->m_next = n;
		p->m_prev = n;

		m_size++;
	}
	return pos;
}
int Sequence::insert(const ItemType value)
{
	int pos = 0;
	bool found = false;
	if (empty())
	{
		addToFront(value);
		return 0;
	}
	Node* p = m_head;
	do
	{
		if (value <= p->m_data)
			found = true;
		else
		{
			p = p->m_next;
			pos++;
		}

	} while (p != m_head && !found);

	if (found == false)
	{
		addToBack(value);
		return m_size - 1;
	}

	if (pos == 0)
	{
		addToFront(value);
		return 0;
	}

	Node* n = new Node;

	n->m_data = value;
	n->m_next = p;
	n->m_prev = p->m_prev;
	p->m_prev = n;
	n->m_prev->m_next = n;

	m_size++;

	return pos;
}
bool Sequence::erase(int pos)
{
	if (pos < 0 || pos > m_size - 1)
		return false;

	Node* p = m_head;
	for (int i = 0; i < pos; i++)
		p = p->m_next;

	if (pos == 0)
		m_head = p->m_next;
	p->m_prev->m_next = p->m_next;
	p->m_next->m_prev = p->m_prev;
	

	delete p;
	m_size--;

	return true;
}
int Sequence::remove(const ItemType& value)
{
	int amt(0);
	Node *p = m_head;
	for (int i = 0; i < m_size; i++)
	{
		if (p->m_data == value)
		{
			p->m_prev->m_next = p->m_next;
			p->m_next->m_prev = p->m_prev;

			if (i == 0)
				m_head = p->m_next;
			Node* trash = p;
			p = p->m_next;
			delete trash;
			amt++;
			m_size--;
			if (i == 0)
			
			i--;
		}
		else
		{
			p = p->m_next;
		}
	}
	return amt;
}
bool Sequence::get(int pos, ItemType& value) const
{
	if (pos < 0 || pos > m_size - 1)
		return false;
	Node *p = m_head;
	if (pos == 0)
	{
		value = m_head->m_data;
		return true;
	}
	p = p->m_next;
	for (int i = 1; p != m_head && i < pos; i++)
		p = p->m_next;
	value = p->m_data;
	return true;
}
bool Sequence::set(int pos, const ItemType& value)
{
	if (pos < 0 || pos > m_size)
		return false;
	Node* p = m_head;
	for (int i = 0; i < pos && p->m_next != m_head; i++)
		p = p->m_next;
	p->m_data = value;
	return true;
}
int Sequence::find(const ItemType& value) const
{
	int position(1);
	if (empty())
		return -1;
	if (m_head->m_data == value)
		return 0;
	Node* p;
	for (p = m_head->m_next; p != m_head; p = p->m_next)
	{
		if (p->m_data == value)
		{
			break;
		}
		position++;
	}

	return position;
}
void Sequence::swap(Sequence& other)
{
	Node *temp_head = m_head;
	m_head = other.m_head;
	other.m_head = temp_head;

	int tempSize(m_size);
	m_size = other.m_size;
	other.m_size = tempSize;
}
void Sequence::dump()
{
	Node *p = m_head;
	do
	{
		cout << p->m_data << ", ";
		p = p->m_next;
	} while (p != m_head);

	cout << endl;
}
void Sequence::addToFront(ItemType value)
{
	if (m_size == 0)
	{
		m_head->m_data = value;
		m_size++;
	}
	else
	{
		Node *p = new Node();
		p->m_data = value;
		p->m_next = m_head;
		p->m_prev = m_head->m_prev;
		m_head->m_prev->m_next = p;
		m_head->m_prev = p;
		m_head = p;
		m_size++;
	}
}
void Sequence::addToBack(ItemType value)
{
	if (m_size == 0)
		addToFront(value);
	else
	{
		Node *p = m_head;
		do
		{
			p = p->m_next;
		}while (p->m_next != m_head);
		Node *n = new Node;
		n->m_data = value;
		p->m_next = n;

		n->m_prev = p;
		n->m_next = m_head;

		m_head->m_prev = n;
		m_size++;
	}
}
int subsequence(const Sequence& seq1, const Sequence& seq2)
{
	if (seq2.empty())
		return -1;
	else if (seq2.size() > seq1.size())
		return -1;
	ItemType seeking, comp;
	seq2.get(0, seeking);
	//looking for a value that is equal to the first value in seq2
	for (int i = 0; i < seq1.size(); i++)
	{
		//get value at i for seq2
		seq1.get(i, comp);
		//compare the two values
		//if i + seq2.size() > seq1.size() return -1
		if (comp == seeking)
		{
			if (i + seq2.size() > seq1.size())
				return -1;
			else
			{
				//if equal, check the next all the way until the end of seq2
				for (int j = 0; j < seq2.size(); j++)
				{
					seq2.get(j, seeking);
					seq1.get(i + j, comp);
					if (comp != seeking)
					{
						return -1;
					}
				}
				return i;
			}
		}
	}
	return -1;
}
void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result)
{
	ItemType val;
	int count(0);

	if (seq1.empty())
		result = seq2;
	if (seq2.empty())
		result = seq1;

	else if(!seq2.empty() && !seq1.empty())
	{
		for (int i = 0; i < seq1.size() + seq2.size(); i++)
		{
			if (seq1.get(i, val))
			{
				result.insert(count, val);
				count++;
			}
			if (seq2.get(i, val))
			{
				result.insert(count, val);
				count++;
			}
		}
	}
}
