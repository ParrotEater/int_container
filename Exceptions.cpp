#include "Header.h"
#include <iostream>
#include <exception>

const char* bad_range::what() const noexcept
{
	return "����� �� ������� �������";
}
const char* bad_length::what() const noexcept
{
	return "����� ����� ������� - ����";
}
const char* notFound::what() const noexcept
{
	return "������� �� ������";
}