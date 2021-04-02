#include "Game.h"


Game::Game(const Board& b, Player* south, Player* north)
	: m_board(b), m_sPlayer(south), m_nPlayer(north),
	currentPlayer(south), currentSide(SOUTH) //CHANGE THE CURRENT PLAYER BACK TO SOUTH
{}

//print the state of the game
void Game::display() const
{
	cout << "                ";
	for (int i = 1; i <= m_board.holes(); i++)
		cout << beans(NORTH, i) << "  ";
	cout << endl;
	cout << m_nPlayer->name() << "'s Pot  " << m_board.beans(NORTH, 0);
	for (int i = 0; i <= m_board.holes() * 3; i++)
		cout << " ";
	cout << m_board.beans(SOUTH, 0) << "  "<< m_sPlayer->name() << "'s Pot";
	cout << endl << "                ";
	for (int i = 1; i <= m_board.holes(); i++)
		cout << beans(SOUTH, i) << "  ";
	cout << endl;
}

void Game::status(bool& over, bool& hasWinner, Side& winner) const
{
	bool nEmpty(true), sEmpty(true);

	//check if either side is empty
	for (int i = 1; i <= m_board.holes(); i++)
	{
		if (m_board.beans(NORTH, i) != 0)
			nEmpty = false;
	}
	for (int i = 1; i <= m_board.holes(); i++)
	{
		if (m_board.beans(SOUTH, i) != 0)
			sEmpty = false;
	}

	//game is over if either side is empty
	if (sEmpty || nEmpty)
		over = true;
	else
	{
		over = false;
		return;
	}

	//if the game is over:
	//check to see if there is a winner and who it is
	if (m_board.beans(NORTH, 0) == m_board.beans(SOUTH, 0))
	{
		hasWinner = false;
		return;
	}
	else if (m_board.beans(NORTH, 0) > m_board.beans(SOUTH, 0))
	{
		hasWinner = true;
		winner = NORTH;
		return;
	}
	else
	{
		hasWinner = true;
		winner = SOUTH;
		return;
	}
}

bool Game::move()
{
	bool over(false), hasWinner(false);
	Side endSide(NORTH), winner(NORTH);
	int hole(0), endHole(0);

	//check the status of the game to make sure
	//a move is not being made
	status(over, hasWinner, winner);

	//if it is over clean up the board
	if (over)
	{
		//if there are any beans left in the holes move them to their respective pots
		for (int i = 1; i <= m_board.holes(); i++)
		{
			m_board.moveToPot(NORTH, i, NORTH);
			m_board.moveToPot(SOUTH, i, SOUTH);
			status(over, hasWinner, winner);
		}
		display();
		cout << "The winner is " << determinePlayerBySide(winner)->name() << endl;
		return false;
	}

	//otherwise have the player make a move
	do
	{
		//have the player pick a hole
		hole = currentPlayer->chooseMove(m_board, currentSide);

		//if there are no holes to be chosen
		if (hole == -1)
		{
			over = true;
			break;
		}

		//display what a computer player chooses
		if (!currentPlayer->isInteractive())
			cout << currentPlayer->name() << " chooses hole " << hole << endl;
	
		//sow the board
		m_board.sow(currentSide, hole, endSide, endHole);
		display();
		
		//check the status of the game again
		status(over, hasWinner, winner);
	} while (endHole == 0 && !over);
	
	//if the hole picked was valid
	if (hole != -1)
	{
		//and the hole opposite is not empty and it was previously empty
		if (endHole != 0 && beans(endSide, endHole) - 1 == 0
			&& beans(opponent(endSide), endHole) != 0
			&& endSide == currentSide)
		{
			//move all those beans to the pot of the player
			m_board.moveToPot(opponent(currentSide), endHole, currentSide);
			display();
		}		
	}

	//check the status again
	status(over, hasWinner, winner);
	if (over)
	{
		//if there are any beans left in the holes move them to their respective pots
		for (int i = 1; i <= m_board.holes(); i++)
		{
			m_board.moveToPot(NORTH, i, NORTH);
			m_board.moveToPot(SOUTH, i, SOUTH);
			status(over, hasWinner, winner);
		}
		display();
		cout << "The winner is " << determinePlayerBySide(winner)->name() << endl;
		return false;
	}

	//switch the player and side
	currentSide = opponent(currentSide);
	currentPlayer = otherPlayer(currentPlayer);
	return true; //TODO
}

void Game::play()
{
	bool over(false), hasWinner(false);
	Side winner(NORTH);

	//check that the game is not over
	status(over, hasWinner, winner);

	if (over)
		return;

	display();

	//while the game is not over
	while (!over)
	{
		//have the player make a move
		move();
		status(over, hasWinner, winner);
		if (!m_nPlayer->isInteractive() && !m_sPlayer->isInteractive())
		{
			cout << "press ENTER to continue";
			cin.ignore();
		}
	}

	return; //TODO
}

int Game::beans(Side s, int hole) const
{
	return m_board.beans(s, hole);
}
Player* Game::otherPlayer(Player* p)
{
	if (p == m_nPlayer)
		return m_sPlayer;
	else
		return m_nPlayer;
}

Side Game::determineSide(Player* p)
{
	if (p == m_nPlayer)
		return NORTH;
	else
		return SOUTH;
}

Player* Game::determinePlayerBySide(Side s)
{
	if (s == SOUTH)
		return m_sPlayer;
	else
		return m_nPlayer;
}
