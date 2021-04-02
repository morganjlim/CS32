//#include "Sequence.h"
//#include <iostream>
//#include <cassert>
//using namespace std;
//
//int main()
//{
	//Sequence s;
	//assert(s.empty());
	//assert(s.find(42) == -1);
	//assert(s.insert(42) == 0);
	//assert(s.size() == 1 && s.find(42) == 0);

	//Sequence s;
	//s.insert(0, "a");
	//s.insert(1, "b");
	//s.insert(2, "c");
	//s.insert(3, "b");
	//s.insert(4, "e");
	//assert(s.remove("b") == 2);
	//assert(s.size() == 3);
	//string x;
	//assert(s.get(0, x) && x == "a");
	//assert(s.get(1, x) && x == "c");
	//assert(s.get(2, x) && x == "e");

	//Sequence s1;
	//s1.insert(0, "paratha");
	//s1.insert(0, "focaccia");
	//Sequence s2;
	//s2.insert(0, "roti");
	//s1.swap(s2);
	//assert(s1.size() == 1 && s1.find("roti") == 0 && s2.size() == 2 &&
	//	s2.find("focaccia") == 0 && s2.find("paratha") == 1);

	//Sequence s;
	//s.insert(0, "dosa");
	//s.insert(1, "pita");
	//s.insert(2, "");
	//s.insert(3, "matzo");
	//assert(s.find("") == 2);
	//s.remove("dosa");
	//assert(s.size() == 3 && s.find("pita") == 0 && s.find("") == 1 &&
	//	s.find("matzo") == 2);
//	cout << "passed all tests" << endl;
//
//
//	return 0;
//}
//#include "Sequence.h"
//#include <string>
//#include <iostream>
//#include <cassert>
//	using namespace std;
//
//	void test()
//	{
//		Sequence s;
//		s.insert(0, "lavash");
//		s.insert(0, "tortilla");
//		assert(s.size() == 2);
//		ItemType x = "injera";
//		assert(s.get(0, x) && x == "tortilla");
//		assert(s.get(1, x) && x == "lavash");
//	}
//
//	int main()
//	{
//		test();
//		cout << "Passed all tests" << endl;
//	}
#include "Sequence.h"
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
	//testing ItemType = int
	Sequence s;
	assert(s.empty());
	assert(s.find(42) == -1);
	assert(s.insert(42) == 0);
	assert(s.size() == 1 && s.find(42) == 0);

	Sequence s2;
	s2.insert(0, 10);
	s2.insert(0, 20);
	assert(s2.size() == 2);
	ItemType x = 999;
	assert(s2.get(0, x) && x == 20);
	assert(s2.get(1, x) && x == 10);

	Sequence s3;
	assert(s3.empty() == true);
	for (int i = 0; i < 15; i++)
		s3.insert(i);
	assert(s3.size() == 15);
	assert(s3.empty() == false);
	s3.insert(4);
	assert(s3.get(11, x) && x == 4);
	assert(s3.get(10, x) && x == 4);
	assert(s3.remove(4) == 2);
	assert(s3.size() == 14);
	assert(s3.erase(2) == true);
	assert(s3.size() == 13);

	s3.swap(s2);
	assert(s2.size() == 13);
	assert(s3.find(12) == -1);
	assert(s3.find(20) == 0);
	
}

int main()
{
	test();
	cout << "Passed all tests" << endl;
}

