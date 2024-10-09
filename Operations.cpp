#include <iostream>
#include <algorithm>
#include "Header.h"
#include <exception>

Container::Container(int length) : m_length(length)
{
	m_data = new int[length];
}
Container::Container(const Container& a) : Container(a.getLength()) // ����������� �����������, �� ���� ��������, ����� ������������� ����� ���������
{
	copy_n(a.m_data, m_length, m_data); // ����������� ��������� �� ��������� � �����
}

Container& Container::operator=(const Container& a) //���������� ���������, ��� ������������� ��������� = � �������� ����� ����������� �����������
{
	if (&a == this) //�������� ������ �� ���� ��
		return *this;
	reAllocate(a.getLength()); //������� � �������� ������ ������ �������
	copy_n(a.m_data, m_length, m_data); //�������� ��� �� ��������� � �������������
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
		delete[] m_data;//����� ��������� ��� ������ � ����, ��� ����� ��������, ����� �������� ������������, ���� � ��� ��������� �������)
		throw bad_range();
	}
	return m_data[index];
}

void Container::erase() //�������� ���������
{
	delete[] m_data;
	m_data = nullptr;
	m_length = 0;
}

int Container::getLength() const
{
	return m_length;
}

void Container::reAllocate(int newLength) //������ ��������� �������, ��� ����������� ���������. �������� ������ ���� ���������
{
	//������ ������ ��������� � ��������� ����� � ����� ��������
	erase();

	if (newLength == 0) //���� ����� �������� = 0, �� ������ ������ �� �����
		return;
	if (newLength < 0) //������ ���������� ���� ����� ����� ������ ����
	{
		delete[] m_data;
		throw bad_length();
	}

	m_data = new int[newLength]; //������ ���������� ������ ��� ������ � ������ ��������
	m_length = newLength; //�������� ����� ���������� ����� ����� �����
}

void Container::resize(int newLength) //��������� ������� � ������������
{
	if (newLength == m_length) //������ �� ����������, ���� ������ � ����� ������� ���������
		return;
	if (newLength == 0) //������ ������ ����������
	{
		erase();
		return;
	}
	if (newLength < 0)
	{
		delete[] m_data;
		throw bad_length();
	}
	int* data = new int[newLength]; //��������� ������ ��� ������ ����� �����

	if (m_length > 0)
	{
		int elementsToCopy{ (newLength > m_length) ? m_length : newLength }; //���� ���������, ��������, ������� �� ������ � ����� - ������������, ������ ���� �� ������, ������ ������ ��������
		std::copy_n(m_data, elementsToCopy, data); // �������� ������, ������� ���������, ����
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

	int* data{ new int[m_length + 1] }; //�������� ������ ��� ����� ������ � �������� �� 1 ������, ��� �������

	std::copy_n(m_data, index, data); //�������� �������� �� ���������� ����� �� �������� � �����

	data[index] = value; //��������� �������� � ��������� ����� ������ �������

	std::copy_n(m_data + index, m_length - index, data + index + 1); //�������� �������� ����� ���������� ����� �� �������� � �����

	delete[] m_data; //������ �������� ���������
	m_data = data; //����� �����������
	++m_length;
}

void Container::insertInTheEnd(int value) //������� � ����� �������
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

	if (m_length == 1) //���� � ������� ��� ����� ���� ������� - �� ����������
	{
		erase();
		return;
	}

	int* data{ new int[m_length - 1] }; //���������� � ����������� �-�� � ������, ������ � ����������� ������� � �������������� ���������� �������

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
			throw notFound(); //����� �������� �������� �� �����������
		}

		if (m_data[i] == target)
		{
			delete[] m_data;
			return i;
		}
	}
}