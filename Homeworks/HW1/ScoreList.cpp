#include "ScoreList.h"

ScoreList::ScoreList()
{
}


// If the score is valid (a value from 0 to 100) and the score list
// has room for it, add it to the score list and return true.
// Otherwise, leave the score list unchanged and return false.
bool ScoreList::add(unsigned long score)
{
	if (score <= 100)
	{
		if (m_sequence.size() < 250)
		{
			m_sequence.insert(score);
			return true;
		}
	}
	return false;
}

// Remove one instance of the specified score from the score list.
// Return true if a score was removed; otherwise false.
bool ScoreList::remove(unsigned long score)
{
	bool removed(false);
	int pos = m_sequence.find(score);
	if (pos == -1)
		return false;
	else
		removed = m_sequence.erase(pos+1);
	return removed;
}

// Return the number of scores in the list.
int ScoreList::size() const
{
	return m_sequence.size();
}

// Return the lowest score in the score list.  If the list is
// empty, return NO_SCORE.
unsigned long ScoreList::minimum() const
{
	if (m_sequence.empty())
		return NO_SCORE;
	ItemType min(0), comp(0);
	m_sequence.get(0, min);
	int size = m_sequence.size();
	for (int i = 0; i < size; i++)
	{
		m_sequence.get(i, comp);
		if (comp < min)
			m_sequence.get(i, min);
	}
	return min;
}

// Return the highest score in the score list.  If the list is
// empty, return NO_SCORE.
unsigned long ScoreList::maximum() const
{
	if (m_sequence.empty())
		return NO_SCORE;
	ItemType max(0), comp(0);
	m_sequence.get(0, max);
	int size = m_sequence.size();
	for (int i = 0; i < size; i++)
	{
		m_sequence.get(i, comp);
		if (comp > max)
			m_sequence.get(i, max);
	}
	return max;
}
