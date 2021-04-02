#include "History.h"

History::History(int nRows, int nCols)
	:m_rows(nRows), m_cols(nCols)
{
	for (int i = 0; i < m_rows; i++)
	{
		for (int j = 0; j < m_cols; j++)
		{
			location[i][j] = '.';
		}
	}
}

bool History::record(int r, int c)
{
	if (r > m_rows || c > m_cols || r<= 0 || c <=0)
	{
		return false;
	}

	if (location[r-1][c-1] == '.')
	{
		location[r-1][c-1] = 'A';
	}
	else if (location[r-1][c-1] >= 'A' && location[r-1][c-1] < 'Z')
	{
		location[r-1][c-1]++;
	}

	return true;
}

void History::display() const
{
	// Draw the grid
	clearScreen();
	for (int r = 0; r < m_rows; r++)
	{
		for (int c = 0; c < m_cols; c++)
			cout << location[r][c];
		cout << endl;
	}
	cout << endl;
}