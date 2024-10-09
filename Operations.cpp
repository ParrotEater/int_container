#include <iostream>
#include <algorithm>
#include "Header.h"
#include <exception>

Container::Container(int length) : m_length(length)
{
	m_data = new int[length];
}
Container::Container(const Container& a) : Container(a.getLength()) // конструктор копирования, на вход оригинал, копии присваивается длина оригинала
{
	copy_n(a.m_data, m_length, m_data); // копирование элементов из оригинала в копию
}

Container& Container::operator=(const Container& a) //перегрузка оператора, при использовании оператора = у объектов будет происходить копирование
{
	if (&a == this) //проверка ссылки на себя же
		return *this;
	reAllocate(a.getLength()); //создаем и выделяем память новому массиву
	copy_n(a.m_data, m_length, m_data); //копируем все из оригинала в новосозданный
	return *this;
}
Container::~Container()
{
	//delete[] m_data;
}

int& Container::operator[](int index)
{
	if (index > m_length - 1 || index < 0)
	{
		delete[] m_data;//когда контейнер уже создан в куче, его нужно очистить, потом кидаться исключениями, если я все правильно понимаю)
		throw bad_range();
	}
	return m_data[index];
}

void Container::erase() //вычищает контейнер
{
	delete[] m_data;
	m_data = nullptr;
	m_length = 0;
}

int Container::getLength() const
{
	return m_length;
}

void Container::reAllocate(int newLength) //просто изменение размера, без копирования элементов. значения должны быть мусорными
{
	//старый массив удаляется и создается новый с новым размером
	erase();

	if (newLength == 0) //если новое значение = 0, то ничего делать не нужно
		return;
	if (newLength < 0) //выброс исключения если новая длина меньше нуля
	{
		delete[] m_data;
		throw bad_length();
	}

	m_data = new int[newLength]; //заново выделяется память под массив с нужным размером
	m_length = newLength; //основная длина становится равна новой длине
}

void Container::resize(int newLength) //изменение размера с копированием
{
	if (newLength == m_length) //ничего не произойдет, если старый и новый размеры совпадают
		return;
	if (newLength == 0) //массив просто вычистится
	{
		erase();
		return;
	}
	if (newLength < 0)
	{
		delete[] m_data;
		throw bad_length();
	}
	int* data = new int[newLength]; //выделение памяти под массив новой длины

	if (m_length > 0)
	{
		int elementsToCopy{ (newLength > m_length) ? m_length : newLength }; //если уменьшаем, элементы, которые не влезли в новый - игнорируются, утечек быть не должно, старый массив удалится
		std::copy_n(m_data, elementsToCopy, data); // копируем откуда, сколько элементов, куда
		delete[] m_data;
		m_data = data;
		m_length = newLength;
	}
}

void Container::insertBefore(int value, int index)
{
	if (index < 0 || index > m_length - 1)
	{
		delete[] m_data;
		throw bad_range();
	}

	int* data{ new int[m_length + 1] }; //выделяем память под новый массив с размером на 1 больше, чем текущий

	std::copy_n(m_data, index, data); //копируем элементы ДО УКАЗАННОГО МЕСТА из текущего в новый

	data[index] = value; //вставляем значение в указанное место нового массива

	std::copy_n(m_data + index, m_length - index, data + index + 1); //копируем элементы ПОСЛЕ УКАЗАННОГО МЕСТА из текущего в новый

	delete[] m_data; //старые значения стираются
	m_data = data; //новые заполняются
	++m_length;
}

void Container::insertInTheEnd(int value) //вставка в конец массива
{
	int* data{ new int[m_length + 1] };
	copy_n(m_data, m_length, data);

	data[m_length] = value;

	delete[] m_data;
	m_data = data;
	++m_length;
}
void Container::insertInTheBeginning(int value)
{
	int* data{ new int[m_length + 1] };
	data[0] = value;
	copy_n(m_data, m_length, data + 1);

	delete[] m_data;
	m_data = data;
	++m_length;
}

void Container::remove(int index)
{
	if (index < 0 || index > m_length - 1)
	{
		delete[] m_data;
		throw bad_range();
	}

	if (m_length == 1) //если в массиве был всего один элемент - он зачистится
	{
		erase();
		return;
	}

	int* data{ new int[m_length - 1] }; //аналогично с добавлением э-та в массив, только с уменьшением размера и игнорированием указанного индекса

	std::copy_n(m_data, index, data);

	std::copy_n(m_data + index + 1, m_length - index - 1, data + index);

	delete[] m_data;
	m_data = data;
	--m_length;
}

int Container::Search(int target)
{
	for (int i{ 0 }; i < getLength() + 1; i++)
	{
		if (i == getLength())
		{
			delete[] m_data;
			throw notFound(); //поиск элемента работает на исключениях
		}

		if (m_data[i] == target)
		{
			delete[] m_data;
			return i;
		}
	}
}