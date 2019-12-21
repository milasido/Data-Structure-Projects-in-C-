#include <iostream>
#include <string>
#include <stack>
#include <fstream>
#include "ArgumentManager.h"
using namespace std;

//check operator
bool isOperator(char c)
{
	if (c == '+' || c == '-')
		return true;
	else return false;
}
//check operrand
bool isOperand(char c)
{
	if (c != '+' && c != '-' && c != '(' && c != ')' && c != '{' && c != '}' && c != '[' && c != ']')
		return true;
	else return false;
}
//check number
bool isNumber(char c)
{
	if (c >= '0' && c <= '9') return true;
	else return false;
}
//check letter
bool isLetter(char c)
{
	if (isOperand(c) && !isNumber(c)) return true;
	else return false;
}
//check parenthese
bool isParenth(char c)
{
	if (c == '(' || c == '{' || c == '[' || c == ')' || c == '}' || c == ']')
		return true;
	else return false;
}
//check open parenthese
bool isOpenParenth(char c)
{
	if (c == '(' || c == '{' || c == '[')
		return true;
	else return false;
}
// check close parenthese
bool isCloseParenth(char c)
{
	if (c == ')' || c == '}' || c == ']')
		return true;
	else return false;
}
//read file
string **read(string filename, int &k)
{
	ifstream input;
	string **arr = new string *[1000];
	for (int i = 0; i < 1000; i++)
		arr[i] = new string[1];

	string line;
	input.open(filename);
	while (getline(input, line))
	{
		if (!line.empty())
		{
			*arr[k] = line;
			k++;
		}
	}
	return arr;
}
// check balanced
bool checkvalid(string s)
{
	stack<char> stc;
	for (int i = 0; i < s.length(); i++)
	{
		if (isCloseParenth(s[i]) && stc.empty())
		{
			return false;
			break;
		}
		else if (s[i] == '(' || s[i] == '{' || s[i] == '[')
		{
			stc.push(s[i]);
		}
		else if (s[i] == ')')
		{
			if (stc.top() == '(')
			{
				stc.pop();
			}
			else break;
		}
		else if (s[i] == ']')
		{
			if (stc.top() == '[')
			{
				stc.pop();
			}
			else break;
		}
		else if (s[i] == '}')
		{
			if (stc.top() == '{')
			{
				stc.pop();
			}
			else break;
		}		
	}
	if (stc.empty()) return true;
}
//correct the expression
void correct_expression(string &s)
{
	if (isOperator(s[0])) s.insert(0, "0");
	while(s.find("(-") != string::npos)	s.replace(s.find("(-"), 2, "(0-");		
	while (s.find("[-") != string::npos) s.replace(s.find("[-"), 2, "[0-");	
	while (s.find("{-") != string::npos) s.replace(s.find("{-"), 2, "{0-");
	while (s.find("(+") != string::npos) s.replace(s.find("(+"), 2, "(0+");
	while (s.find("[+") != string::npos) s.replace(s.find("[+"), 2, "[0+");
	while (s.find("{+") != string::npos) s.replace(s.find("{+"), 2, "{0+");
	while (s.find("--") != string::npos) s.replace(s.find("--"), 2, "+");
	while (s.find("-+") != string::npos) s.replace(s.find("-+"), 2, "-");
	while (s.find("+-") != string::npos) s.replace(s.find("+-"), 2, "-");
	while (s.find("++") != string::npos) s.replace(s.find("++"), 2, "+");
	//cout <<"corrected: "<< s << endl;
}
//infix to posfix
string convert_to_postfix(string &s)
{
	correct_expression(s);
	stack<char> stc;
	string p;
	char temp;
	for (int i = 0; i < s.length(); i++)
	{
		if (isOperand(s[i])) 
			p += s[i];
		else if (isOperator(s[i]) && stc.empty())
		{
			stc.push(s[i]);
		}
		else if ((isOperator(s[i]) && !stc.empty()) && !isOpenParenth(stc.top()))
		{
			p += stc.top();
			stc.pop();
			stc.push(s[i]);
		}
		else if (isOpenParenth(s[i]))
		{
			stc.push(s[i]);
		}
		else if (isOperator(s[i]) && isOpenParenth(stc.top()))
		{
			stc.push(s[i]);
		}
		else if (isCloseParenth(s[i]))
		{
			while (!isOpenParenth(stc.top()))
			{
				p += stc.top();
				stc.pop();
			}
			if (isOpenParenth(stc.top()))
			{
				stc.pop();
			}
		}
	}
	if (!stc.empty()) p += stc.top();
	return p;
}
//evaluate expression
int evaluate(string s)
{
	stack<int> sti;
	for (int i = 0; i < s.length(); i++)
	{
		if (isLetter(s[i])) s[i] *= s[i];
	}
	for (int i = 0; i < s.length(); i++)
	{
		if (isLetter(s[i]))
			sti.push(s[i]);
		else if (isNumber(s[i]))
			sti.push(s[i] - '0');//convert char number to int
		else if (s[i] == '+')
		{
			int x = sti.top(); sti.pop(); //take out 2 operand, add, push back
			int y = sti.top(); sti.pop();
			sti.push(x + y);
		}
		else if (s[i] == '-')
		{
			int x = sti.top(); sti.pop();
			int y = sti.top(); sti.pop();
			sti.push(y - x);
		}
	}
	return sti.top();
}
//check error
bool allFileValid(string **arr, int count)
{
	int k = 0;
	for (int i = 0; i < count; i++)
	{
		if (checkvalid(*arr[i]) != true)
		{
			k++;
		}
	}
	if (k==0) 
		return true;
	else return false;
}
//check similarity
bool checkSimilarity(string **arr, int count)
{
	int k = 0;
	for (int i = 0; i < count; i++)
	{
		if (evaluate(*arr[0]) != evaluate(*arr[i]))
		{
			k++;
		}
	}
	if (k > 0) 
		return false; 
	else return true;
}
int main(int argc, char* argv[])
{
	ArgumentManager am(argc, argv);
	string input = am.get("input");
	string output = am.get("output");

//int main()
//{	
//	string input = "input18.txt";
//	string output = "1111.txt";

	ofstream ofs;
	ofs.open(output);
	int count = 0;
	string **arr = read(input, count);

	if (allFileValid(arr, count) != true)
	{
		for (int i = 0; i < count; i++)
		{
			if (checkvalid(*arr[i]) != true)
			{
				//cout << "Error at: " << i + 1 << endl;
				ofs << "Error at: " << i + 1 << endl;
			}
		}
	}
	else
	{//convert all expressions into postfix
		for (int i = 0; i < count; i++)
		{
			*arr[i] = convert_to_postfix(*arr[i]);
		}
		if (checkSimilarity(arr, count) == true)
		{
			//cout << "yes" << endl;
			ofs << "yes" << endl;
		}
		else
		{
			//cout << "no" << endl;
			ofs << "no" << endl;
		}
	}
	
	ofs.close();

	//delete[]arr;
	//system("pause");
	return 0;
}