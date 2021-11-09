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

	//По знаку операции возвращает её приоритет
	int prior(char op) {
		switch (op) {
		//Чтобы не писать отдельный обработчик, при работе со стеком,
		//назначим скобке приоритет 0 (наверх скобки заносится любая лругая операция)
		case '(': return 0;
		case '+': return 1;
		case '-': return 1;
		case '*': return 2;
		case '/': return 2;
		case '^': return 3;
		}
		return 0;
	}

	string ToPostfix() {
		string postfixResult = "";

		//Наша исходная строка, обрамлённая скобками
		string infix = "(" + expr + ")";
		//Очистка предыдущего результата и стека от старых результатов
		postfix = "";
		st_char.Clear();

		for (int i = 0; i < infix.size(); i++)
		{
			//Если число - допишем в результат сразу
			if (isdigit(infix[i]))
			{
				postfix += infix[i] + " ";
			}
			//Если открывающая скобка - просто запишем в стек
			else if (infix[i] == '(')
			{
				st_char.Push(infix[i]);
			}
			//Если закрывающая скобка - вытаскиваем из стека в результат всё до первой (
			else if (infix[i] == ')')
			{
				while (st_char.Top() != '(')
					postfix += st_char.Pop() + " ";
				//Удалим саму закрывающую скобку
				st_char.Pop();
			}
			else if ((infix[i] == '+') || (infix[i] == '-') || (infix[i] == '*') || (infix[i] == '/') || (infix[i] == '^'))
			{
				while (prior(infix[i]) <= prior(st_char.Top()))
				{
					postfix += st_char.Pop() + " ";
				}
				st_char.Push(infix[i]);
			}
		}

		return postfixResult;
	}

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
	}

	//Оператор присваивания
	TCalculator& operator=(const TCalculator& other) {
		expr = other.expr;
		return *this;
	}

	void SetExpr(string _expr) {
		expr = _expr;
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
		postfix = ToPostfix();

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