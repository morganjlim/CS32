#ifndef PLAYER_H
#define PLAYER_H
#include "Board.h"
#include "Side.h"
#include <chrono>
#include <future>
#include <atomic>

class Player
{
public:
	//Create a Player with the indicated name.
	Player(std::string name) : m_name(name) {};
	//Return the name of the player.
	std::string name() const { return m_name; };
	//Return false if the player is a computer player.
	//Return true if the player is human. Most kinds of
	//players will be computer players.
	virtual bool isInteractive() const { return false; };
	//Every concrete class derived from this class must
	//implement this function so that if the player were
	//to be playing side s and had to make a move given
	//board b, the function returns the move the player
	//would choose.If no move is possible, return −1.
	virtual int chooseMove(const Board& b, Side s) const = 0;
	//Since this class is designed as a base class,
	//it should have a virtual destructor.
	virtual ~Player() {};
private:
	string m_name;
};

class HumanPlayer : public Player
{
public:
	//Create a Player with the indicated name.
	HumanPlayer(std::string name) : Player(name) {};
	//Return false if the player is a computer player.
	//Return true if the player is human.Most kinds of
	//players will be computer players.
	virtual bool isInteractive() const { return true; };
	//Every concrete class derived from this class must
	//implement this function so that if the player were
	//to be playing side s and had to make a move given
	//board b, the function returns the move the player
	//would choose.If no move is possible, return −1.
	virtual int chooseMove(const Board& b, Side s) const;
	//Since this class is designed as a base class,
	//it should have a virtual destructor.
	virtual ~HumanPlayer() {} ;
private:
};

class BadPlayer : public Player
{
public:
	//Create a Player with the indicated name.
	BadPlayer(std::string name) : Player(name) {};
	//Every concrete class derived from this class must
	//implement this function so that if the player were
	//to be playing side s and had to make a move given
	//board b, the function returns the move the player
	//would choose.If no move is possible, return −1.
	virtual int chooseMove(const Board& b, Side s) const;
	//Since this class is designed as a base class,
	//it should have a virtual destructor.
	virtual ~BadPlayer() {};
private:
};

class SmartPlayer : public Player
{
public:
	//Create a Player with the indicated name.
	SmartPlayer(std::string name) : Player(name) {};
	//Every concrete class derived from this class must
	//implement this function so that if the player were
	//to be playing side s and had to make a move given
	//board b, the function returns the move the player
	//would choose.If no move is possible, return −1.
	virtual int chooseMove(const Board& b, Side s) const;
	//Since this class is designed as a base class,
	//it should have a virtual destructor.
	virtual ~SmartPlayer() {};

private:
	class AlarmClock
	{
	public:
		AlarmClock(int ms)
		{
			m_timedOut = false;
			m_isRunning = true;
			m_alarmClockFuture = std::async([=]() {
				for (int k = 0; k < ms && m_isRunning; k++)
					std::this_thread::sleep_for(std::chrono::milliseconds(1));
				if (m_isRunning)
					m_timedOut = true;
			});
		}

		~AlarmClock()
		{
			m_isRunning = false;
			m_alarmClockFuture.get();
		}

		bool timedOut() const
		{
			return m_timedOut;
		}

		AlarmClock(const AlarmClock&) = delete;
		AlarmClock& operator=(const AlarmClock&) = delete;
	private:
		std::atomic<bool> m_isRunning;
		std::atomic<bool> m_timedOut;
		std::future<void> m_alarmClockFuture;
	};

	//returns an evaluatio of how "good" a move is
	int miniMax(AlarmClock& ac, const Board& b, int depth, bool isMax, int maxH, Side s, Side originalSide) const;
	//returns the bigger value
	int max(int i, int j) const;
	//returns the smaller value
	int min(int i, int j) const;
	//evaluates the state of the board and returns an evaluation for it
	//based on the side that it is playing on
	int evaluate(const Board b, Side playerSide, bool& over) const;
	//clean up for the game: moves beans into pots as needed
	bool isOver(Board b, Side s) const;
};
#endif // !PLAYER_H
