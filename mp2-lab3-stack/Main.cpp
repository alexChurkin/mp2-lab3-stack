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

	cout << "1. Braces test:\n";
	cout << "==============\n\n";
	cout << "Enter some usual PREFIX expression:\n";
	getline(cin, str);

	calc.SetExpr(str);
	if (calc.CheckExpr()) {
		cout << "Braces are correct :)\n\n";
	}
	else {
		cout << "Braces are incorrect :(\n\n";
	}

	cout << "2. Postfix test:\n";
	cout << "===============\n\n";
	cout << "Enter some POSTFIX expression:\n";
	getline(cin, str);

	calc.SetExpr(str);
	cout << "Result: " << calc.Calc();

	return 0;
}