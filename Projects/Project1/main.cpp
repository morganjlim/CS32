#include "Game.h"

int main()
{
	// Create a game
	//Game g(3, 4, 2);
	Game g(7, 8, 25);

	// Play the game
	g.play();
}


//#include "Game.h"
//#include <iostream>
//#include <sstream>
//#include <streambuf>
//#include <string>
//#include <map>
//#include <cstdlib>
//#include <cassert>
//using namespace std;
//
//class streambuf_switcher
//{
//public:
//	streambuf_switcher(ios& dest, ios& src)
//		: dest_stream(dest), saved_streambuf(dest.rdbuf(src.rdbuf()))
//	{}
//	~streambuf_switcher()
//	{
//		dest_stream.rdbuf(saved_streambuf);
//	}
//private:
//	ios& dest_stream;
//	streambuf* saved_streambuf;
//};
//
//map<void*, size_t> allocMap;
//bool recordaddrs = false;
//
//inline bool isRecordedSize(size_t n)
//{
//	return n == sizeof(Zombie) || n == sizeof(Player);
//}
//
//void* operator new(size_t n)
//{
//	void* p = malloc(n);
//	fill_n(static_cast<char*>(p), n, 0xca);
//	if (recordaddrs  &&  isRecordedSize(n))
//	{
//		recordaddrs = false;
//		allocMap.insert(make_pair(p, n));
//		recordaddrs = true;
//	}
//	return p;
//}
//
//void unrecordaddr(void* p)
//{
//	recordaddrs = false;
//	auto it = allocMap.find(p);
//	if (it != allocMap.end())
//	{
//		fill_n(static_cast<char*>(p), it->second, 0xcb);
//		allocMap.erase(it);
//	}
//	recordaddrs = true;
//}
//
//#if __cplusplus >= 201402L  &&  ! defined(__clang__)
//// Unless clang is supplied the -fsized-deallocation flag, it will
//// not call the C++14 sized operator delete.
//
//void operator delete(void* p) noexcept
//{
//	free(p);
//}
//
//void operator delete(void* p, size_t n) noexcept
//{
//	if (recordaddrs  &&  isRecordedSize(n))
//		unrecordaddr(p);
//	operator delete(p);
//}
//#else
//void operator delete(void* p) noexcept
//{
//	if (recordaddrs)
//		unrecordaddr(p);
//	free(p);
//}
//#endif
//
//void testone(int n)
//{
//	streambuf_switcher sso(cout, cerr);
//
//	switch (n)
//	{
//	default: {
//		cout << "Bad argument" << endl;
//	} break; case  1: {
//		Arena a(15, 18);
//		a.addPlayer(2, 2);
//		Zombie z(&a, 5, 17);
//		assert(z.row() == 5 && z.col() == 17);
//	} break; case  2: {
//		Arena a(20, 30);
//		a.addPlayer(1, 1);
//		Zombie z(&a, 12, 22);
//		for (int k = 0; k < 8; k++)
//		{
//			int oldr = z.row();
//			int oldc = z.col();
//			z.move();
//			assert((z.row() == oldr && abs(z.col() - oldc) == 1) ||
//				(z.col() == oldc && abs(z.row() - oldr) == 1));
//		}
//	} break; case  3: {
//		bool moved = false;
//		for (int k = 0; k < 50; k++)
//		{
//			Arena a(1, 29);
//			a.addPlayer(1, 1);
//			Zombie z(&a, 1, 29);
//			for (int m = 0; m < 20 && z.col() > 1; m++)
//			{
//				int oldc = z.col();
//				z.move();
//				assert(z.row() == 1 && z.col() <= 29 &&
//					abs(z.col() - oldc) <= 1);
//				if (z.col() != oldc)
//					moved = true;
//			}
//		}
//		assert(moved);
//	} break; case  4: {
//		bool moved = false;
//		for (int k = 0; k < 50; k++)
//		{
//			Arena a(19, 1);
//			a.addPlayer(1, 1);
//			Zombie z(&a, 19, 1);
//			for (int m = 0; m < 17 && z.row() > 1; m++)
//			{
//				int oldr = z.row();
//				z.move();
//				assert(z.col() == 1 && z.row() <= 19 &&
//					abs(z.row() - oldr) <= 1);
//				if (z.row() != oldr)
//					moved = true;
//			}
//		}
//		assert(moved);
//	} break; case  5: {
//		bool moved = false;
//		for (int k = 0; k < 50; k++)
//		{
//			Arena a(1, 30);
//			a.addPlayer(1, 30);
//			Zombie z(&a, 1, 1);
//			for (int m = 0; m < 20 && z.col() < 30; m++)
//			{
//				int oldc = z.col();
//				z.move();
//				assert(z.row() == 1 && z.col() >= 1 &&
//					abs(z.col() - oldc) <= 1);
//				if (z.col() != oldc)
//					moved = true;
//			}
//		}
//		assert(moved);
//	} break; case  6: {
//		bool moved = false;
//		for (int k = 0; k < 50; k++)
//		{
//			Arena a(20, 1);
//			a.addPlayer(20, 1);
//			Zombie z(&a, 1, 1);
//			for (int m = 0; m < 20 && z.row() < 20; m++)
//			{
//				int oldr = z.row();
//				z.move();
//				assert(z.col() == 1 && z.row() >= 1 &&
//					abs(z.row() - oldr) <= 1);
//				if (z.row() != oldr)
//					moved = true;
//			}
//		}
//		assert(moved);
//	} break; case  7: {
//		Arena a(10, 20);
//		a.addPlayer(1, 1);
//		Zombie z(&a, 8, 12);
//		z.move();
//		assert((z.row() == 8 && abs(z.col() - 12) == 1) ||
//			(z.col() == 12 && abs(z.row() - 8) == 1));
//
//	} break; case  8: {
//		Arena a(10, 20);
//		a.addPlayer(1, 1);
//		Zombie z(&a, 5, 7);
//		assert(!z.getAttacked(UP));
//		assert(z.getAttacked(DOWN));
//	} break; case  9: {
//		Arena a(10, 20);
//		a.addPlayer(1, 1);
//		Zombie z(&a, 5, 1);
//		assert(z.getAttacked(LEFT));
//	} break; case 10: {
//		Arena a(10, 20);
//		Player p(&a, 2, 3);
//		assert(p.row() == 2 && p.col() == 3);
//	} break; case 11: {
//		Arena a(10, 20);
//		Player p(&a, 2, 3);
//		assert(!p.isDead());
//		p.setDead();
//		assert(p.isDead());
//	} break; case 12: {
//		Arena a(10, 20);
//		a.addPlayer(8, 12);
//		Player* p = a.player();
//		p->moveOrAttack(UP);
//		assert(p->row() == 7 && p->col() == 12);
//		p->moveOrAttack(DOWN);
//		assert(p->row() == 8 && p->col() == 12);
//		p->moveOrAttack(LEFT);
//		assert(p->row() == 8 && p->col() == 11);
//		p->moveOrAttack(RIGHT);
//		assert(p->row() == 8 && p->col() == 12);
//	} break; case 13: {
//		Arena a(15, 18);
//		a.addPlayer(1, 1);
//		Player* p = a.player();
//		p->moveOrAttack(LEFT);
//		assert(p->row() == 1 && p->col() == 1 && !p->isDead());
//		p->moveOrAttack(UP);
//		assert(p->row() == 1 && p->col() == 1 && !p->isDead());
//	} break; case 14: {
//		Arena a(15, 18);
//		a.addPlayer(15, 18);
//		Player* p = a.player();
//		p->moveOrAttack(RIGHT);
//		assert(p->row() == 15 && p->col() == 18 && !p->isDead());
//		p->moveOrAttack(DOWN);
//		assert(p->row() == 15 && p->col() == 18 && !p->isDead());
//	} break; case 15: {
//		Arena a(10, 20);
//		a.addPlayer(5, 6);
//		a.addZombie(5, 7);
//		assert(a.numZombiesAt(5, 7) == 1 && a.numZombiesAt(5, 8) == 0);
//		Player* p = a.player();
//		p->moveOrAttack(RIGHT);
//		assert(p->row() == 5 && p->col() == 6 &&
//			a.numZombiesAt(5, 7) == 0 && a.numZombiesAt(5, 8) == 1);
//	} break; case 16: {
//		Arena a(10, 20);
//		a.addPlayer(5, 6);
//		a.addZombie(5, 7);
//		assert(a.numZombiesAt(5, 7) == 1 && a.numZombiesAt(5, 8) == 0);
//		Player* p = a.player();
//		p->moveOrAttack(RIGHT);
//		assert(p->row() == 5 && p->col() == 6 &&
//			a.numZombiesAt(5, 7) == 0 && a.numZombiesAt(5, 8) == 1);
//		p->moveOrAttack(RIGHT);
//		assert(p->row() == 5 && p->col() == 7 &&
//			a.numZombiesAt(5, 7) == 0 && a.numZombiesAt(5, 8) == 1);
//		p->moveOrAttack(RIGHT);
//		assert(p->row() == 5 && p->col() == 7 &&
//			a.numZombiesAt(5, 7) == 0 && a.numZombiesAt(5, 8) == 0);
//	} break; case 17: {
//		Arena a(19, 27);
//		assert(a.rows() == 19 && a.cols() == 27);
//	} break; case 18: {
//		Arena a(10, 20);
//		a.addPlayer(3, 6);
//		a.addZombie(7, 5);
//		a.addZombie(4, 7);
//		a.addZombie(7, 5);
//		assert(a.numZombiesAt(7, 5) == 2 && a.zombieCount() == 3);
//	} break; case 19: {
//		Arena a(10, 20);
//		int r = 5;
//		int c = 7;
//		assert(a.determineNewPosition(r, c, UP) && r == 4 && c == 7);
//		assert(a.determineNewPosition(r, c, LEFT) && r == 4 && c == 6);
//		assert(a.determineNewPosition(r, c, DOWN) && r == 5 && c == 6);
//		assert(a.determineNewPosition(r, c, RIGHT) && r == 5 && c == 7);
//	} break; case 20: {
//		Arena a(10, 20);
//		int r = 1;
//		int c = 7;
//		assert(!a.determineNewPosition(r, c, UP) && r == 1 && c == 7);
//		r = 5;
//		c = 1;
//		assert(!a.determineNewPosition(r, c, LEFT) && r == 5 && c == 1);
//	} break; case 21: {
//		Arena a(10, 20);
//		int r = 10;
//		int c = 7;
//		assert(!a.determineNewPosition(r, c, DOWN) && r == 10 && c == 7);
//		r = 5;
//		c = 20;
//		assert(!a.determineNewPosition(r, c, RIGHT) && r == 5 && c == 20);
//	} break; case 22: {
//		Arena a(10, 20);
//		a.addPlayer(3, 6);
//		a.addZombie(4, 4);
//		assert(!a.attackZombieAt(4, 5, RIGHT) && a.numZombiesAt(4, 4) == 1 &&
//			a.numZombiesAt(4, 6) == 0 && a.zombieCount() == 1);
//	} break; case 23: {
//		Arena a(10, 20);
//		a.addPlayer(3, 6);
//		a.addZombie(4, 4);
//		assert(a.numZombiesAt(4, 4) == 1 && a.numZombiesAt(5, 4) == 0 &&
//			a.zombieCount() == 1);
//		assert(!a.attackZombieAt(4, 4, DOWN));
//		assert(a.numZombiesAt(5, 4) == 1 && a.numZombiesAt(4, 4) == 0 &&
//			a.zombieCount() == 1);
//		assert(a.attackZombieAt(5, 4, RIGHT));
//		assert(a.numZombiesAt(5, 4) == 0 && a.numZombiesAt(5, 5) == 0 &&
//			a.zombieCount() == 0);
//	} break; case 24: {
//		Arena a(10, 20);
//		a.addPlayer(3, 6);
//		a.addZombie(4, 4);
//		a.addZombie(7, 5);
//		a.addZombie(5, 7);
//		a.addZombie(7, 5);
//		int oldCount = a.zombieCount();
//		a.attackZombieAt(5, 7, LEFT);
//		assert(a.numZombiesAt(5, 6) == 1 && a.zombieCount() == oldCount);
//		a.attackZombieAt(4, 4, UP);
//		assert(a.numZombiesAt(5, 6) == 1 && a.zombieCount() == oldCount);
//		assert(a.numZombiesAt(3, 4) == 1);
//		a.attackZombieAt(5, 6, LEFT);
//		assert(a.numZombiesAt(5, 6) == 0 && a.numZombiesAt(5, 5) == 0 &&
//			a.zombieCount() == oldCount - 1);
//		assert(a.numZombiesAt(3, 4) == 1);
//	} break; case 25: {
//		Arena a(10, 20);
//		a.addPlayer(3, 6);
//		a.addZombie(4, 4);
//		a.addZombie(7, 5);
//		a.addZombie(8, 5);
//		a.addZombie(7, 5);
//		int oldCount = a.zombieCount();
//		a.attackZombieAt(7, 5, DOWN);
//		assert(a.numZombiesAt(7, 5) == 1 && a.numZombiesAt(8, 5) == 2 &&
//			a.zombieCount() == oldCount);
//		a.attackZombieAt(8, 5, DOWN);
//		assert((a.numZombiesAt(8, 5) == 1 && a.numZombiesAt(9, 5) == 0 &&
//			a.zombieCount() == oldCount - 1) ||
//			(a.numZombiesAt(8, 5) == 1 && a.numZombiesAt(9, 5) == 1 &&
//				a.zombieCount() == oldCount));
//		a.attackZombieAt(8, 5, DOWN);
//		assert(a.numZombiesAt(8, 5) == 0 && a.numZombiesAt(9, 5) == 1 &&
//			a.zombieCount() == oldCount - 1);
//		a.attackZombieAt(9, 5, DOWN);
//		assert(a.numZombiesAt(9, 5) == 0 && a.zombieCount() == oldCount - 2);
//	} break; case 26: {
//		Arena a(10, 20);
//		a.addPlayer(6, 17);
//		for (int r = 1; r <= 10; r++)
//			for (int c = 1; c <= 15; c++)
//				assert(a.addZombie(r, c));
//		assert(!a.addZombie(5, 17));
//	} break; case 27: {
//		Arena a(10, 20);
//		a.addPlayer(6, 6);
//		a.addZombie(4, 6);
//		a.addZombie(5, 8);
//		a.moveZombies();
//		assert(a.numZombiesAt(4, 6) == 0 &&
//			(a.numZombiesAt(3, 6) + a.numZombiesAt(5, 6) +
//				a.numZombiesAt(4, 5) + a.numZombiesAt(4, 7)) == 1);
//		assert(a.numZombiesAt(5, 8) == 0 &&
//			(a.numZombiesAt(4, 8) + a.numZombiesAt(6, 8) +
//				a.numZombiesAt(5, 7) + a.numZombiesAt(5, 9)) == 1);
//	} break; case 28: {
//		Arena a(10, 20);
//		a.addPlayer(7, 7);
//		for (int k = 0; k < MAXZOMBIES / 4; k++)
//		{
//			a.addZombie(6, 7);
//			a.addZombie(8, 7);
//			a.addZombie(7, 6);
//			a.addZombie(7, 8);
//		}
//		assert(!a.player()->isDead());
//		a.moveZombies();
//		assert(a.player()->isDead());
//	} break; case 29: {
//		Arena a(1, 3);
//		a.addPlayer(1, 1);
//		Player* p = a.player();
//		for (int j = 0; j < 10; j++)
//			a.addZombie(1, 3);
//		assert(!p->isDead());
//		a.moveZombies();
//		int k;
//		for (k = 0; k < 100; k++)
//		{
//			assert(!p->isDead());
//			bool b = a.moveZombies();
//			if (!b || a.numZombiesAt(1, 1) > 0 || p->isDead())
//			{
//				assert(!b && a.numZombiesAt(1, 1) > 0 &&
//					p->isDead());
//				break;
//			}
//		}
//		assert(k < 100);
//	} break; case 30: {
//		ostringstream oss;
//		streambuf_switcher sso2(cout, oss);
//		Arena a(2, 3);
//		a.addPlayer(1, 2);
//		a.addZombie(1, 3);
//		a.addZombie(2, 2);
//		a.display();
//		string s = oss.str();
//		assert(s.find(".@Z") != string::npos);
//		assert(s.find(".Z.") != string::npos);
//	} break; case 31: {
//		ostringstream oss;
//		streambuf_switcher sso2(cout, oss);
//		Arena a(2, 3);
//		a.addPlayer(1, 2);
//		for (int k = 1; k <= 8; k++)
//			a.addZombie(1, 3);
//		a.addZombie(2, 2);
//		a.display();
//		string s = oss.str();
//		assert(s.find(".@8") != string::npos);
//	} break; case 32: {
//		ostringstream oss;
//		streambuf_switcher sbs(cout, oss);
//		Arena a(2, 3);
//		a.addPlayer(1, 2);
//		for (int k = 1; k <= 10; k++)
//			a.addZombie(1, 3);
//		a.addZombie(2, 2);
//		a.display();
//		string s = oss.str();
//		assert(s.find(".@9") != string::npos);
//	} break; case 33: {
//		recordaddrs = true;
//		int oldn = allocMap.size();
//		{
//			Arena a(10, 20);
//			int oldn2 = allocMap.size();
//			assert(oldn2 >= oldn);
//			a.addPlayer(4, 3);
//			a.addZombie(5, 6);
//			a.addZombie(5, 7);
//			a.addZombie(5, 8);
//			assert(allocMap.size() == oldn2 + 4);
//		}
//		assert(allocMap.size() == oldn);
//		recordaddrs = false;
//	} break; case 34: {
//		Arena a(1, 30);
//		a.addPlayer(1, 2);
//		recordaddrs = true;
//		int oldn = allocMap.size();
//		a.addZombie(1, 5);
//		assert(allocMap.size() == oldn + 1);
//		a.attackZombieAt(1, 5, RIGHT);
//		a.attackZombieAt(1, 6, RIGHT);
//		assert(allocMap.size() == oldn);
//		recordaddrs = false;
//	} break; case 35: {
//		Arena a(1, 30);
//		a.addPlayer(1, 3);
//		for (int k = 0; k < 20; k++)
//		{
//			a.addZombie(1, 2);
//			a.addZombie(1, 4);
//		}
//		a.addZombie(1, 30);
//		for (int k = 0; k < 20; k++)
//		{
//			a.addZombie(1, 2);
//			a.addZombie(1, 4);
//		}
//		assert(a.zombieCount() == 81);
//		for (int k = 0; k < 80; k++)
//		{
//			a.attackZombieAt(1, 2, LEFT);
//			a.attackZombieAt(1, 4, RIGHT);
//		}
//		for (int k = 0; k < 80; k++)
//		{
//			a.attackZombieAt(1, 1, LEFT);
//			a.attackZombieAt(1, 5, RIGHT);
//		}
//		assert(a.zombieCount() == 1 && a.numZombiesAt(1, 30) == 1);
//		for (int c = 1; c <= 6; c++)
//			assert(a.numZombiesAt(1, c) == 0);
//		Player* p = a.player();
//		assert(!p->isDead());
//		for (int k = 0; k < 10; k++)
//		{
//			a.moveZombies();
//			assert(!p->isDead());
//			for (int c = 1; c <= 6; c++)
//			{
//				a.attackZombieAt(1, c, RIGHT);
//				assert(a.numZombiesAt(1, c) == 0);
//			}
//		}
//	} break;
//	}
//}
//
//int main()
//{
//	cout << "Enter test number (1-35): ";
//	int n;
//	cin >> n;
//	testone(n);
//	cout << "Passed" << endl;
//}