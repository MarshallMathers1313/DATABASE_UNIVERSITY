#include "Library.h"


const char* path = "DB/library.db";
string searchWord;

//Создание файла для БД
int createDB(const char* path)
{
	sqlite3* DB;
	int exit = 0;//Переменная для проверки БД
	exit = sqlite3_open(path, &DB);
	if (exit == 0)
	{
		cout << "--------------------------------------------------------------------------\n";
		cout << "                        SUCCESFULLY! CREATED DATABASE                     \n";
		cout << "--------------------------------------------------------------------------\n";
	}
	else
	{
		cout << "--------------------------------------------------------------------------\n";
		cout << "                        ERROR! DOES NOT CREAT DATABASE                    \n";
		cout << "--------------------------------------------------------------------------\n";
	}

	sqlite3_close(DB);

	return 0;
}

//Создание таблицы БД
int createTable(const char* path)
{
	sqlite3* DB;
	char* messageError;
	
	string sql = "CREATE TABLE IF NOT EXISTS GRADES("
		"ID INTEGER PRIMARY KEY AUTOINCREMENT, "
		"NAME      TEXT NOT NULL, "
		"AUTHOR     TEXT NOT NULL, "
		"GENRE       TEXT  NOT NULL, "
		"YEAR   INT NOT NULL);";

	try
	{
		int exit = 0;
		exit = sqlite3_open(path, &DB);
		
		exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);

		if (exit != SQLITE_OK)
		{
			cout << "--------------------------------------------------------------------------\n";
			cout << "                        ERROR! DOES NOT CREAT TABLE IN DATABASE           \n";
			cout << "--------------------------------------------------------------------------\n";
			sqlite3_free(messageError);
		}
		else
		{
			cout << "--------------------------------------------------------------------------\n";
			cout << "                        SUCCESFULLY! CREATED TABLE IN DATABASE            \n";
			cout << "--------------------------------------------------------------------------\n";
			sqlite3_close(DB);
		}
	}
	catch (const exception& e)
	{
		cerr << e.what();
	}
	return 0;
}

//Добавление информации в БД
int insertData(const char* path, string name, string author, string genre, int year)
{
	sqlite3* DB;
	char* messageError;

	string sql = "INSERT INTO GRADES (NAME, AUTHOR, GENRE, YEAR) VALUES(";
	sql = sql + "\'" + name + "\', '" + author + "\', '" + genre + "\'," + to_string(year) + ");";

	int exit = sqlite3_open(path, &DB);

	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);

	try
	{
		if (exit != SQLITE_OK)
		{
			cout << "--------------------------------------------------------------------------\n";
			cout << "                        ERROR! INSERT DATA IN DATABASE                    \n";
			cout << "--------------------------------------------------------------------------\n";
			sqlite3_free(messageError);
		}
		else
		{
			cout << "--------------------------------------------------------------------------\n";
			cout << "                        SUCCESFULLY! RECORDS INSERTED IN DATABASE         \n";
			cout << "--------------------------------------------------------------------------\n";
			sqlite3_close(DB);
		}
	}
	catch (const exception& e)
	{
		cerr << e.what();
	}

	return 0;
}

int callback(void* NotUsed, int argc, char** argv, char** azColName)
{
	cout << "--------------------------------------------------------------------------\n";
	cout << "                        ||ALL LIBRARY BOOKS||                             \n";
	cout << "--------------------------------------------------------------------------\n";

	cout << "--------------------------------------------------------------------------\n";
	cout << "                        BOOK INFORAMATION...                              \n";

	for (int i = 0; i < argc; i++) {
		// column name and value
		cout <<"||->" << azColName[i] << ": " << argv[i] << endl;
	}

	cout << "--------------------------------------------------------------------------\n\n";

	return 0;
}

int callback_search_name(void* NotUsed, int argc, char** argv, char** azColName)
{
	cout << "--------------------------------------------------------------------------\n";
	cout << "                        ||SEARCHING BY NAME||                             \n";
	cout << "--------------------------------------------------------------------------\n";

	cout << "--------------------------------------------------------------------------\n";
	cout << "                        BOOK INFORAMATION...                              \n";
	if (searchWord == argv[1])
	{
		for (int i = 0; i < argc; i++) {
			// column name and value
			cout << "||->" << azColName[i] << ": " << argv[i] << endl;
		}
	}

	cout << "--------------------------------------------------------------------------\n\n";

	return 0;
}

int callback_search_author(void* NotUsed, int argc, char** argv, char** azColName)
{
	cout << "--------------------------------------------------------------------------\n";
	cout << "                        ||SEARCHING BY AUTHOR||                           \n";
	cout << "--------------------------------------------------------------------------\n";

	cout << "--------------------------------------------------------------------------\n";
	cout << "                        BOOK INFORAMATION...                              \n";
	if (searchWord == argv[2])
	{
		for (int i = 0; i < argc; i++) {
			// column name and value
			cout << azColName[i] << ": " << argv[i] << endl;
		}
	}
	cout << "--------------------------------------------------------------------------\n\n";

	return 0;
}

int callback_search_genre(void* NotUsed, int argc, char** argv, char** azColName)
{
	cout << "--------------------------------------------------------------------------\n";
	cout << "                        ||SEARCHING BY GENRE||                            \n";
	cout << "--------------------------------------------------------------------------\n";

	cout << "--------------------------------------------------------------------------\n";
	cout << "                        BOOK INFORAMATION...                              \n";
	if (searchWord == argv[3])
	{
		for (int i = 0; i < argc; i++) {
			// column name and value
			cout << azColName[i] << ": " << argv[i] << endl;
		}
	}

	cout << "--------------------------------------------------------------------------\n\n";

	return 0;
}

//Вывод данных
void print()
{
	sqlite3* DB;
	char* messageError;

	string sql = "SELECT * FROM GRADES;";
	
	int exit = sqlite3_open(path, &DB);

	exit = sqlite3_exec(DB, sql.c_str(), callback, NULL, &messageError);

	try
	{
		if (exit != SQLITE_OK)
		{
			cout << "--------------------------------------------------------------------------\n";
			cout << "                        ERROR! SELECT DATA IN DATABASE                    \n";
			cout << "--------------------------------------------------------------------------\n";
			sqlite3_free(messageError);
		}
		else
		{
			cout << "--------------------------------------------------------------------------\n";
			cout << "                        SUCCESFULLY! SELECT INSERTED IN DATABASE          \n";
			cout << "--------------------------------------------------------------------------\n";
			sqlite3_close(DB);
		}
	}
	catch (const exception& e)
	{
		cerr << e.what();
	}
}

//Поиск по имени
void search_name(const char* path)
{
	sqlite3* DB;
	char* messageError;

	cout << "INPUT BOOK'S NAME: ";
	cin.ignore(32765, '\n');
	getline(cin, searchWord);

	string sql = "SELECT * FROM GRADES;";

	int exit = sqlite3_open(path, &DB);

	exit = sqlite3_exec(DB, sql.c_str(), callback_search_name, NULL, &messageError);
}

//Поиск по автору
void search_author(const char* path)
{
	sqlite3* DB;
	char* messageError;

	cout << "INPUT BOOK'S AUTHOR: ";
	cin.ignore(32765, '\n');
	getline(cin, searchWord);

	string sql = "SELECT * FROM GRADES;";

	int exit = sqlite3_open(path, &DB);

	exit = sqlite3_exec(DB, sql.c_str(), callback_search_author, NULL, &messageError);
}

//Поиск по ганру
void search_genre(const char* path)
{
	sqlite3* DB;
	char* messageError;

	cout << "INPUT BOOK'S GENRE: ";
	cin.ignore(32765, '\n');
	getline(cin, searchWord);

	string sql = "SELECT * FROM GRADES;";

	int exit = sqlite3_open(path, &DB);

	exit = sqlite3_exec(DB, sql.c_str(), callback_search_genre, NULL, &messageError);
}

//Удаление книги
void delete_book(const char* path, int choice)
{
	sqlite3* DB;
	char* messageError;
	string sql = "DELETE FROM GRADES WHERE ID='" + to_string(choice) + "';";
	int exit = sqlite3_open(path, &DB);

	exit = sqlite3_exec(DB, sql.c_str(), callback, NULL, &messageError);

	cout << "--------------------------------------------------------------------------\n";
	cout << "                        DELETING BOOK...                                  \n";
}

void Book::info()const
{
	cout << "--------------------------------------------------------------------------\n";
	cout << "                        INFORMATION ABOUT BOOK!                           \n";
	cout << "||->Name: " << name << "\n";
	cout << "||->Author: " << author << "\n";
	cout << "||->Genre: " << genre << "\n";
	cout << "||->Year: " << year << "\n";
	cout << "--------------------------------------------------------------------------\n";
}

//Меню для поиска
void searchMenu()
{
	int choice;
	do
	{
		cout << "--------------------------------------------------------------------------\n";
		cout << "                        WELCOME TO SEARCH MENU                            \n";
		cout << "1 - search by name\n";
		cout << "2 - search by author\n";
		cout << "3 - search by genre\n";
		cout << "0 - previous menu\n";
		cout << "--------------------------------------------------------------------------\n";
		cout << "INPUT YOUR CHOICE: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			search_name(path);
			break;
		case 2:
			search_author(path);
			break;
		case 3:
			search_genre(path);
			break;
		default:
			break;
		}
	} while (choice != 0);
}

//Меню
void menu()
{
	list<Book> books;
	list<Book>::const_iterator it;
	createDB(path);
	createTable(path);
	int choice = 0;
	int choice2 = 0;
	do
	{
		cout << "--------------------------------------------------------------------------\n";
		cout << "                        WELCOME TO LIBRARY                                \n";
		cout << "1 - add book\n";
		cout << "2 - print book\n";
		cout << "3 - search book\n";
		cout << "4 - delete book\n";
		cout << "0 - exit\n";
		cout << "--------------------------------------------------------------------------\n";
		cout << "INPUT YOUR CHOICE: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			add(books);
			break;
		case 2:
			print();
			break;
		case 3:
			searchMenu();
			break;
		case 4:
			print();
			cout << "--------------------------------------------------------------------------\n";
			cout << "                        ||DELETE BOOK||                                   \n";
			cout << "--------------------------------------------------------------------------\n";
			cout << "INPUT YOUR CHOICE (INPUT ID BOOK): ";
			cin >> choice2;
			delete_book(path, choice2);
			break;
		case 0:
			cout << "--------------------------------------------------------------------------\n";
			cout << "                        GOODBYE! SEE YOU SOON...                          \n";
			cout << "--------------------------------------------------------------------------\n";
			break;
		default:
			cout << "--------------------------------------------------------------------------\n";
			cout << "                        Input correct operation                           \n";
			cout << "--------------------------------------------------------------------------\n";
			break;
		}
	} while (choice != 0);
}

//Добавление книги
void add(list<Book>& books)

{
	cout << "--------------------------------------------------------------------------\n";
	cout << "                        WELCOME TO ADD BOOK!                              \n";
	cout << "||->Input Book's Name: ";
	string name;
	cin.ignore(32765, '\n');
	getline(cin, name);
	cout << "--------------------------------------------------------------------------\n";
	cout << "||->Input Book's Author: ";
	string author;
	getline(cin, author);
	cout << "--------------------------------------------------------------------------\n";
	cout << "||->Input Book's Genre: ";
	string genre;
	getline(cin, genre);
	cout << "--------------------------------------------------------------------------\n";
	cout << "||->Input Book's Year: ";
	int year;
	cin >> year;
	cout << "--------------------------------------------------------------------------\n";
	//Добавление книги
	books.push_back(Book(name, author, genre, year));
	//Добавление в БД
	insertData(path, name, author, genre, year);
}