#include "Game.h"
#include <cassert>
int main()
{
	//Board b(6, 3);
	//HumanPlayer p1("p1");
	//SmartPlayer p2("p2");
	//Player* pt1 = &p1;
	//Player* pt2 = &p2;

	//Game g(b, pt1, pt2);

	//g.play();

	//Board b(6, 3);
	//Side endSide(SOUTH);
	//int endHole(0);
	//bool over, hasWinner(true);

	//HumanPlayer p1("p1");
	//BadPlayer p2("p2");
	//SmartPlayer p3("p3");
	//Player* pt1 = &p1;
	//Player* pt2 = &p2;

	//Game g(b, pt2, pt1);

	////board test cases
	////to check holes()
	//assert(b.holes() == 6);
	////to check that the assigned number of beans for
	////the holes and pots are correct
	//assert(b.beans(NORTH, 1) == 3);
	//assert(b.beans(SOUTH, 1) == 3);
	//assert(b.beans(NORTH, 0) == 0);
	//assert(b.beans(SOUTH, 0) == 0);
	////to test that beans() is working correctly
	//assert(b.beans(SOUTH, 7) == -1);
	//assert(b.beans(SOUTH, -3) == -1);
	////to test beansInPlay()
	//assert(b.beansInPlay(SOUTH) == 18);
	//assert(b.totalBeans() == 36);
	////to check that sow is working correctly
	//assert(b.sow(SOUTH, 6, endSide, endHole) == true);
	//assert(endHole == 5);
	//assert(endSide == NORTH);
	//assert(b.sow(SOUTH, 6, endSide, endHole) == false);
	//assert(b.beansInPlay(SOUTH) == 15);
	//assert(b.sow(SOUTH, -1, endSide, endHole) == false);
	////to check moveToPot
	//assert(b.moveToPot(SOUTH, 1, SOUTH) == true);
	//assert(b.moveToPot(SOUTH, 7, SOUTH) == false);
	//assert(b.beans(SOUTH, 1) == 0);
	//assert(b.beans(SOUTH, 0) == 4);

	////to test player

	////to test name()
	//assert(p1.name() == "p1");
	//assert(p2.name() == "p2");
	//assert(p3.name() == "p3");

	////to test isInteractive
	//assert(p1.isInteractive() == true);
	//assert(p2.isInteractive() == false);
	//assert(p3.isInteractive() == false);

	////to test chooseMove
	//assert(p1.chooseMove(b, SOUTH) != 1 && p1.chooseMove(b, SOUTH) != 6);
	//assert(p2.chooseMove(b, SOUTH) != 1 && p2.chooseMove(b, SOUTH) != 6);
	//assert(p3.chooseMove(b, SOUTH) != 1 && p3.chooseMove(b, SOUTH) != 6);
	//
	////to test Game
	//g.display();
	//g.status(over, hasWinner, endSide);
	//assert(over == false && hasWinner == true);
	////^ hasWinner is true because if the game is not
	////over, status() is only supposed to set over to
	////false and nothing else

	////cerr << "passed all tests!";

	//return 0;
}


//spec test cases

//spec test 1

//#include "game.h"
//#include "player.h"
//#include "board.h"
//#include "side.h"
//#include <iostream>
//#include <cassert>
//using namespace std;
//
//void dogametests()
//{
//	badplayer bp1("bart");
//	badplayer bp2("homer");
//	board b(3, 0);
//	b.setbeans(south, 1, 2);
//	b.setbeans(north, 2, 1);
//	b.setbeans(north, 3, 2);
//	game g(b, &bp1, &bp2);
//	bool over;
//	bool haswinner;
//	side winner;
//	//    homer
//	//   0  1  2
//	// 0         0
//	//   2  0  0
//	//    bart
//	g.status(over, haswinner, winner);
//	assert(!over && g.beans(north, pot) == 0 && g.beans(south, pot) == 0 &&
//		g.beans(north, 1) == 0 && g.beans(north, 2) == 1 && g.beans(north, 3) == 2 &&
//		g.beans(south, 1) == 2 && g.beans(south, 2) == 0 && g.beans(south, 3) == 0);
//
//	g.move();
//	//   0  1  0
//	// 0         3
//	//   0  1  0
//	g.status(over, haswinner, winner);
//	assert(!over && g.beans(north, pot) == 0 && g.beans(south, pot) == 3 &&
//		g.beans(north, 1) == 0 && g.beans(north, 2) == 1 && g.beans(north, 3) == 0 &&
//		g.beans(south, 1) == 0 && g.beans(south, 2) == 1 && g.beans(south, 3) == 0);
//
//	g.move();
//	//   1  0  0
//	// 0         3
//	//   0  1  0
//	g.status(over, haswinner, winner);
//	assert(!over && g.beans(north, pot) == 0 && g.beans(south, pot) == 3 &&
//		g.beans(north, 1) == 1 && g.beans(north, 2) == 0 && g.beans(north, 3) == 0 &&
//		g.beans(south, 1) == 0 && g.beans(south, 2) == 1 && g.beans(south, 3) == 0);
//
//	g.move();
//	//   1  0  0
//	// 0         3
//	//   0  0  1
//	g.status(over, haswinner, winner);
//	assert(!over && g.beans(north, pot) == 0 && g.beans(south, pot) == 3 &&
//		g.beans(north, 1) == 1 && g.beans(north, 2) == 0 && g.beans(north, 3) == 0 &&
//		g.beans(south, 1) == 0 && g.beans(south, 2) == 0 && g.beans(south, 3) == 1);
//
//	g.move();
//	//   0  0  0
//	// 1         4
//	//   0  0  0
//	g.status(over, haswinner, winner);
//	assert(over && g.beans(north, pot) == 1 && g.beans(south, pot) == 4 &&
//		g.beans(north, 1) == 0 && g.beans(north, 2) == 0 && g.beans(north, 3) == 0 &&
//		g.beans(south, 1) == 0 && g.beans(south, 2) == 0 && g.beans(south, 3) == 0);
//	assert(haswinner && winner == south);
//}
//
//int main()
//{
//	dogametests();
//	cout << "passed all tests" << endl;
//}

//spec test 2

//#include "Player.h"
//#include "Board.h"
//#include "Side.h"
//#include <iostream>
//#include <cassert>
//using namespace std;
//
//void doPlayerTests()
//{
//	HumanPlayer hp("Marge");
//	assert(hp.name() == "Marge"  &&  hp.isInteractive());
//	BadPlayer bp("Homer");
//	assert(bp.name() == "Homer" && !bp.isInteractive());
//	SmartPlayer sp("Lisa");
//	assert(sp.name() == "Lisa" && !sp.isInteractive());
//	Board b(3, 2);
//	b.setBeans(SOUTH, 2, 0);
//	cout << "=========" << endl;
//	int n = hp.chooseMove(b, SOUTH);
//	cout << "=========" << endl;
//	assert(n == 1 || n == 3);
//	n = bp.chooseMove(b, SOUTH);
//	assert(n == 1 || n == 3);
//	n = sp.chooseMove(b, SOUTH);
//	assert(n == 1 || n == 3);
//}
//
//int main()
//{
//	doPlayerTests();
//	cout << "Passed all tests" << endl;
//}

//spec test 3

//#include "Board.h"
//#include "Side.h"
//#include <iostream>
//#include <cassert>
//using namespace std;
//
//void doBoardTests()
//{
//	Board b(3, 2);
//	assert(b.holes() == 3 && b.totalBeans() == 12 &&
//		b.beans(SOUTH, POT) == 0 && b.beansInPlay(SOUTH) == 6);
//	b.setBeans(SOUTH, 1, 1);
//	b.moveToPot(SOUTH, 2, SOUTH);
//	assert(b.totalBeans() == 11 && b.beans(SOUTH, 1) == 1 &&
//		b.beans(SOUTH, 2) == 0 && b.beans(SOUTH, POT) == 2 &&
//		b.beansInPlay(SOUTH) == 3);
//	Side es;
//	int eh;
//	b.sow(SOUTH, 3, es, eh);
//	assert(es == NORTH && eh == 3 && b.beans(SOUTH, 3) == 0 &&
//		b.beans(NORTH, 3) == 3 && b.beans(SOUTH, POT) == 3 &&
//		b.beansInPlay(SOUTH) == 1 && b.beansInPlay(NORTH) == 7);
//}
//
//int main()
//{
//	doBoardTests();
//	cout << "Passed all tests" << endl;
//}