#include <iostream>
#include <fstream> //Including the <fstream> header defines two classes: std::ifstream,
					//the input file stream class, and std::ofstream, the output file stream class.
#include <string>
#include "HashTable.h"
using namespace std;



//notes:

//add instruction: A(length):(text); length = length of text, text = character sequence
	//things 2 check: check that length is valid(not negative or greater than what is in the file)
	//check that the text length is same as length
//copy instruction: C(length),(offset); length = length of text, offset in original file
	//things 2 check: check that length is valid(not negative/greater than what it is in the file)
	//check that the offset is valid(not negative/greater than length of file)
//do nothing instruction: newline character ('\n') or single carriage return character ('\r')

//instructions that are valid but weird:
	//A0: does nothing
	//C0,12; also does nothing
	//^for those to applyDiff can just return false, having it no longer change anything
	//A005:Hello is valid and is the same thing as A5:Hello

bool getInt(istream& inf, int& n);
bool getCommand(istream& inf, char& cmd, int& length, int& offset);
void createDiff(istream& fold, istream& fnew, ostream& fdiff)
{
	string sold(""), add("");
	//put the contents of the old file into a string
	while (fold.peek() != EOF)
	{
		getline(fold, add);
		sold += add + '\n';
	}
	int n(12);

	HashTable h;

	//put substrings of the old file into hash table
	for (int i = 0; i < n; i++)
	{
		for (int offset = i; offset < sold.size(); offset += n)
		{
			h.insert(offset, sold.substr(offset, n));
		}
	}
	//while (fnew.peek() != EOF)
	//{
	//	string temp = "";
	//	Node* p;
	//	int lastOffset(-1);
	//
	//	for (int i = 0; i < n && fnew.peek() != EOF; i++)
	//	{
	//		temp += fnew.get();
	//	}
	//	
	//	if (h.find(temp, p, lastOffset))
	//	{
	//		int begPos = fnew.tellg(), searches(0),longestOffset(-1), longestMatch(-1);
	//		begPos -= temp.size();
	//
	//		while (h.find(temp, p, lastOffset) && searches <= 100)
	//		{
	//			int offset = p->m_offset;
	//			int length(temp.size());
	//			bool match(true);
	//			while (match && p->m_next != nullptr)
	//			{
	//				int templength(0);
	//				string comp = "";
	//				for (int i = 0; i < n && fnew.peek() != EOF; i++)
	//					comp += fnew.get();
	//
	//				string check = p->m_next->m_data;
	//				for (int i = 0; i < comp.size() && i < check.size(); i++)
	//				{
	//					if (check[i] == comp[i])
	//					{
	//						templength++;
	//					}
	//					else
	//					{
	//						match = false;
	//						break;
	//					}
	//				}
	//				length += templength;
	//				for (int i = 0; i < comp.size() - templength; i++)
	//					fnew.unget();
	//				p = p->m_next;
	//			}
	//
	//			if (length > longestMatch)
	//			{
	//				longestMatch = length;
	//				longestOffset = offset;
	//			}
	//			fnew.seekg(begPos);
	//			lastOffset = offset;
	//			searches++;
	//		}
	//		fnew.seekg(begPos + longestMatch);
	//		fdiff << "C" << longestMatch << "," << longestOffset;
	//	}

	//while not the end of the file
	while (fnew.peek() != EOF)
	{
		string temp = "";
		Node* p;
	
		//get a string of size n from the new file stream
		for (int i = 0; i < n && fnew.peek() != EOF; i++)
		{
			temp += fnew.get();
		}
		//look for it in the hash table
		if (h.find(temp, p, -1))
		{
			//if found
			int length(temp.size());
			bool match(true);
			int offset = p->m_offset;
			while (match && p->m_next != nullptr)
			{
				int templength(0);
				string comp = "";
				//check the next set of character from the new file stream
				for (int i = 0; i < n && fnew.peek() != EOF; i++)
					comp += fnew.get();
				
				string check = p->m_next->m_data;
				//if they are the same then go back through the while loop
				//otherwise
				for (int i = 0; i < comp.size() && i < check.size(); i++)
				{
					if (check[i] == comp[i])
					{
						templength++;
					}
					else
					{
						match = false;
						break;
					}
				}
				length += templength;
				for (int i = 0; i < comp.size() - templength; i++)
					fnew.unget();
				p = p->m_next;
			}
			//once there are no more matches add the command to the diff file
			fdiff << "C" << length << "," << offset;
		}
		else
		{
			//if there is no match
			for (int i = 0; i < temp.size() - 1; i++)
				fnew.unget();
			temp = temp[0];
			bool match(false);
			while (!match)
			{
				//keep looking for string that are not found in the old file
				string comp = "";
				for (int i = 0; i < n && fnew.peek() != EOF; i++)
					comp += fnew.get();
				if (comp.size() < 4)
				{
					temp += comp;
					break;
				}
				if (h.find(comp, p, -1))
				{
					for (int i = 0; i < comp.size(); i++)
						fnew.unget();
					match = true;
				}
				else
				{
					temp += comp[0];

					for (int i = 0; i < comp.size() - 1; i++)
						fnew.unget();
				}
			}
			//add command to diff file
			fdiff << "A" << temp.size() << ":" << temp;
		}
	}
}
//returns true if operation succeeded. returns false if operation fails for reasons:
//because diff file is malformed, character other than A or C where command is expected
//or offset length is invalid
bool applyDiff(istream& fold, istream& fdiff, ostream& fnew)
{
	char cmd('\0');
	int len(0), offset(0);
	string sold(""), temp(""), add("");
	fold.seekg(0);

	//put the entire old file into a string
	while (!fold.eof())
	{
		getline(fold, add);
		sold += add + '\n';
	}

	//while the command is not the end of file command
	while (cmd != 'x')
	{
		//get teh comang
		if (!getCommand(fdiff, cmd, len, offset))
			return false;
		//based on what was returned for cmd determine what to do
		switch (cmd)
		{
		case 'A':
			for (int i = 0; i < len; i++)
			{
				char c;
				fdiff.get(c);
				fnew << c;
			}
			break;
		case 'C':
			temp = sold.substr(offset, len);
			fnew << temp;
			break;
		case '\r':
		case '\n':
			break;
		}
	}
	return true;
}

int main()
{
	//hashtable testing

	//HashTable h;
	//Node p;
	//Node* ptr = &p;
	//
	//string arr[] = { "desert", "bless", "planes", "finicky", "iron", "miscreant",
	//				"fanatical", "energetic", "history", "nice", "selective", "claim",
	//				"cause", "sock", "poised", "clap", "hall", "wet", "understood", "writing"};
	//for (int i = 0; i < 20; i++)
	//	h.insert(i, arr[i]);
	//for (int i = 0; i < 20; i++)
	//{
	//	if (!h.find(arr[i], ptr))
	//	{
	//		cout << "not found!" <<endl;
	//	}
	//	cout << ptr->offset() << " " << ptr->data() << " " << ptr->next() << endl;
	//}
	//
	//cout << "all found!";

	//ifstream oldMart("smallmart1.txt");
	//ifstream changeMart("smallmart2.txt");
	//ofstream diffMart("diffMart.txt");

	//createDiff(oldMart, changeMart, diffMart);

	//ifstream oldEggs("greeneggs1.txt");
	//ifstream changeEggs("greeneggs2.txt");
	//ofstream diffEggs("diffEggs.txt");

	//createDiff(oldEggs, changeEggs, diffEggs);

	//ifstream oldWar("warandpeace1.txt");
	//ifstream changeWar("warandpeace2.txt");
	//ofstream diffWar("diffWar.txt");

	//createDiff(oldWar, changeWar, diffWar);

	//ifstream oldStrange("strange1.txt");
	//ifstream changeStrange("strange2.txt");
	//ofstream diffStrange("diffStrange.txt");

	//createDiff(oldStrange, changeStrange, diffStrange);

	/************************************************************************/

	//ifstream oldEggs("greeneggs1.txt");
	//ifstream diffEggs2("diffEggs.txt");
	//ofstream changeEggs2("newEggs.txt");

	//applyDiff(oldEggs, diffEggs2, changeEggs2);

	//ifstream oldMart("smallmart1.txt");
	//ifstream diffMart("diffMart.txt");
	//ofstream changeMart("newMart.txt");

	//applyDiff(oldMart, diffMart, changeMart);

	//ifstream oldWar("warandpeace1.txt");
	//ifstream diffWar("diffWar.txt");
	//ofstream changeWar("newWar.txt");

	//applyDiff(oldWar, diffWar, changeWar);

	//ifstream oldStrange("strange1.txt");
	//ifstream diffStrange("diffStrange.txt");
	//ofstream changeStrange("newStrange.txt");

	//applyDiff(oldStrange, diffStrange, changeStrange);

	return 0;
}

bool getInt(istream& inf, int& n)
{
	char ch;
	if (!inf.get(ch) || !isascii(ch) || !isdigit(ch))
		return false;
	inf.unget();
	inf >> n;
	return true;
}

bool getCommand(istream& inf, char& cmd, int& length, int& offset)
{
	if (!inf.get(cmd))
	{
		cmd = 'x';  // signals end of file
		return true;
	}
	char ch;
	switch (cmd)
	{
	case 'A':
		return getInt(inf, length) && inf.get(ch) && ch == ':';
	case 'C':
		return getInt(inf, length) && inf.get(ch) && ch == ',' && getInt(inf, offset);
	case '\r':
	case '\n':
		return true;
	}
	return false;
}