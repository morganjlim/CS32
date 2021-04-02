#include "NewSequence.h"
#include <iostream>
using namespace std;

//Sequence::Sequence()
//	:m_size(0), m_maxSize(DEFAULT_MAX_ITEMS)
//{
//	s = new ItemType[m_maxSize];
//}

Sequence::Sequence(int maxSize)
{
	m_maxSize = maxSize;
	s = new ItemType[maxSize];
}

//destructor
Sequence::~Sequence()
{
	delete[] s;
}

//copy constructor
Sequence::Sequence(const Sequence &other)
{
	m_size = other.m_size;
	m_maxSize = other.m_maxSize;
	s = new ItemType[other.m_size + 1];
	for (int i = 0; i < other.m_size; i++)
	{
		s[i] = other.s[i];
	}
}

//equal operator
Sequence& Sequence::operator= (const Sequence& rhs)
{
	if (this != &rhs)
	{
		Sequence temp(rhs);
		swap(temp);
	}
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
	if (pos < 0 || pos > m_size || m_size == m_maxSize)
		return -1;

	for (int i = m_size; i > pos; i--)
	{
		s[i] = s[i - 1];
	}
	m_size++;
	s[pos] = value;
	return pos;
}
int Sequence::insert(const ItemType value)
{
	if (m_size == m_maxSize)
		return -1;

	int pos = 0, i = 0;
	bool found = false;
	while (found == false && i < m_size)
	{
		if (s[i] <= value)
		{
			pos = i;
			found = true;
		}
		i++;
	}

	if (found == false)
		pos = m_size;

	m_size++;

	for (int j = m_size - 1; j > pos; j--)
	{
		s[j] = s[j - 1];
	}

	s[pos] = value;

	return pos;
}
bool Sequence::erase(int pos)
{
	if (pos < 0 || pos > m_size)
		return false;
	if (pos != 0)
	{
		pos -= 1;
	}
	for (int i = pos; i < m_size - 1; i++)
	{
		s[i] = s[i + 1];
	}
	m_size--;
	return true;
}
int Sequence::remove(const ItemType& value)
{
	int amt(0);
	for (int i = 0; i < m_size; i++)
	{
		if (s[i] == value)
		{
			amt++;
			for (int j = i; j < m_size - 1; j++)
			{
				s[j] = s[j + 1];
			}
			i--;
			m_size--;
		}
	}
	return amt;
}
bool Sequence::get(int pos, ItemType& value) const
{
	if (pos < 0 || pos > m_size)
		return false;
	value = s[pos];
	return true;
}
bool Sequence::set(int pos, const ItemType& value)
{
	if (pos < 0 || pos > m_size)
		return false;
	s[pos] = value;
	return true;
}
int Sequence::find(const ItemType& value) const
{
	bool cont(true);
	int i(0), p(-1);
	while (cont && i < m_size)
	{
		if (s[i] == value)
		{
			p = i;
			cont = false;
		}
		i++;
	}
	return p;
}

void Sequence::swap(Sequence& other)
{
	ItemType *tempArr;
	
	tempArr = s;
	s = other.s;
	other.s = tempArr;
	
	int tempSize(m_size);
	m_size = other.m_size;
	other.m_size = tempSize;

	int tempMaxSize(m_maxSize);
	m_maxSize = other.m_maxSize;
	other.m_maxSize = tempMaxSize;
	
}

void Sequence::dump()
{
	for (int i = 0; i < m_size; i++)
	{
		cout << s[i] << endl;
	}
}