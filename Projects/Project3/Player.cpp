#include "Player.h"

int HumanPlayer::chooseMove(const Board& b, Side s) const
{
	bool cont(false);
	int hole(0);

	while (!cont)
	{
		cout << "Select a hole, " << name() << ": ";
		cin >> hole;

		if (b.beans(s, hole) < 0 || hole > b.holes())
			cout << "The hole number must be from 1 to " << b.holes() << endl;
		else if (b.beans(s, hole) == 0)
			cout << "There are no beans in that hole." << endl;
		else
			cont = true;
	}
	return hole;
}

int BadPlayer::chooseMove(const Board& b, Side s) const
{
	//pick the first hole that has beans in it
	for (int i = 1; i <= b.holes(); i++)
	{
		if (b.beans(s, i) != 0)
			return i;
	}
	return -1;
}

//evaluation of moves: -1000 for loss, 1000 for win, 0 for neither win or loss
int SmartPlayer::chooseMove(const Board& b, Side s) const
{
	AlarmClock ac(2200);
	int bestVal = -8800, bestHole(1), endHole(0);
	Side endSide;

	//for every hole that is not empty
	for (int j = 1; j <= b.holes(); j++)
	{
		if (b.beans(s, j) != 0)
		{
			//create a copy of the board
			Board temp = b;
			//play by sowing and making captures as needed
			
				temp.sow(s, j, endSide, endHole);
				if (endHole != 0 && temp.beans(endSide, endHole) - 1 == 0
					&& temp.beans(opponent(endSide), endHole) != 0
					&& endSide == s)
					temp.moveToPot(opponent(s), endHole, s);
				
			//quantify how good that move is using minimax
			int moveVal = miniMax(ac, temp, 0, false, 7, s, s);
	
			//if this move is better than the best move from before,
			//change the value and set the hole to be chosen to j
			if (moveVal > bestVal)
			{
				bestHole = j;
				bestVal = moveVal;
			}
		}
	}
	
	//just as a guard, if no best move was found
	//find a valid hole to pick and return that one
	
	if (bestVal == -8800)
	{
		for (int i = 1; i <= b.holes(); i++)
		{
			if (b.beans(s, i) != 0)
				return i;
		}
	}

	return bestHole;
}

int SmartPlayer::miniMax(AlarmClock& ac, const Board& b, int depth, bool isMax, int maxD, Side s, Side originalSide) const
{
	bool over(false);
	Side endSide(SOUTH);
	int eval(0),endHole(0), best(0);
	
	
	//evaluate the state of the board from the player's side
	eval = evaluate(b, originalSide, over);
	
	//if the game is over or the maximum depth has been reached
	//return how "good" of a state the board is in for the player
	if (over || ac.timedOut())
		return eval;
	
	//if looking for the best state the board can be in
	if (isMax)
	{
		//for every hole that is not empty
		for (int i = 1; i <= b.holes(); i++)
		{
			if (b.beans(s, i) != 0)
			{
				//create a temporary board
				Board temp = b;
	
				//make necessary moves for the board
				temp.sow(s, i, endSide, endHole);
				if (endHole != 0 && temp.beans(endSide, endHole) - 1 == 0
					&& temp.beans(opponent(endSide), endHole) != 0
					&& endSide == s)
					temp.moveToPot(opponent(s), endHole, s);

				//compare the best possible move by calling minimax
				best = max(best, miniMax(ac, temp, depth + 1, !isMax, maxD, opponent(s), originalSide));
			}
		}
	}
	//other wise if looking for the worst state the board can be in
	else
	{	
		for (int i = 1; i <= b.holes(); i++)
		{
			if (b.beans(s, i) != 0)
			{
				Board temp = b;
	
				temp.sow(s, i, endSide, endHole);
				if (endHole != 0 && temp.beans(endSide, endHole) - 1 == 0
					&& temp.beans(opponent(endSide), endHole) != 0
					&& endSide == s)
					temp.moveToPot(opponent(s), endHole, s);

				best = min(best, miniMax(ac, temp, depth + 1, !isMax, maxD, opponent(s), originalSide));
			}
		}
	}
	return best;
}

int SmartPlayer::evaluate(const Board b, Side s, bool& over) const
{
	over = isOver(b, s);

	if (over)
	{
		//if the game is over make sure to account for
		//beans that are not in the pots
		Board temp = b;
		for (int i = 1; i <= temp.holes(); i++)
		{
			temp.moveToPot(SOUTH, i, SOUTH);
			temp.moveToPot(NORTH, i, NORTH);
		}

		//compare values and return
		if (temp.beans(s, 0) == temp.beans(opponent(s), 0))
		{
			return 0;
		}
		else if (temp.beans(s, 0) > temp.beans(opponent(s), 0))
		{
			return 10000;
		}
		else if (temp.beans(s, 0) < temp.beans(opponent(s), 0))
		{
			return -10000;
		}
	}
	else
	{
		//if the game is not over return a "middle value"
		//that is not the best but also not the worst possible outcome
		if (b.beans(s, 0) == b.beans(opponent(s), 0))
		{
			return 0;
		}
		else if (b.beans(s, 0) > b.beans(opponent(s), 0))
		{
			return 5000;
		}
		else if (b.beans(s, 0) < b.beans(opponent(s), 0))
		{
			return -5000;
		}
	}
	return 0;
		
}

int SmartPlayer::max(int i, int j) const
{
	if (i > j)
		return i;
	else
		return j;
}

int SmartPlayer::min(int i, int j) const
{
	if (i < j)
		return i;
	else
		return j;
}

bool SmartPlayer::isOver(Board b, Side s) const
{
	bool playerEmpty(true), opponentEmpty(true);

	//check both sides of the board to see if either side is empty
	for (int j = 1; j <= b.holes(); j++)
	{
		if (b.beans(s, j) != 0)
			playerEmpty = false;
	}
	for (int j = 1; j <= b.holes(); j++)
	{
		if (b.beans(opponent(s), j) != 0)
			opponentEmpty = false;
	}

	//return whether the game is over or not
	if (playerEmpty || opponentEmpty)
		return true;
	return false;
}

