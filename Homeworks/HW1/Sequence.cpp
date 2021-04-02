#include "Sequence.h"

Sequence::Sequence()
	:m_size(0)
{}
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
	if (pos < 0 || pos > m_size || m_size == DEFAULT_MAX_ITEMS)
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
	if (m_size == DEFAULT_MAX_ITEMS)
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
			m_size--;
			i--;
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
	ItemType tempArr[DEFAULT_MAX_ITEMS], val;
	int tempSize(m_size);

	for (int i = 0; i < m_size; i++)
	{
		tempArr[i] = s[i];
	}

	//copying members from other sequence into this sequence
	
	for (int i = 0; i < other.size(); i++)
	{
		other.get(i, val);
		s[i] = val;
	}

	m_size = other.size();
	other.m_size = tempSize;

	for (int i = 0; i <= other.size(); i++)
	{
		other.set(i, tempArr[i]);
	}
}
