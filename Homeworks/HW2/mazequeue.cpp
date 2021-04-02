#include <queue>
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
	queue <Coord> coordQueue;
	Coord start(sr, sc), end(er, ec);

	coordQueue.push(start);
	maze[start.r()][start.c()] = '#';
	while (!coordQueue.empty())
	{
		Coord c = coordQueue.front();
		coordQueue.pop();
		if (c.r() == end.r() && c.c() == end.c())
			return true;
		else
		{
			if (maze[c.r() + 1][c.c()] != 'X' && maze[c.r() + 1][c.c()] != '#')
			{
				maze[c.r() + 1][c.c()] = '#';
				Coord add(c.r() + 1, c.c());
				coordQueue.push(add);
			}
			if (maze[c.r()][c.c() - 1] != 'X' && maze[c.r()][c.c() - 1] != '#')
			{
				maze[c.r()][c.c() - 1] = '#';
				Coord add(c.r(), c.c() - 1);
				coordQueue.push(add);
			}
			if (maze[c.r() - 1][c.c()] != 'X' && maze[c.r() - 1][c.c()] != '#')
			{
				maze[c.r() - 1][c.c()] = '#';
				Coord add(c.r() - 1, c.c());
				coordQueue.push(add);
			}
			if (maze[c.r()][c.c() + 1] != 'X' && maze[c.r()][c.c() + 1] != '#')
			{
				maze[c.r()][c.c() + 1] = '#';
				Coord add(c.r(), c.c() + 1);
				coordQueue.push(add);
			}
		}
	}
	return false;
}
