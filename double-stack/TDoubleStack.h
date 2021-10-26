#pragma once
#include <iostream>
#include <cmath>
using namespace std;

template <class T>
class TDoubleStack {

private:
	//������ � ��� ������
	T* arr;
	int shared_size;
	//������ ������ �������������� 1 � 2 ������ (1-� ���������� �����, 2-� - ������)
	int pos1, pos2;
public:
	TDoubleStack(int _shared_size = 6)
	{
		//��� ������ ��������� ������� ���� �����, ��� �� 2 ��������
		if (_shared_size <= 1)
			throw "Exception: size of TDoubleStack cannot be <= 1";

		shared_size = _shared_size;
		arr = new T[_shared_size];

		//�����������: -> -1 [0 ... ... shared_size-1] shared_size <-
		pos1 = -1;
		pos2 = shared_size;
	}

	~TDoubleStack()
	{
		delete[] arr;
	}

	TDoubleStack(const TDoubleStack& other)
	{
		shared_size = other.shared_size;
		pos1 = other.pos1;
		pos2 = other.pos2;

		arr = new T[shared_size];

		//�������� ��������� 1-�� (������) �����
		for (int i = 0; i <= pos1; i++)
			arr[i] = other.arr[i];

		//�������� ��������� 2-�� (�������) �����
		for (int i = shared_size - 1; i >= pos2; i--)
			arr[i] = other.arr[i];
	}

	TDoubleStack& operator=(const TDoubleStack& other)
	{
		if (shared_size != other.shared_size) {
			delete[] arr;
			shared_size = other.shared_size;
			arr = new T[shared_size];
		}

		pos1 = other.pos1;
		pos2 = other.pos2;

		//�������� ��������� 1-�� (������) �����
		for (int i = 0; i <= pos1; i++)
			arr[i] = other.arr[i];

		//�������� ��������� 2-�� (�������) �����
		for (int i = shared_size - 1; i >= pos2; i--)
			arr[i] = other.arr[i];
	}

	bool IsEmpty1() {
		return (pos1 == -1);
	}

	bool IsEmpty2() {
		return (pos2 == shared_size);
	}

	bool IsFull() {
		return (pos2 - pos1) == 1;
	}

	//���������� �������� � 1-� (�����) ����
	void Push1(T item) {
		//��� ��������������� �������� ������ 1 � 2 ���������� ���������� ����������
		if (IsFull())
			throw "Exception: Impossible to Push1: no more size available";

		pos1++;
		arr[pos1] = item;
	}

	//���������� �������� �� 2-� (������) ����
	void Push2(T item) {
		//��� ��������������� �������� ������ 1 � 2 ���������� ���������� ����������
		if (IsFull())
			throw "Exception: Impossible to Push1: no more size available";

		pos2--;
		arr[pos2] = item;
	}

	//������ �������� �������� �� 1-�� (������) �����
	T Pop1() {
		if (IsEmpty1())
			throw "Exception: Can't do Pop1: Stack 1 is empty";

		T item = arr[pos1];
		pos1--;

		return item;
	}

	//������ �������� �������� �� 2-�� (�������) �����
	T Pop2() {
		if (IsEmpty2())
			throw "Exception: Can't do Pop2: Stack 2 is empty";

		T item = arr[pos2];
		pos2++;

		return item;
	}

	void Clear() {
		pos1 = -1;
		pos2 = shared_size;
	}

	friend ostream& operator<<(ostream& out, const TDoubleStack& s)
	{
		out << "[ ";
		//����� ������ �����
		for (int i = 0; i <= s.pos1; i++)
			out << s.arr[i] << ' ';

		out << "| ";

		//����� ������� �����
		for (int i = s.pos2; i <= s.shared_size - 1; i++)
			out << s.arr[i] << ' ';

		out << "]";
		return out;
	}
};