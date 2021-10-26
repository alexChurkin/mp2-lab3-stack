#include <iostream>
using namespace std;

template <class T>
class TStack
{
private:
	//Просто массив
	T* arr;
	int size;
	//Номер последнего элемента стэка
	int pos;

public:
	TStack(int _size = 10)
	{
		if (_size <= 0)
			throw _size;

		size = _size;
		arr = new T[size];
		pos = -1;
	}

	~TStack()
	{
		delete[] arr;
	}

	TStack(const TStack& other)
	{
		size = other.size;
		pos = other.pos;

		arr = new T[size];

		for (int i = 0; i <= pos; i++)
			arr[i] = other.arr[i];
	}

	TStack& operator=(const TStack& other)
	{
		if (size != other.size)
		{
			delete[] arr;
			size = other.size;
			arr = new T[size];
		}

		pos = other.pos;

		for (int i = 0; i <= pos; i++)
			arr[i] = other.arr[i];
	}

	//Сравнение двух стэков
	bool operator==(const TStack& other)
	{
		if (size != other.size)
			return false;

		for (int i = 0; i < size; i++)
			if (arr[i] != other.arr[i])
				return false;

		return true;
	}

	bool IsEmpty()
	{
		return (pos == -1);
	}

	bool IsNotEmpty()
	{
		return (pos != -1);
	}

	bool IsFull()
	{
		return (pos == (size - 1));
	}

	bool IsNotFull()
	{
		return (pos < (size - 1));
	}

	void Push(T item)
	{
		if (IsFull())
			throw "Can't push: Stack is already full";

		pos++;
		arr[pos] = item;
	}

	T Pop()
	{
		if (IsEmpty())
			throw "Can't Pop: Stack is empty";

		T item = arr[pos];
		pos--;

		return item;
	}

	T Top()
	{
		if (IsEmpty())
			throw "Can't access top element: Stack is empty";

		return arr[pos];
	}

	void Clear()
	{
		pos = -1;
	}

	friend ostream& operator<<(ostream& out, const TStack& v)
	{
		for (int i = 0; i <= v.pos; i++)
			out << v.arr[i] << ' ';
		return out;
	}
};