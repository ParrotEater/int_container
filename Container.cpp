#include <iostream>
#include <algorithm>
#include "Header.h"
#include <exception>

using namespace std;

int main()
{
    setlocale(LC_ALL, "RU");
	
	try
	{
		//Container c(-1); //перехвачено
		Container c(10); //нормалды, контейнер создан на 10 интовых элементов

		//cout << c[-1] << endl;
		//cout << c[10] << endl; //перехвачены
		for (int i{ 0 }; i < 10; i++) //заполняем контейнер числами 1-10
		{
			c[i] = i + 1;
		}
		//c.erase(); //вроде работает, иногда при очистке памяти улетало в ошибку (p.s. потому что деструктор чистил память повторно)
		//c.reAllocate(-1); //перехвачено

		//c.resize(-15); //не понятно почему программа падает и выдает ошибку(?) в delete_scalar 
		//по идее, все то же самое, как и в реаллокейте 
		//Разобрался, деструктор пытается второй раз удалить массив, в реаллокейте после удаления его аллоцировали заново, деструктор снес его и не пожаловался)
		//очищение памяти из деструктора убрал, сам буду пытаться чистить

		//c.resize(15); //работает. на всем, что дальше десятого - мусор

		//c.remove(-25); //перехвачено, как и слишком большое значение

		//c.insertBefore(20, -15); //перехвачено, как и слишком большое значение
		// 
		//c.insertBefore(99, 5); //работает

		//c.insertInTheEnd(16); //все работает
		//c.insertInTheBeginning(4); //все работает

		for (int i{ 0 }; i < c.getLength(); i++)
		{
			cout << c[i] << endl;
		}

		cout << "поиск по значению: элемент под индексом - " << c.Search(5); //можно и ввод от пользователя сделать и передать его как аргумент, надеюсь, это можно было опустить
	}
	catch (bad_alloc& ba )
	{
		cout << "bad_alloc caught!" << endl;
		cout << ba.what() << endl;
	}
	catch (bad_range& br)
	{
		cout << "bad_range caught!" << endl;
		cout << br.what() << endl;		
	}
	catch (bad_length& bl)
	{
		cout << "bad_length caught!" << endl;
		cout << bl.what() << endl;
	}
	catch (notFound& nf)
	{
		cout << nf.what() << endl;
	}
    return 0;
}