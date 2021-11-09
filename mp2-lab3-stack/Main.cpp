#include <iostream>
#include <fstream>
#include <clocale>
#include <ctime>
#include <string>

#include "TCalculator.h"
using namespace std;

int main()
{
	setlocale(LC_ALL, "russian");
	
	TCalculator calc;

	string str;

	while (true) {
		cout << "Enter some expression:\n";
		getline(cin, str);
		cout << '\n';
		calc.SetExpr(str);

		cout << "1. Braces:\n";
		cout << "==========================\n";
		bool bracesOk = calc.CheckExpr();

		if (bracesOk) {
			cout << "Braces are correct :)\n";
			cout << "==========================\n\n";
		}
		else {
			cout << "Braces are incorrect :(\n";
			cout << "==========================\n\n\n";
			continue;
		}

		cout << "2. Translation to postfix:\n";
		cout << "==========================\n";
		calc.PreparePostfix();
		cout << "Result: " << calc.GetPostfix() << "\n";
		cout << "==========================\n\n";

		cout << "3. Calculation result:\n";
		cout << "==========================\n";
		cout << "Result: " << calc.Calc() << "\n";
		cout << "==========================\n\n\n";
	}
	return 0;
}