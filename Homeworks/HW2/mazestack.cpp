#include <stack>
#include <iostream>
using namespace std;

class Coord
{
public:
	Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
	int r() const { return m_r; }
	int c() const { return m_c; }
private:
	int m_r;
	int m_c;
};

bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
	stack <Coord> coordStack;

	Coord start(sr, sc), end(er, ec);

	coordStack.push(start);
	maze[start.r()][start.c()] = '#';
	while (!coordStack.empty())
	{
		Coord c = coordStack.top();
		coordStack.pop();
		if (c.r() == end.r() && c.c() == end.c())
			return true;
		else
		{
			if(maze[c.r() + 1][c.c()] != 'X' && maze[c.r() + 1][c.c()] != '#')
			{
				maze[c.r() + 1][c.c()] = '#';
				Coord add(c.r() + 1, c.c());
				coordStack.push(add);
			}
			if (maze[c.r()][c.c() - 1] != 'X' && maze[c.r()][c.c() - 1] != '#')
			{
				maze[c.r()][c.c() - 1] = '#';
				Coord add(c.r(), c.c() - 1);
				coordStack.push(add);
			}
			if (maze[c.r() - 1 ][c.c()] != 'X' && maze[c.r() - 1][c.c()] != '#')
			{
				maze[c.r() - 1][c.c()] = '#';
				Coord add(c.r() - 1 , c.c());
				coordStack.push(add);
			}
			if (maze[c.r()][c.c() + 1] != 'X' && maze[c.r()][c.c() + 1] != '#')
			{
				maze[c.r()][c.c() + 1] = '#';
				Coord add(c.r(), c.c() + 1);
				coordStack.push(add);
			}
		}
	}
	return false;
}
