#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include "TLStack.h"

using namespace std;

class TLCalculator
{
	//Строка, содержащая некоторое арифметическое выражение
	//Например, (2 + 2) * 2
	string expr;
	string postfix;
	TLStack<char> st_char;
	TLStack<double> st_d;

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

public:

	TLCalculator() {
	}

	~TLCalculator() {
	}

	TLCalculator(const TLCalculator& other) {
		expr = other.expr;
		postfix = other.postfix;
	}

	TLCalculator& operator=(const TLCalculator& other) {
		expr = other.expr;
		postfix = other.postfix;
		return *this;
	}

	void SetExpr(string _expr) {
		expr = _expr;
	}

	string GetExpr() {
		return expr;
	}

	string GetPostfix() {
		return postfix;
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

	void PreparePostfix() {
		//Исходная строка, обрамлённая скобками, чтобы стек самоочистился в конце
		string infix = "(" + expr + ")";
		//Очистка предыдущего результата и стека от старых результатов
		postfix = "";
		st_char.Clear();

		for (int i = 0; i < infix.size(); i++)
		{
			//Если число - допишем в результат сразу
			if (isdigit(infix[i]))
			{
				size_t idx;
				double tmp = stod(&infix[i], &idx);

				ostringstream ss;
				ss << tmp;

				postfix += ss.str();
				postfix += " ";

				//К счётчику прибавляется индекс, чтобы пропустить длинное число
				//-1, т.к. сам цикл сделает i++ затем
				i += idx - 1;
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
				{
					postfix += st_char.Pop();
					postfix += " ";
				}
				//Удалим открывающую скобку
				st_char.Pop();
			}
			else if ((infix[i] == '+') || (infix[i] == '-') || (infix[i] == '*') || (infix[i] == '/') || (infix[i] == '^'))
			{
				while (prior(infix[i]) <= prior(st_char.Top()))
				{
					postfix += st_char.Pop();
					postfix += " ";
				}
				st_char.Push(infix[i]);
			}
		}
		//Избавление от пробела в конце, если он остался
		if (!postfix.empty())
			postfix.pop_back();
	}

	//Вычисление значения выражения в постфиксной записи
	//(считывает только числа от 1 до 9 без дробной части)
	double CalcPostfix() {
		if (postfix.empty()) throw "Empty";
		//Пройдём по всему выражению посимвольно
		for (int i = 0; i < postfix.length(); i++)
		{
			//Если текущий символ - число, то кладём его в стек
			if (postfix[i] >= '0' && postfix[i] <= '9') {

				size_t idx;
				double tmp = stod(&postfix[i], &idx);
				st_d.Push(tmp);
				//К счётчику прибавляется индекс, чтобы пропустить длинное число
				//-1, т.к. сам цикл сделает i++ затем
				i += idx - 1;
			}
			//Если символ - знак некой операции, то выполним эту операцию
			else if (postfix[i] == '+' || postfix[i] == '-' ||
				postfix[i] == '*' || postfix[i] == '/' || postfix[i] == '^') {
				double second;
				double first;

				//Удалось взять второй операнд (стек не пуст)
				if (st_d.IsNotEmpty()) {
					second = st_d.Pop();
				}
				else throw "Exception: Too much operations: column "
					+ to_string(i + 1) + " of the postfix string";

				//Удалось взять первый операнд (стек не пуст)
				if (st_d.IsNotEmpty()) {
					first = st_d.Pop();
				}
				else throw "Exception: Too much operations: column "
					+ to_string(i + 1) + " of the postfix string";


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

	//Вычисление значения выражения сразу
	double Calc()
	{
		string infix = "(" + expr + ")";

		st_char.Clear();
		st_d.Clear();

		for (int i = 0; i < infix.length(); i++)
		{
			//Скобка - добавляется в стек операций
			if (infix[i] == '(')
			{
				st_char.Push(infix[i]);
			}
			//Число - считывается и добавляется в стек операндов
			else if (isdigit(infix[i]))
			{
				size_t idx;
				double tmp = stod(&infix[i], &idx);
				st_d.Push(tmp);
				//К счётчику прибавляется индекс, чтобы пропустить длинное число
				//-1, т.к. сам цикл сделает i++ затем
				i += idx - 1;
			}
			//Операция - добавляется в стек операций
			else if ((infix[i] == '+') || (infix[i] == '-') || (infix[i] == '*') || (infix[i] == '/') || (infix[i] == '^'))
			{
				//Если операция имеет приоритет ниже операции на вершине стека операций,
				//Выполняются все более приоритетные операции из стека (до достижения <= по приоритету)
				//и их результаты каждый раз попадают в стек операндов
				while (prior(infix[i]) <= prior(st_char.Top()))
				{
					if (st_d.IsEmpty())
						throw "Exception: Too much operations";
					double second = st_d.Pop();

					if (st_d.IsEmpty())
						throw "Exception: Too much operations";
					double first = st_d.Pop();

					char op = st_char.Pop();

					switch (op)
					{
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
				st_char.Push(infix[i]);
			}
			//Закрывающая скобка ) - выполняем из стека операций всё до открывающей (
			else if (infix[i] == ')')
			{
				while (st_char.Top() != '(')
				{
					if (st_d.IsEmpty()) throw "Exception: Too much operations";
					double second = st_d.Pop();

					if (st_d.IsEmpty()) throw "Exception: Too much operations";
					double first = st_d.Pop();

					char op = st_char.Pop();

					switch (op)
					{
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
				//Удалим открывающую скобку
				st_char.Pop();
			}
		}

		if (st_d.IsEmpty()) throw "Exception: No operands in the string";
		double result = st_d.Pop();

		//Если в стеке ещё остались числа, то в исх. строке было слишком много операндов
		if (st_d.IsNotEmpty()) throw "Exception: Too many operands in the string";

		return result;
	}
};