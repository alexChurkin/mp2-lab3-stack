#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include "TStack.h"

using namespace std;

class TCalculator {
	//Строка, содержащая некоторое арифм. выражение
	//Например, (2+2)*2
	string expr;
	string postfix = "2 2 +";
	TStack<char> st_char;
	TStack<double> st_d;

public:
	//Конструктор
	TCalculator() {
	}

	//Деструктор
	~TCalculator() {
	}

	//Конструктор копирования
	TCalculator(const TCalculator& other) {
		expr = other.expr;
		postfix = other.postfix;
	}

	//Оператор присваивания
	TCalculator& operator=(const TCalculator& other) {
		expr = other.expr;
		postfix = other.postfix;
		return *this;
	}

	void SetExpr(string _expr) {
		expr = _expr;
		//TODO Convert expr to postfix
		postfix = expr;
	}

	string GetExpr() {
		return expr;
	}

	//Проверка выражения на правильность расстановки скобок
	bool CheckExpr() {
		for (int i = 0; i < expr.length(); i++)
		{
			if (expr[i] == '(')
				st_char.Push(expr[i]);
			else if (expr[i] == ')')
			{
				if (st_char.IsEmpty()) return false;
				else st_char.Pop();
			}
		}
		return st_char.IsEmpty();
	}

	//Вычисление значения выражения в постфиксной записи
	//(пока что считывает только числа от 1 до 9, причём без дробной части)
	double Calc() {
		//Пройдём по всему выражению посимвольно
		for (int i = 0; i < postfix.length(); i++)
		{
			//Если текущий символ - число, то кладём его в стек
			if (postfix[i] >= '0' && postfix[i] <= '9') {
				st_d.Push(stod(&postfix[i]));
			}
			//Если символ - знак некой операции, то выполним эту операцию
			if (postfix[i] == '+' || postfix[i] == '-' ||
				postfix[i] == '*' || postfix[i] == '/' || postfix[i] == '^') {
				double second;
				double first;

				//Удалось взять второй операнд (стек не пуст)
				if (st_d.IsNotEmpty()) {
					second = st_d.Pop();
				}
				else throw "Exception: Too much operations: column "
					+ to_string(i + 1) + "of the postfix string";

				//Удалось взять первый операнд (стек не пуст)
				if (st_d.IsNotEmpty()) {
					first = st_d.Pop();
				}
				else throw "Exception: Too much operations: column "
					+ to_string(i + 1) + "of the postfix string";

				
				switch (postfix[i]) {
				case '+':
					st_d.Push(first + second);
					break;
				case '-':
					st_d.Push(first - second);
					break;
				case '*':
					st_d.Push(first * second);
					break;
				case '/':
					st_d.Push(first / second);
					break;
				case '^':
					st_d.Push(pow(first, second));
					break;
				}
			}
		}

		if (st_d.IsNotEmpty()) {
			double result = st_d.Pop();
			//Если в стеке ещё остались числа, то в исх. строке было слишком много операндов
			if (st_d.IsNotEmpty()) {
				throw "Exception: Too many operands in the string";
			}
			return result;
		}
		//Если стек оказался пуст на этапе возврата результата, то операндов не было в принципе,
		//Как и операций, т.к. в противном случае исключение из-за недостатка операндов возникло бы раньше
		else {
			throw "Exception: No operands in the string";
		}
	}
};