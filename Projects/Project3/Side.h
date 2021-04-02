#ifndef SIDE_H
#define SIDE_H

#include <string>
#include <iostream>
using namespace std;

enum Side { NORTH, SOUTH };

const int NSIDES = 2;
const int POT = 0;

inline
Side opponent(Side s)
{
	return Side(NSIDES - 1 - s);
}

#endif