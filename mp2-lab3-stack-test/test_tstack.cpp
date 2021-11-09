#include "pch.h"
#include "..\mp2-lab3-stack\TStack.h"
#include <iostream>

TEST(TStack, can_create_stack_with_positive_size)
{
	ASSERT_NO_THROW(TStack<int> s(100));
}

TEST(TStack, cant_create_stack_with_negative_size)
{
	ASSERT_ANY_THROW(TStack<int> s(-5));
}

TEST(TStack, cant_create_stack_with_zero_size)
{
	ASSERT_ANY_THROW(TStack<int> s(0));
}

TEST(TStack, can_create_copied_stack)
{
	TStack<int> s(5);
	ASSERT_NO_THROW(TStack<int> copy = s);
}

TEST(TStack, copied_stack_is_equal_to_source_one)
{
	int size = 5;
	TStack<int> s(size);
	for (int i = 0; i < size; i++)
	{
		s.Push(i + 1);
	}

	TStack<int> copy = s;

	EXPECT_EQ(copy, s);
}

TEST(TStack, copied_stack_has_its_own_memory) {
	int size = 5;
	TStack<int> s(size);
	for (int i = 0; i < size; i++)
	{
		s.Push(i + 1);
	}

	TStack<int> copy = s;

	copy.Clear();
	for (int i = 0; i < size; i++)
	{
		copy.Push(i + 2);
	}

	for (int i = 0; i < size; i++) {
		EXPECT_NE(s.Pop(), copy.Pop());
	}
		
}

TEST(TStack, can_assign_stacks_of_equal_size)
{
	int size = 5;

	TStack<int> s1(size);
	for (int i = 0; i < size; i++)
	{
		s1.Push(i + 1);
	}

	TStack<int> s2(size);
	for (int i = 0; i < size; i++)
	{
		s2.Push(i - 1);
	}

	s2 = s1;

	EXPECT_EQ(s2, s1);
}

TEST(TStack, can_assign_stacks_of_different_size)
{
	int size = 5;

	TStack<int> s1(size);
	for (int i = 0; i < size; i++)
	{
		s1.Push(i + 1);
	}

	TStack<int> s2(size + 10);
	for (int i = 0; i < size + 10; i++)
	{
		s2.Push(i - 1);
	}

	s2 = s1;

	EXPECT_EQ(s2, s1);
}

TEST(TStack, can_assign_stack_to_itself)
{
	TStack<int> s(10);
	for (int i = 0; i < 10; i++)
	{
		s.Push(i + 1);
	}

	s = s;

	EXPECT_EQ(s, s);
}

TEST(TStack, equal_stacks_comparison_returns_true)
{
	TStack<int> s1(10);
	for (int i = 0; i < 10; i++)
	{
		s1.Push(i + 1);
	}

	TStack<int> s2(10);
	for (int i = 0; i < 10; i++)
	{
		s2.Push(i + 1);
	}

	EXPECT_EQ(s1, s2);
}

TEST(TStack, unequal_stacks_comparison_returns_false)
{
	TStack<int> s1(10);
	for (int i = 0; i < 10; i++)
	{
		s1.Push(i + 1);
	}

	TStack<int> s2(10);
	for (int i = 0; i < 10; i++)
	{
		s2.Push(i + 2);
	}

	EXPECT_NE(s1, s2);
}

TEST(TStack, stacks_with_different_sizes_are_not_equal)
{
	TStack<int> s1(10);
	TStack<int> s2(20);

	EXPECT_NE(s1, s2);
}

TEST(TStack, empty_stack_isempty_true)
{
	TStack<int> s(100);
	ASSERT_TRUE(s.IsEmpty());
	ASSERT_TRUE(!s.IsNotEmpty());
}

TEST(TStack, not_empty_stack_isempty_false)
{
	TStack<int> s(100);
	s.Push(1);
	ASSERT_TRUE(s.IsNotEmpty());
	ASSERT_TRUE(!s.IsEmpty());
}

TEST(TStack, full_stack_isfull_true)
{
	TStack<int> s(10);
	for (int i = 0; i < 10; i++)
		s.Push(1);

	ASSERT_TRUE(s.IsFull());
	ASSERT_TRUE(!s.IsNotFull());
}

TEST(TStack, not_full_stack_isfull_false)
{
	TStack<int> s(10);

	ASSERT_TRUE(s.IsNotFull());
	ASSERT_TRUE(!s.IsFull());

	s.Push(1);

	ASSERT_TRUE(s.IsNotFull());
	ASSERT_TRUE(!s.IsFull());
}

TEST(TStack, can_push_and_pop_normally)
{
	TStack<int> s(5);
	int number = 1;
	int popped;

	ASSERT_NO_THROW(s.Push(number));
	ASSERT_NO_THROW(popped = s.Pop());
	EXPECT_EQ(popped, number);
}

TEST(TStack, cant_push_when_stack_is_full)
{
	int size = 5;
	TStack<int> s(size);
	for (int i = 0; i < size; i++)
	{
		s.Push(i + 1);
	}

	ASSERT_ANY_THROW(s.Push(120));
}

TEST(TStack, cant_pop_when_stack_is_empty)
{
	int size = 5;
	TStack<int> s(size);

	ASSERT_ANY_THROW(s.Pop());
}

TEST(TStack, can_give_top_normally)
{
	TStack<int> s(5);
	s.Push(10);
	EXPECT_EQ(s.Top(), 10);
}

TEST(TStack, cant_give_top_when_stack_is_empty)
{
	TStack<int> s(5);
	ASSERT_ANY_THROW(s.Top());
}

TEST(TStack, can_clear_stack)
{
	TStack<int> s(15);
	for (int i = 0; i < 10; i++)
		s.Push(1);

	ASSERT_NO_THROW(s.Clear());
}