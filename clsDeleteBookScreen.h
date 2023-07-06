#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "clsBook.h"
#include "clsRenter.h"
#include "clsScreen.h"
#include "clsUtil.h"
#include "clsInputValidate.h"
#include "clsUser.h"
#include "clsRenter.h"
#include "clsDate.h"

using namespace std;

class clsDeleteBookScreen : protected clsScreen
{

private:

	static int _ReadIdNumber()
	{
		cout << "\n Enter book ID number? ";
		int ID = clsInputValidate::ReadNumberBetween<int>(1, INT_MAX, " Enter book ID? ");

		return ID;
	}

	static string _getStatusName(bool Status)
	{
		return (Status ? "Available" : "Rented");
	}

	static void _PrintBookLine(clsBook Book)
	{
		cout << " |" << left << setw(7) << Book.ID() << "|";
		cout << left << setw(38) << Book.Name << "|";
		cout << left << setw(25) << Book.Author << "|";
		cout << left << setw(9) << Book.getCategoryName() << "|";
		cout << left << fixed << setw(9) << setprecision(2) << Book.DayPrice << "|";
		cout << left << setw(9) << _getStatusName(Book.IsAvailable()) << "|";

		if (Book.IsAvailable())
			cout << left << setw(13) << " " << "|\n";
		else
			cout << left << setw(13) << Book.Renter.ReturnDate() << "|\n";
	}

	static void _PrintBook(clsBook Book)
	{
		cout << " ______________________________________________________________________________________________________________________\n\n";
		cout << " |" << left << setw(7) << "ID";
		cout << "|" << left << setw(38) << "Name";
		cout << "|" << left << setw(25) << "Author";
		cout << "|" << left << setw(9) << "Category";
		cout << "|" << left << setw(9) << "Day Price";
		cout << "|" << left << setw(9) << "Status";
		cout << "|" << left << setw(13) << "Return Date" << "|\n";
		cout << " ______________________________________________________________________________________________________________________\n\n";

		_PrintBookLine(Book);

		cout << " ______________________________________________________________________________________________________________________\n";
	}

	static void _PrintMenuHedar()
	{
		clsUtil::ResetScreen();

		cout << endl;

		cout << left << setw(37) << " " << "==============================================\n";
		cout << left << setw(37) << " " << "| ";
		cout << left << setw(43) << "             Delete Book Screen" << "|\n";
		cout << left << setw(37) << " " << "==============================================\n";
	}

	static void _DeleteBook()
	{
		clsBook Book = clsBook::Find(_ReadIdNumber());

		if (Book.IsEmpty())
		{
			cout << "\n Book is not found.\n";
			return;
		}

		if (!Book.IsAvailable())
		{
			cout << "\n Book is rented you cannot delete it.\n";
			return;
		}

		_PrintBook(Book);

		char Sure = 'N';

		cout << "\n Are you sure to delete this book? Y/N? ";
		cin >> Sure;

		if (toupper(Sure) == 'Y')
		{

			if (Book.Delete())
			{
				cout << "\n Book deleted successfully.\n";
			}

			else
			{
				cout << "\n Book delete faild.\n";
			}

		}

		else
		{
			cout << "\n Book delete canceled.\n";
			return;
		}

	}

public:

	static void ShowDeleteBookScreen()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pDeleteBook))
			return;

		char Sure = 'N';

		do
		{
			_PrintMenuHedar();

			_DeleteBook();

			cout << "\n Do you want to delete more books? Y/N? ";
			cin >> Sure;

		} while (toupper(Sure) == 'Y');

	}

};

