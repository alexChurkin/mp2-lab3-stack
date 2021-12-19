#include <iostream>

#include "TDoubleStack.h"
using namespace std;

int main()
{
	cout << "Double stack:\n";
	cout << "==================\n\n";

	cout << "> We have this stack (size = 10):" << '\n';
	TDoubleStack<int> s(10);

	for (int i = 0; i <= 4; i++)
	{
		s.Push1(i + 1);
	}

	for (int i = 5; i <= 9; i++)
	{
		s.Push2(i + 1);
	}

	cout << s << "\n\n";

	cout << "> Let's try to add one more element into our full double stack:" << '\n';
	try {
		s.Push1(10);
	}
	catch (...) {
		cout << "Exception: stack is full, no more size available\n\n";
	}

	cout << "> Then we can take the top element " << s.Pop1() << " from the 1-st stack:" << '\n';
	cout << s << "\n\n";

	cout << "> And push 500 to the 2-nd, for example:" << '\n';
	s.Push2(500);
	cout << s << "\n\n";

	cout << "> Then we can copy both of the stacks to another variable called s2:" << '\n';
	TDoubleStack<int> s2 = s;
	cout << s2 << "\n\n";

	cout << "> And clear s:\n";
	s.Clear();

	cout << "s:  " << s << "\n";
	cout << "s2: " << s2 << "\n\n";
}