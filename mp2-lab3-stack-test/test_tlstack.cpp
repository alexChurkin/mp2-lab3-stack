#include "pch.h"
#include "..\stack-with-list\TLStack.h"
#include <iostream>

TEST(TLStack, can_create_stack)
{
	ASSERT_NO_THROW(TLStack<int> s);
}

TEST(TLStack, can_create_copied_stack)
{
	TLStack<int> s;
	ASSERT_NO_THROW(TLStack<int> copy = s);
}

TEST(TLStack, copied_stack_is_equal_to_source_one)
{
	TLStack<int> s;
	for (int i = 0; i < 5; i++)
		s.Push(i + 1);

	TLStack<int> copy = s;

	EXPECT_EQ(copy, s);
}

TEST(TLStack, copied_stack_has_its_own_memory) {
	TLStack<int> s;

	for (int i = 0; i < 5; i++)
		s.Push(i + 1);

	TLStack<int> copy = s;

	copy.Clear();
	for (int i = 0; i < 5; i++)
		copy.Push(i + 2);

	for (int i = 0; i < 5; i++)
		EXPECT_NE(s.Pop(), copy.Pop());
}

TEST(TLStack, can_assign_stacks)
{
	TLStack<int> s1;
	for (int i = 0; i < 5; i++)
	{
		s1.Push(i + 1);
	}

	TLStack<int> s2;
	for (int i = 0; i < 5 + 10; i++)
	{
		s2.Push(i - 1);
	}

	ASSERT_NO_THROW(s2 = s1);
	EXPECT_EQ(s2, s1);
}

TEST(TLStack, can_assign_stack_to_itself)
{
	TLStack<int> s;
	for (int i = 0; i < 10; i++)
		s.Push(i + 1);
	s = s;

	EXPECT_EQ(s, s);
}

TEST(TLStack, equal_stacks_comparison_returns_true)
{
	TLStack<int> s1;
	for (int i = 0; i < 10; i++)
	{
		s1.Push(i + 1);
	}

	TLStack<int> s2;
	for (int i = 0; i < 10; i++)
	{
		s2.Push(i + 1);
	}

	EXPECT_EQ(s1, s2);
}

TEST(TLStack, unequal_stacks_comparison_returns_false)
{
	TLStack<int> s1;
	for (int i = 0; i < 10; i++)
	{
		s1.Push(i + 1);
	}

	TLStack<int> s2;
	for (int i = 0; i < 10; i++)
	{
		s2.Push(i + 2);
	}

	EXPECT_NE(s1, s2);
}

TEST(TLStack, empty_stack_isempty_true)
{
	TLStack<int> s;
	ASSERT_TRUE(s.IsEmpty());
	ASSERT_TRUE(!s.IsNotEmpty());
}

TEST(TLStack, not_empty_stack_isempty_false)
{
	TLStack<int> s;
	s.Push(1);
	ASSERT_TRUE(s.IsNotEmpty());
	ASSERT_TRUE(!s.IsEmpty());
}

TEST(TLStack, can_push_and_pop_normally)
{
	TLStack<int> s;
	int number = 1;
	int popped;

	ASSERT_NO_THROW(s.Push(number));
	ASSERT_NO_THROW(popped = s.Pop());
	EXPECT_EQ(popped, number);
}

TEST(TLStack, cant_pop_when_stack_is_empty)
{
	TLStack<int> s;
	ASSERT_ANY_THROW(s.Pop());
}

TEST(TLStack, can_get_top_normally)
{
	TLStack<int> s;
	s.Push(10);
	EXPECT_EQ(s.Top(), 10);
}

TEST(TLStack, cant_get_top_when_stack_is_empty)
{
	TLStack<int> s;
	ASSERT_ANY_THROW(s.Top());
}

TEST(TLStack, can_clear_stack)
{
	TLStack<int> s;
	for (int i = 0; i < 10; i++)
		s.Push(1);

	ASSERT_NO_THROW(s.Clear());
}