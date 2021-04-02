#include "ScoreList.h"
using namespace std;
#include <iostream>
#include <cassert>

int main()
{
	ScoreList s;
	for (int i = 0; i < 6; i++)
		s.add(i);
	assert(s.minimum() == 0);
	assert(s.maximum() == 5);
	ScoreList s1;
	s1.add(5);
	s1.add(6);
	s1.add(42);
	s1.add(74);
	s1.add(32);
	assert(s1.size() == 5);
	assert(s1.maximum() == 74);
	assert(s1.minimum() == 5);
	assert(s1.remove(5) == true);
	assert(s1.remove(60) == false);
	assert(s1.size() == 4);
	assert(s1.minimum() == 6);
	cout << "passed!";

	return 0;
}