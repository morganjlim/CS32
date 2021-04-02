//#include <string>
//using namespace std;
//#include <iostream>
//#include <cassert>
//
//bool somePredicate(string s)
//{
//	if (s == "T")
//		return true;
//	else
//		return false;
//}

// Return false if the somePredicate function returns false for at
	  // least one of the array elements; return true otherwise.
bool allTrue(const string a[], int n)
{
	if (n <= 0)
		return true;
	else if (!somePredicate(a[n - 1]))
		return false;
	return allTrue(a, n - 1);
}

// Return the number of elements in the array for which the
// somePredicate function returns false.
int countFalse(const string a[], int n)
{
	if (n <= 0)
		return 0;
	int count = !somePredicate(a[0]);
	
	if (n > 1)
		return count + countFalse(a + 1, n - 1);
	else return count;
}

// Return the subscript of the first element in the array for which
// the somePredicate function returns false.  If there is no such
// element, return -1.
int firstFalse(const string a[], int n)
{
	if (n <= 0)
		return -1;
	int count(0);
	if (!somePredicate(a[0]))
		return count;
	else if (somePredicate(a[0]))
	{
		count++;
		if (firstFalse(a + 1, n - 1) == -1)
			return -1;
		else
			return count + firstFalse(a + 1, n - 1);
	}
	return count;
}

// Return the subscript of the least string in the array (i.e.,
// return the smallest subscript m such that a[m] <= a[k] for all
// k from 0 to n-1).  If the function is told to examine no
// elements, return -1.
int indexOfLeast(const string a[], int n)
{
	if (n <= 0)
		return -1;
	if (n == 1)
		return 0;
	int s = indexOfLeast(a, n - 1);
	if (a[s] < a[n - 1])
		return s;
	else
		return n - 1;
}

// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    "stan" "kyle" "cartman" "kenny" "kyle" "cartman" "butters"
// then the function should return true if a2 is
//    "kyle" "kenny" "butters"
// or
//    "kyle" "cartman" "cartman"
// and it should return false if a2 is
//    "kyle" "butters" "kenny"
// or
//    "stan" "kenny" "kenny"

bool includes(const string a1[], int n1, const string a2[], int n2)
{
	if (n2 > n1)
		return false;
	if (n2 == 0 && a1 != a2)
		return false;
	if (n2 <= 0)
		return true;
	if (n1 <= 0)
		return false;
	if (a1[0] == a2[0])
	{
		if (n2 > 1)
			return includes(a1 + 1, n1 - 1, a2 + 1, n2 - 1);
	}
	else
		return includes(a1 + 1, n1 - 1, a2, n2);
}

//int main()
//{
//	string a[] = { "T", "F", "F", "T" };
//	string a1[] = { "T", "T", "T","T" };
//	string a2[] = { "T", "T", "T","F" };
//	string a3[] = { "a", "c", "g", "d", "h" };
//	string a4[] = { "b", "a", "b", "d", "g" };
//	string a5[] = { "b", "h", "b", "d", "a" };
//	string a6[] = {"stan", "kyle", "cartman", "kenny", "kyle", "cartman", "butters"};
//	string a7[] = { "kyle", "kenny", "butters" };
//	string a8[] = { "kyle", "cartman", "cartman" };
//	string a9[] = { "stan", "kenny", "kenny"};
//	string a10[] = { "a", "g", "h"};
//	string a11[] = { "stan"};
//	string a12[] = { "kyle"};
//
//	string a13[] = {"T"};
//	string a14[] = { "F" };
//
//	assert(!allTrue(a, 4));
//	assert(allTrue(a1, 4));
//	assert(!allTrue(a2, 4));
//	assert(allTrue(a13, 1));
//
//	assert(countFalse(a, 4) == 2);
//	assert(countFalse(a1, 4) == 0);
//	assert(countFalse(a2, 4) == 1);
//	assert(countFalse(a14, 1) == 1);
//
//	
//	assert(firstFalse(a, 4) == 1);
//	assert(firstFalse(a1, 4) == -1);
//	assert(firstFalse(a2, 4) == 3);
//	assert(firstFalse(a14, 1) == 0);
//
//	assert(indexOfLeast(a3, 5) == 0);
//	assert(indexOfLeast(a4, 5) == 1);
//	assert(indexOfLeast(a5, 5) == 4);
//
//	assert(includes(a6, 7, a7, 3) == true);
//	assert(includes(a6, 7, a8, 3) == true);
//	assert(includes(a6, 7, a9, 3) == false);
//	assert(includes(a6, 7, a11, 1) == true);
//	assert(includes(a6, 7, a12, 1) == true);
//	assert(includes(a3, 5, a10, 1) == true);
//
//	cout << "passed";
//}