#pragma once
#include <iostream>

/* TLStackException - класс исключения для TLStack */

class TLStackException
{
private:
	std::string desc;

public:
	TLStackException(std::string _desc)
	{
		desc = _desc;
	}
	TLStackException(const TLStackException& e)
	{
		desc = e.desc;
	}

	friend std::ostream& operator<<(std::ostream& os, const TLStackException& e)
	{
		os << "Exception message: " << e.desc << '\n';
		return os;
	}
};

/* TNode - звено списка */

template <class T>
struct TNode
{
	T value;
	TNode* pNext;
};

/* TLStack - стек на основе односвязного списка */

template <class T>
class TLStack
{
private:
	//Вершина - первый элемент списка
	TNode<T>* pFirst;

public:
	TLStack();
	TLStack(const TLStack<T>& other);
	~TLStack();

	TLStack<T>& operator=(const TLStack<T>& other);

	bool IsEmpty() const;
	bool IsNotEmpty() const;

	bool operator==(const TLStack<T>& other) const;
	bool operator!=(const TLStack<T>& other) const;

	void Push(T value);
	T Pop();
	T Top() const;

	void Clear();

	friend std::ostream& operator<<(
		std::ostream& out,
		const TLStack<T>& s)
	{
		TNode<T>* node = s.pFirst;

		out << "[ ";
		while (node != nullptr)
		{
			out << node->value << ' ';
			node = node->pNext;
		}
		out << "]";

		return out;
	}

private:
	void CopyNodesFrom(const TLStack<T>& other);
};

template <class T>
TLStack<T>::TLStack(): pFirst(nullptr) {}

template <class T>
TLStack<T>::TLStack(const TLStack& other)
{
	pFirst = nullptr;
	CopyNodesFrom(other);
}

template <class T>
TLStack<T>::~TLStack()
{
	Clear();
}

template <class T>
TLStack<T>& TLStack<T>::operator=(
	const TLStack<T>& other
)
{
	if (this == &other)
		return *this;

	Clear();
	CopyNodesFrom(other);
}

template <class T>
bool TLStack<T>::IsEmpty() const
{
	return pFirst == nullptr;
}

template <class T>
bool TLStack<T>::IsNotEmpty() const
{
	return pFirst != nullptr;
}

template <class T>
bool TLStack<T>::operator==(
	const TLStack<T>& other
) const
{
	TNode<T> *node = pFirst;
	TNode<T> *nodeOther = other.pFirst;

	//Сравнение элементов звеньев
	while (node != nullptr && nodeOther != nullptr)
	{
		if (node->value != nodeOther->value) return false;
		node = node->pNext;
		nodeOther = nodeOther->pNext;
	}

	//Если в стеках разное число элементов -
	//они не равны
	if (node != nullptr || nodeOther != nullptr)
		return false;

	return true;
}

template <class T>
bool TLStack<T>::operator!=(
	const TLStack<T>& other
) const
{
	return !operator==(other);
}

template <class T>
void TLStack<T>::Push(T value)
{
	TNode<T>* newNode = new TNode<T>();
	newNode->value = value;
	newNode->pNext = pFirst;
	pFirst = newNode;
}

template <class T>
T TLStack<T>::Pop()
{
	if (pFirst == nullptr)
		throw TLStackException("Can't pop from an empty stack");

	TNode<T>* oldFirst = pFirst;
	T topValue = oldFirst->value;

	pFirst = oldFirst->pNext;
	delete oldFirst;

	return topValue;
}

template <class T>
T TLStack<T>::Top() const
{
	if (pFirst == nullptr)
		throw TLStackException(
			"Can't get top element of an empty stack");
	return pFirst->value;
}

//Удаляет все элементы стека (все звенья списка)
template <class T>
void TLStack<T>::Clear()
{
	/* Последовательное удаление звеньев,
       начиная с 1-го */
	TNode<T>* node;
	while (pFirst != nullptr)
	{
		node = pFirst;
		pFirst = pFirst->pNext;
		delete node;
	}
}

/* Последовательное копирование звеньев,
   начиная с 1-го */
template <class T>
void TLStack<T>::CopyNodesFrom(
	const TLStack<T>& other
)
{
	if (other.IsNotEmpty())
	{
		TNode<T>* newNode;
		//Копирование первого звена
		newNode = new TNode<T>;
		newNode->value = other.pFirst->value;
		newNode->pNext = nullptr;
		pFirst = newNode;

		//Копирование остальных звеньев:

		//Предыдущее звено текущего списка
		TNode<T>* prevNewNode = newNode;

		//Звено "другого" списка
		TNode<T>* otherNode = other.pFirst->pNext;

		while (otherNode != nullptr)
		{
			newNode = new TNode<T>;
			newNode->value = otherNode->value;
			newNode->pNext = nullptr;

			prevNewNode->pNext = newNode;

			prevNewNode = newNode;
			otherNode = otherNode->pNext;
		}
	}
}