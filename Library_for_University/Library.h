#pragma once
#include <iostream>//базовая библиотека для работы ввод и вывод и т.д
#include <list>//для двусвязанного списка
#include <string>//для работы стороками
#include "sqlite3.h"//для работы sqlite
using namespace std;//чтобы каждый раз не писать std::cout, чтобы просто писать cout

//Класс "Книга"
class Book
{
	//Переменные для хранения имя, автор, жанр, год книги
	string name, author, genre;
	int year;

public:
	//Конструктор
	Book(string name = "\0", string author = "\0", string genre = "\0", int year = 0)
		:name{ name }, author{ author }, genre{ genre }, year{ year }
	{
		cout << "\nSuccesfully! BOOK ADDED\n";
	}
	//Деструктор
	~Book()
	{
	}
	//Вывод информации о книге
	void info()const;

};

//Меню
void menu();

//Добавление книги
void add(list<Book>& books);