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
	setlocale(LC_NUMERIC, "eng");
	
	TCalculator calc;

	string str;

	while (true) {
		cout << "Enter your expression:\n\n";
		getline(cin, str);
		cout << "========================\n\n";
		calc.SetExpr(str);
		cout << "Expression: " << calc.GetExpr();

		bool bracesOk = calc.CheckExpr();
		if (bracesOk) {
			cout << "Braces are correct :)\n\n";
		}
		else {
			cout << "Braces are incorrect :(\n\n";
			continue;
		}

		cout << "Postfix: ";
		calc.PreparePostfix();
		cout << calc.GetPostfix() << "\n\n";

		cout << "Result (CalcPostfix):  ";
		try
		{
			cout << calc.CalcPostfix() << "\n";
		}
		catch (...)
		{
			cout << "Exception\n\n";
		}

		cout << "Result (Calc):         ";
		try
		{
			cout << calc.Calc() << "\n\n";
		}
		catch (...)
		{
			cout << "Exception\n\n";
		}
		cout << "==================================\n\n";
	}
	return 0;
}