#include "pch.h"
#include "..\mp2-lab3-stack\TCalculator.h"

TEST(TCalculator, can_create_calculator)
{
	ASSERT_NO_THROW(TCalculator c);
}

//can_set_and_get_expression (����� �������� ������ � �����. ���������� � ����� ��������� � �� ��)
//can_check_brackets (���������� ������ - true, ������������ - false)
//can_convert_to_postfix
//can_calculate (can_add, can_substract, can_multiply, can_divide, can_raise_to_the_power)
//can_calculate_complex_expression (very_complex_with_brackets) ...