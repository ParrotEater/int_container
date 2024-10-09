#pragma once
#include <cassert>
#include <algorithm>
#include <exception>

using namespace std;

class bad_range : public exception
{
public:
	virtual const char* what() const noexcept override;
};
class bad_length : public exception
{
public:
	virtual const char* what() const noexcept override;	
};
class notFound : public exception
{
public:
	virtual const char* what() const noexcept override;	
};

class Container
{
	int m_length;
	int* m_data;
public:
	Container() = default;
	Container(int length);
	Container(const Container& a);
	Container& operator=(const Container& a);
	~Container();
	int& operator[](int index);
	void erase();
	int getLength() const;
	void reAllocate(int newLength);
	void resize(int newLength);
	void insertBefore(int value, int index);
	void insertInTheEnd(int value);
	void insertInTheBeginning(int value);
	void remove(int index);
	int Search(int target);
};