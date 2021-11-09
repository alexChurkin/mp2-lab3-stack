#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include "TStack.h"

using namespace std;

class TCalculator {
	//������, ���������� ��������� �����. ���������
	//��������, (2+2)*2
	string expr;
	string postfix = "2 2 +";
	TStack<char> st_char;
	TStack<double> st_d;

	//�� ����� �������� ���������� � ���������
	int prior(char op) {
		switch (op) {
		//����� �� ������ ��������� ����������, ��� ������ �� ������,
		//�������� ������ ��������� 0 (������ ������ ��������� ����� ������ ��������)
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

		//���� �������� ������, ���������� ��������
		string infix = "(" + expr + ")";
		//������� ����������� ���������� � ����� �� ������ �����������
		postfix = "";
		st_char.Clear();

		for (int i = 0; i < infix.size(); i++)
		{
			//���� ����� - ������� � ��������� �����
			if (isdigit(infix[i]))
			{
				postfix += infix[i] + " ";
			}
			//���� ����������� ������ - ������ ������� � ����
			else if (infix[i] == '(')
			{
				st_char.Push(infix[i]);
			}
			//���� ����������� ������ - ����������� �� ����� � ��������� �� �� ������ (
			else if (infix[i] == ')')
			{
				while (st_char.Top() != '(')
					postfix += st_char.Pop() + " ";
				//������ ���� ����������� ������
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
	//�����������
	TCalculator() {
	}

	//����������
	~TCalculator() {
	}

	//����������� �����������
	TCalculator(const TCalculator& other) {
		expr = other.expr;
	}

	//�������� ������������
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

	//�������� ��������� �� ������������ ����������� ������
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

	//���������� �������� ��������� � ����������� ������
	//(���� ��� ��������� ������ ����� �� 1 �� 9, ������ ��� ������� �����)
	double Calc() {
		postfix = ToPostfix();

		//������ �� ����� ��������� �����������
		for (int i = 0; i < postfix.length(); i++)
		{
			//���� ������� ������ - �����, �� ����� ��� � ����
			if (postfix[i] >= '0' && postfix[i] <= '9') {
				st_d.Push(stod(&postfix[i]));
			}
			//���� ������ - ���� ����� ��������, �� �������� ��� ��������
			if (postfix[i] == '+' || postfix[i] == '-' ||
				postfix[i] == '*' || postfix[i] == '/' || postfix[i] == '^') {
				double second;
				double first;

				//������� ����� ������ ������� (���� �� ����)
				if (st_d.IsNotEmpty()) {
					second = st_d.Pop();
				}
				else throw "Exception: Too much operations: column "
					+ to_string(i + 1) + "of the postfix string";

				//������� ����� ������ ������� (���� �� ����)
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
			//���� � ����� ��� �������� �����, �� � ���. ������ ���� ������� ����� ���������
			if (st_d.IsNotEmpty()) {
				throw "Exception: Too many operands in the string";
			}
			return result;
		}
		//���� ���� �������� ���� �� ����� �������� ����������, �� ��������� �� ���� � ��������,
		//��� � ��������, �.�. � ��������� ������ ���������� ��-�� ���������� ��������� �������� �� ������
		else {
			throw "Exception: No operands in the string";
		}
	}
};