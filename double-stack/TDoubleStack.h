#pragma once
#include <iostream>
#include <cmath>
using namespace std;

template <class T>
class TDoubleStack {

private:
	//Массив и его размер
	T* arr;
	int shared_size;
	//Номера вершин соответственно 1 и 2 стеков (1-й начинается слева, 2-й - справа)
	int pos1, pos2;
public:
	TDoubleStack(int _shared_size = 6)
	{
		//Нет смысла создавать двойной стек менее, чем на 2 элемента
		if (_shared_size <= 1)
			throw "Exception: size of TDoubleStack cannot be <= 1";

		shared_size = _shared_size;
		arr = new T[_shared_size];

		//Иллюстрация: -> -1 [0 ... ... shared_size-1] shared_size <-
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

		//Перепись элементов 1-го (левого) стека
		for (int i = 0; i <= pos1; i++)
			arr[i] = other.arr[i];

		//Перепись элементов 2-го (правого) стека
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

		//Перепись элементов 1-го (левого) стека
		for (int i = 0; i <= pos1; i++)
			arr[i] = other.arr[i];

		//Перепись элементов 2-го (правого) стека
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

	//Добавление элемента в 1-й (левый) стек
	void Push1(T item) {
		//При соприкосновении верхушек стеков 1 и 2 продолжать добавление невозможно
		if (IsFull())
			throw "Exception: Impossible to Push1: no more size available";

		pos1++;
		arr[pos1] = item;
	}

	//Добавление элемента во 2-й (правый) стек
	void Push2(T item) {
		//При соприкосновении верхушек стеков 1 и 2 продолжать добавление невозможно
		if (IsFull())
			throw "Exception: Impossible to Push1: no more size available";

		pos2--;
		arr[pos2] = item;
	}

	//Взятие верхнего элемента из 1-го (левого) стека
	T Pop1() {
		if (IsEmpty1())
			throw "Exception: Can't do Pop1: Stack 1 is empty";

		T item = arr[pos1];
		pos1--;

		return item;
	}

	//Взятие верхнего элемента из 2-го (правого) стека
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
		//Вывод левого стека
		for (int i = 0; i <= s.pos1; i++)
			out << s.arr[i] << ' ';

		out << "| ";

		//Вывод правого стека
		for (int i = s.pos2; i <= s.shared_size - 1; i++)
			out << s.arr[i] << ' ';

		out << "]";
		return out;
	}
};