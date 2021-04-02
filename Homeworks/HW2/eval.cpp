#include <iostream>
#include <string>
#include <stack>
#include <cassert>
using namespace std;

int evaluate(string infix, string& postfix, bool& result);
string toPostfix(string infix);
bool lessThanOrEqual(char c1, char c2);
void omitSpace(string& s);

int main()
{
	string pf;
	bool answer;
	assert(evaluate("T^ F", pf, answer) == 0 && pf == "TF^"  &&  answer);
	assert(evaluate("T^", pf, answer) == 1);
	assert(evaluate("F F", pf, answer) == 1);
	assert(evaluate("TF", pf, answer) == 1);
	assert(evaluate("()", pf, answer) == 1);
	assert(evaluate("()T", pf, answer) == 1);
	assert(evaluate("T(F^T)", pf, answer) == 1);
	assert(evaluate("T(&T)", pf, answer) == 1);
	assert(evaluate("(T&(F^F)", pf, answer) == 1);
	assert(evaluate("(T&&(F^F))", pf, answer) == 1);
	assert(evaluate("(T&(F^F))", pf, answer) == 0);
	assert(evaluate("", pf, answer) == 1);
	assert(evaluate("F  ^  !F & (T&F) ", pf, answer) == 0
		&& pf == "FF!TF&&^" && !answer);
	assert(evaluate(" F  ", pf, answer) == 0 && pf == "F" && !answer);
	assert(evaluate("((T))", pf, answer) == 0 && pf == "T"  &&  answer);
	//cout << "Passed all tests" << endl;
	return 0;
}

int evaluate(string infix, string& postfix, bool& result)
{
	postfix = toPostfix(infix);
	if (postfix == "bad")
		return 1;

	stack <int> operandStack;
	for (int i = 0; i < postfix.length(); i++)
	{
		char c = postfix[i];
		
		if (c == 'T' || c == 'F')
		{
			operandStack.push(c);
		}
		else if (c == '&' || c == '^')
		{
			char add;
			char operand1 = operandStack.top();
			operandStack.pop();
			char operand2 = operandStack.top();
			operandStack.pop();
			switch (c)
			{
			case '&':
				if (operand1 == 'F' || operand2 == 'F')
					add = 'F';
				break;
			case '^':
				if (operand1 == 'F' && operand2 == 'F')
					add = 'F';
				if (operand1 == 'T' && operand2 == 'T')
					add = 'F';
				if (operand1 == 'T' && operand2 == 'F')
					add = 'T';
				if (operand1 == 'F' && operand2 == 'T')
					add = 'T';
				break;
			}
			operandStack.push(add);
		}
		else if (c == '!')
		{
			char add;
			char operand = operandStack.top();
			operandStack.pop();
			if (operand == 'T')
				add = 'F';
			else if (operand == 'F')
				add = 'T';
			operandStack.push(add);
		}
		else
			return 1;
	}
	if (operandStack.top() == 'T')
		result = true;
	else if (operandStack.top() == 'F')
		result = false;
	return 0;
}
string toPostfix(string infix)
{
	string postfix = "";
	if (infix == postfix)
		return "bad";
	omitSpace(infix);
	stack <char> operatorStack;
	//if the beginning or end are not valid characters
	if (infix[0] == '&' || infix[0] == '^' || infix[infix.size()] == '&'
		|| infix[infix.size()] == '^' || infix[infix.size()] == '!')
		return "bad";

	for (int i = 0; i < infix.size(); i++)
	{
		char ch = infix[i];
		switch (ch)
		{
		case 'T': case 'F':
			if (i != infix.size())
			{
				if (infix[i + 1] == 'T' || infix[i + 1] == 'F' || infix[i + 1] == '(' || infix[ i + 1 ] == '!')
					return "bad";
			}
			postfix += ch;
			break;
		case '(':
			if (i + 1 == infix.size() || infix[i + 1] == ')')
				return "bad";
			operatorStack.push(ch);
			break;
		case')':
			while (operatorStack.top() != '(')
			{
				if (operatorStack.size() == 1 && operatorStack.top() != '(')
					return "bad";
				else if (i < postfix.size())
				{
					if (infix[i + 1] == '!' || infix[i + 1] == '(' || infix[i + 1] == 'T' || infix[i + 1] == 'F')
						return "bad";
				}
				if (operatorStack.top() != ' ')
				{
					postfix += operatorStack.top();
					operatorStack.pop();
				}
			}
			operatorStack.pop();
			break;
		case '&':
			//not at the end of the string, not followed by ), &, or ^
			if (i + 1 == infix.size() || infix[ i + 1 ] == ')' || infix[i + 1] == '&' || infix[i + 1] == '^')
				return "bad";
			while (!operatorStack.empty() && operatorStack.top() != '(')
			{
				if (lessThanOrEqual(ch, operatorStack.top()))
				{
					postfix += operatorStack.top();
					operatorStack.pop();
				}
				else
					break;
			}
			operatorStack.push(ch);
			break;
		case '^':
			//not at the end of the string, not followed by &, ^, )
			if (i + 1 == infix.size() || infix[i + 1] == '&' || infix[i + 1] == '^' || infix[i + 1] == ')')
				return "bad";
			while (!operatorStack.empty() && operatorStack.top() != '(')
			{
				if (lessThanOrEqual(ch, operatorStack.top()))
				{
					postfix += operatorStack.top();
					operatorStack.pop();
				}
				else
					break;
			}
			operatorStack.push(ch);
			break;
		case '!':
			//not 
			if (i + 1== infix.size() || infix[i + 1] == ')' || infix[i + 1] == '&' || infix[i + 1] == '^')
				return "bad";
			while (!operatorStack.empty() && operatorStack.top() != '(')
			{
				if (lessThanOrEqual(ch, operatorStack.top()))
				{
					postfix += operatorStack.top();
					operatorStack.pop();
				}
				else
					break;
			}
			operatorStack.push(ch);
			break;
		//if the character is none of the valid characters
		default:
			return "bad";
		}
	}
	while (!operatorStack.empty())
	{
		postfix += operatorStack.top();
		operatorStack.pop();
	}
	return postfix;
}
bool lessThanOrEqual(char c1, char c2)
{
	if (c1 == '^')
		return true;
	if (c1 == '&' && c2 == '^')
		return false;
	if (c1 == '&' && c2 == '!')
		return true;
	if (c1 == '&' && c2 == '&')
		return true;
	if (c1 == '!' && c2 == '!')
		return true;
	else
		return false;
}

void omitSpace(string& s)
{
	string temp = "";
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] != ' ')
			temp += s[i];
	}
	s = temp;
}

