#pragma once
#include <iostream>
#include <list>
#include <string>
#include "sqlite3.h"
using namespace std;
class Book
{
	string name, author, genre;
	int year;
	double width, height;
	string dateLibrary, dateOfReading;
	string review;

public:
	//Конструктор
	Book(string name = "\0", string author = "\0", string genre = "\0", int year = 0, double width = 0, double height = 0,
		string dateLibrary = "\0", string dateOfReading = "\0", string review = "\0")
		:name{ name }, author{ author }, genre{ genre }, year{ year }, width{ width }, height{ height }, dateLibrary{ dateLibrary },
		dateOfReading{ dateOfReading }, review{ review }
	{
		cout << "BOOK ADD COMPLATE!!!: " << this << endl;
	}

	//Деструктор
	~Book()
	{
	}

	void print()
	{
		cout << "INFORMATION ABOUT BOOK!!!\n";
		cout << "Name: " << name << endl;
		cout << "Author: " << author << endl;
		cout << "Genre: " << genre << endl;
		cout << "Year: " << year << endl << endl << endl;
	}
	friend void searchName(list<Book>& books);
	friend void searchAuthor(list<Book>& books);
	friend void searchGenre(list<Book>& books);
	friend void deleteBook(list<Book>& books);
};

void menu()
{
	cout << "1 - add book\n";
	cout << "2 - print book\n";
	cout << "3 - search book\n";
	cout << "4 - edit book\n";
	cout << "5 - delete book\n";
	cout << "0 - exit\n";
}

void searchMenu()
{
	cout << "\n\n\n1 - Search name\n";
	cout << "2 - Search genre\n";
	cout << "3 - Search author\n";
	cout << "0 - exit\n\n\n";
}

void searchName(list<Book>& books)
{
	cout << "Input book name: ";
	string name;
	cin.ignore(32765, '\n');
	getline(cin, name);
	int k = 0;
	list<Book>::iterator it = books.begin();
	while (it != books.end())
	{
		if (it->name == name)
		{
			k++;
			it->print();
		}
		it++;
	}
	if (k == 0)
	{
		cout << "We don't have this book!\n\n";
	}
}

void searchAuthor(list<Book>& books)
{
	cout << "Input book author: ";
	string author;
	cin.ignore(32765, '\n');
	getline(cin, author);
	int k = 0;
	list<Book>::iterator it = books.begin();
	while (it != books.end())
	{
		if (it->author == author)
		{
			k++;
			it->print();
		}
		it++;
	}
	if (k == 0)
	{
		cout << "We don't have this book!\n\n";
	}
}

void searchGenre(list<Book>& books)
{
	cout << "Input book genre: ";
	string genre;
	cin.ignore(32765, '\n');
	getline(cin, genre);
	int k = 0;
	list<Book>::iterator it = books.begin();
	while (it != books.end())
		if (it->genre == genre)
		{
			{
				k++;
				it->print();
			}
			it++;
		}
	if (k == 0)
	{
		cout << "We don't have this book!\n\n";
	}
}

void firstMenu(list<Book>& books)
{
	cout << "Input book name: ";
	string name;
	cin.ignore(32765, '\n');
	getline(cin, name);

	cout << "Input book author: ";
	string author;
	getline(cin, author);

	cout << "Input book genre: ";
	string genre;
	getline(cin, genre);

	cout << "Input book year: ";
	int year;
	cin >> year;

	Book book(name, author, genre, year);

	books.push_back(book);
}

void outputBooks(list<Book>& books)
{
	list<Book>::iterator it = books.begin();
	while (it != books.end())
	{
		it->print();
		it++;
	}
}

void deleteBook(list<Book>& books)
{
	string name;
	cin.ignore(32765, '\n');
	cout << "Input book name: ";
	getline(cin, name);

	int k = 0;
	list<Book>::iterator it = books.begin();
	while (it != books.end())
	{
		if (it->name == name)
		{
			k++;
			cout << "Delete book!\n";
			books.erase(it);
			break;
		}
		it++;
	}
	if (k == 0)
	{
		cout << "We don't have this book!\n\n";
	}
}


/*DATABASE*/
int callback(void* NotUsed, int argc, char** argv, char** azColName)
{
	for (int i = 0; i < argc; i++) {
		// column name and value
		cout << azColName[i] << ": " << argv[i] << endl;
	}

	cout << endl;

	return 0;
}

int createDB(const char* s)
{
	sqlite3* DB;

	int exit = 0;
	exit = sqlite3_open(s, &DB);

	if (exit == 0)
		cout << "DB created Succesfully!\n";

	else
		cerr << "DB doesn't creat!\n";

	sqlite3_close(DB);

	return 0;
}

int createTable(const char* s)
{
	sqlite3* DB;
	char* messageError;

	string sql = "CREATE TABLE IF NOT EXISTS GRADES("
		"ID INTEGER PRIMARY KEY AUTOINCREMENT, "
		"NAME      TEXT NOT NULL, "
		"LNAME     TEXT NOT NULL, "
		"AGE       INT  NOT NULL, "
		"ADDRESS   CHAR(50), "
		"GRADE     CHAR(1) );";

	try
	{
		int exit = 0;
		exit = sqlite3_open(s, &DB);
		/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
		exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
		if (exit != SQLITE_OK) {
			cerr << "Error in createTable function." << endl;
			sqlite3_free(messageError);
		}
		else
			cout << "Table created Successfully" << endl;
		sqlite3_close(DB);
	}
	catch (const exception& e)
	{
		cerr << e.what();
	}

	return 0;
}

int insertData(const char* s)
{
	sqlite3* DB;
	char* messageError;

	string sql("INSERT INTO GRADES (NAME, LNAME, AGE, ADDRESS, GRADE) VALUES('Alice', 'Chapa', 35, 'Tampa', 'A');"
		"INSERT INTO GRADES (NAME, LNAME, AGE, ADDRESS, GRADE) VALUES('Bob', 'Lee', 20, 'Dallas', 'B');"
		"INSERT INTO GRADES (NAME, LNAME, AGE, ADDRESS, GRADE) VALUES('Fred', 'Cooper', 24, 'New York', 'C');");

	int exit = sqlite3_open(s, &DB);
	/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK) {
		cerr << "Error in insertData function." << endl;
		sqlite3_free(messageError);
	}
	else
		cout << "Records inserted Successfully!" << endl;

	return 0;
}

int updateData(const char* s)
{
	sqlite3* DB;
	char* messageError;

	string sql("UPDATE GRADES SET GRADE = 'A' WHERE LNAME = 'Cooper'");

	int exit = sqlite3_open(s, &DB);
	/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK) {
		cerr << "Error in updateData function." << endl;
		sqlite3_free(messageError);
	}
	else
		cout << "Records updated Successfully!" << endl;

	return 0;
}

int selectData(const char* s)
{
	sqlite3* DB;
	char* messageError;

	string sql = "SELECT * FROM GRADES;";

	int exit = sqlite3_open(s, &DB);
	/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here*/
	exit = sqlite3_exec(DB, sql.c_str(), callback, NULL, &messageError);

	if (exit != SQLITE_OK) {
		cerr << "Error in selectData function." << endl;
		sqlite3_free(messageError);
	}
	else
		cout << "Records selected Successfully!" << endl;

	return 0;
}

int deleteData(const char* s)
{
	sqlite3* DB;
	char* messageError;

	string sql = "DELETE FROM GRADES;";

	int exit = sqlite3_open(s, &DB);
	/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
	exit = sqlite3_exec(DB, sql.c_str(), callback, NULL, &messageError);
	if (exit != SQLITE_OK) {
		cerr << "Error in deleteData function." << endl;
		sqlite3_free(messageError);
	}
	else
		cout << "Records deleted Successfully!" << endl;

	return 0;
}