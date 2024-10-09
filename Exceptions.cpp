#include "Header.h"
#include <iostream>
#include <exception>

const char* bad_range::what() const noexcept
{
	return "Выход за пределы массива";
}
const char* bad_length::what() const noexcept
{
	return "Новая длина массива - чушь";
}
const char* notFound::what() const noexcept
{
	return "Элемент не найден";
}