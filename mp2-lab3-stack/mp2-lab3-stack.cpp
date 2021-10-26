#include <iostream>
#include <fstream>
#include <clocale>
#include <ctime>
#include <string>

#include "TStack.h"
using namespace std;


bool HasCorrectBraces(string str)
{
	TStack<char> s(str.length());

	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == '(')
			s.Push(str[i]);
		else if (str[i] == ')')
		{
			if (s.IsEmpty()) return false;
			else s.Pop();
		}
	}
	return s.IsEmpty();
}

int main()
{
	setlocale(LC_ALL, "russian");
	TStack<int> s(20);
	s.Push(1);
	s.Push(2);
	s.Push(50);

	cout << "> We have stack 1, 2, 50:\n";
	cout << "  " << s << "\n\n";
	cout << "> Pop " << s.Pop() << ":\n";
	cout << "  " << s << "\n\n";


	cout << "Enter your string with braces:\n";
	string str;
	getline(cin, str);

	if (HasCorrectBraces(str))
		cout << "Braces are correct :)";
	else
		cout << "Braces are INCORRECT :(";

	return 0;
}