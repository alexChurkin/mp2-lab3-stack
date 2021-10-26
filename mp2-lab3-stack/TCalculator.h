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
		postfix = other.postfix;
	}

	//�������� ������������
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