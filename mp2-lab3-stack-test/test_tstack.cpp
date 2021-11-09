#include "pch.h"
#include "..\mp2-lab3-stack\TStack.h"

TEST(TStack, can_create_stack_with_positive_size)
{
	ASSERT_NO_THROW(TStack<int> s(100));
}

TEST(TStack, cant_create_stack_with_not_positive_size)
{
	ASSERT_ANY_THROW(TStack<int> s(-5));
	ASSERT_ANY_THROW(TStack<int> s(0));
}

//не могу создать стек отрицательного размера
//не могу извлечь из пустого стека
//могу извлечь из стека (что те же самые элементы извлекаются)