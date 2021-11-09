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
	string postfix;
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
	}

	string GetExpr() {
		return expr;
	}

	string GetPostfix() {
		return postfix;
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

	void PreparePostfix() {
		//�������� ������, ���������� ��������, ����� ���� ������������� � �����
		string infix = "(" + expr + ")";
		//������� ����������� ���������� � ����� �� ������ �����������
		postfix = "";
		st_char.Clear();

		for (int i = 0; i < infix.size(); i++)
		{
			//���� ����� - ������� � ��������� �����
			if (isdigit(infix[i]))
			{
				postfix += infix[i];
				postfix += " ";
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
				{
					postfix += st_char.Pop();
					postfix += " ";
				}
				//������ ���� ����������� ������
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
		//���������� �� ������� � �����, ���� �� �������
		if (postfix[postfix.size() - 1] == ' ')
		{
			postfix.pop_back();
		}
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
				//else throw "Exception: Too much operations: column "
					//+ to_string(i + 1) + "of the postfix string";

				//������� ����� ������ ������� (���� �� ����)
				if (st_d.IsNotEmpty()) {
					first = st_d.Pop();
				}
				//else throw "Exception: Too much operations: column "
					//+ to_string(i + 1) + "of the postfix string";


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
				//throw "Exception: Too many operands in the string";
			}
			return result;
		}
		//���� ���� �������� ���� �� ����� �������� ����������, �� ��������� �� ���� � ��������,
		//��� � ��������, �.�. � ��������� ������ ���������� ��-�� ���������� ��������� �������� �� ������
		else {
			//throw "Exception: No operands in the string";
		}
	}
};