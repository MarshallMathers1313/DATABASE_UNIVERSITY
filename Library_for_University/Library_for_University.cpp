#include "Header.h"

int main()
{
	/*int key, key2;
	list<Book> books;
	do
	{
		menu();
		cin >> key;
		switch (key)
		{
		case 1:
			firstMenu(books);
			break;
		case 2:
			if(books.size() != 0)
				outputBooks(books);
			break;
		case 3:
			searchMenu();
			cin >> key2;
			switch (key2)
			{
			case 1:
				searchName(books);
				break;
			case 2:
				searchGenre(books);
				break;
			case 3:
				searchAuthor(books);
				break;
			default:
				break;
			}
			break;
		case 4:
			
			break;
		case 5:
			deleteBook(books);
			break;
		default:
			break;
		}
	} while (key);*/

	string path = "DB\\library.db";

	createDB(path.c_str());
	createTable(path.c_str());
	insertData(path.c_str());
}