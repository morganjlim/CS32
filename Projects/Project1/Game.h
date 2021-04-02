#ifndef GAME_H
#define GAME_H
#include "globals.h"

using namespace std;
class Arena;
class Game
{
public:
	// Constructor/destructor
	Game(int rows, int cols, int nZombies);
	~Game();

	// Mutators
	void play();

private:
	Arena* m_arena;
};

#endif