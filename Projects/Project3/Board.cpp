#include "Board.h"

Board::Board(int nHoles, int nInitialBeansPerHole)
	: m_holes(nHoles), m_nInitialBeansPerHole(nInitialBeansPerHole)
{
	//if the entered amount of holes is less than one
	//treat it as if it was 1
	if (nHoles <= 0)
		m_holes = 1;
	//if entered amount of beans was negative treat it as if it was 0
	if (nInitialBeansPerHole < 0)
		m_nInitialBeansPerHole = 0;
	//dynamically allocate memory for the two arrays
	southHoles = new int[nHoles + 1];
	northHoles = new int[nHoles + 1];
	//the pot for each side is the first index of each array
	southHoles[0] = 0;
	northHoles[0] = 0;
	//"fill" each hole on the board with beans
	for (int i = 1; i <= nHoles; i++)
	{
		southHoles[i] = m_nInitialBeansPerHole;
		northHoles[i] = m_nInitialBeansPerHole;
	}
}

Board::~Board()
{
	delete[] southHoles;
	delete[] northHoles;
}

Board::Board(const Board &other)
{
	//copy data
	m_holes = other.m_holes;
	m_nInitialBeansPerHole = other.m_nInitialBeansPerHole;
	//allocate new memory for the copied arrays
	southHoles = new int[other.m_holes + 1];
	northHoles = new int[other.m_holes + 1];
	//copy data
	for (int i = 0; i <= other.m_holes; i++)
	{
		southHoles[i] = other.southHoles[i];
		northHoles[i] = other.northHoles[i];
	}
}

int Board::holes() const
{
	return m_holes;
}

int Board::beans(Side s, int hole) const
{
	//if the hole is invalid return -1
	if (hole > m_holes || hole < 0)
		return -1;
	//otherwise determine the array to use
	int *p = determineSide(s);
	//return the amount of beans in that hole
	return p[hole];
}

int Board::beansInPlay(Side s) const
{
	//for every hole on the side s add it to count
	int count(0);
	for (int i = 1; i <= m_holes; i ++)
		count += beans(s, i);
	return count;
}

int Board::totalBeans() const
{
	//add up the beans in play for both sides and the pots
	return beansInPlay(NORTH) + beansInPlay(SOUTH) + northHoles[0] + southHoles[0];
}

bool Board::sow(Side s, int hole, Side& endSide, int& endHole)
{
	//if the hole picked is a pot or invalid, return false
	if (beans(s, hole) <= 0 || hole == 0)
		return false;
	int *originalSide = determineSide(s);
	int *currentSide = determineSide(s);
	int numBeans = originalSide[hole];
	Side startingSide = s;
	currentSide[hole] = 0;

	//if sowing in the last hole of either side,
	//first sow that bean and indicate that the
	//hole it was placed in is the pot
	if (hole == 1 && s == NORTH)
	{
		northHoles[0]++;
		numBeans--;
		hole = 0;
	}
	else if (hole == m_holes && s == SOUTH)
	{
		southHoles[0]++;
		numBeans--;
		hole = 0;
	}

	//while there are still beans
	while (numBeans != 0)
	{
		//edge cases for the north side
		if (hole == 1 && s == NORTH)
		{
			//if it's the last hole on the player's side
			if (s == startingSide)
			{
				if (numBeans == 1)
				{
					northHoles[0]++;
					numBeans--;
					hole = 0;
				}
				else
				{
					s = opponent(s);
					currentSide = determineOppSide(currentSide);
					hole = 1;
					currentSide[hole]++;
					originalSide[0]++;
					numBeans -= 2;
				}
			}
			//if its the last hole on the opponent's side
			else
			{
				s = opponent(s);
				currentSide = determineOppSide(currentSide);
				hole = 1;
				currentSide[hole]++;
				numBeans--;
			}
		}
		//edge cases for the south side
		else if (hole == m_holes && s == SOUTH)
		{
			//if it's the last hole on the player's side
			if (s == startingSide)
			{
				if (numBeans == 1)
				{
					southHoles[0]++;
					numBeans--;
					hole = 0;
				}
				else
				{
					s = opponent(s);
					hole = m_holes;
					currentSide = determineOppSide(currentSide);
					currentSide[hole]++;
					originalSide[0]++;
					numBeans -= 2;
				}
			}
			//if it's the last hole on the opponent's side
			else
			{
				s = opponent(s);
				currentSide = determineOppSide(currentSide);
				hole = m_holes;
				currentSide[hole]++;
				numBeans--;
			}
		}
		//otherwise if it not on the edges
		else
		{
			if (s == SOUTH)
			{
				//if the bean was last placed in a pot
				//change the side that the bean is one
				//and update the hole to the first hole
				//of the other side
				if (hole == 0)
				{
					hole = m_holes;
					s = NORTH;
					currentSide = northHoles;
				}
				else
					hole++;
				currentSide[hole] += 1;
				numBeans--;
			}
			else
			{
				if (hole == 0)
				{
					hole = 1;
					s = SOUTH;
					currentSide = southHoles;
				}
				else
					hole--;
				currentSide[hole]++;
				numBeans--;
			}
		}
	}
	//record the ending hole and side
	endSide = s;
	endHole = hole;
	return true;

}

bool Board::moveToPot(Side s, int hole, Side potOwner)
{
	//check that the hole that was selected is valid
	if (beans(s, hole) == -1 || hole == 0)
		return false;
	
	int numBeans = beans(s, hole);
	int* p = determineSide(s);
	int* owner = determineSide(potOwner);
	p[hole] = 0;
	//move beans from player's hole and the
	//opponent's hole to the potOwner's pot
	owner[0] += numBeans + owner[hole];
	owner[hole] = 0;
	return true;
}

bool Board::setBeans(Side s, int hole, int beans)
{
	if (hole > m_holes || beans < 0)
		return false;
	int* p = determineSide(s);
	p[hole] = beans;
	return true;
}

//returns pointer to the appropriate side's array
int* Board::determineSide(Side s) const
{
	if (s == SOUTH)
		return southHoles;
	else
		return northHoles;
}

int* Board::determineOppSide(int* p) const
{
	if ( p == southHoles)
		return northHoles;
	else
		return southHoles;
}