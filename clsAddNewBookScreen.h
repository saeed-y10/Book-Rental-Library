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

class clsAddNewBookScreen : protected clsScreen
{

private:

	static int _ReadIdNumber()
	{
		cout << " ID Number: ";
		int ID = clsInputValidate::ReadNumberBetween<int>(1, INT_MAX, " ID Number: ");

		while (clsBook::IsIDNumberExist(ID))
		{
			cout << " Book with ID number [" << ID << "] is already exist enter another one: ";
			ID = clsInputValidate::ReadNumberBetween<int>(1, INT_MAX, " Book with ID number [" + to_string(ID) + "] is already exist enter another one: ");
		}

		return ID;
	}

	static clsBook::enCategorys _ReadCategory()
	{
		cout << "\n Books Categorys:";
		cout << "\n [1] Novel.";
		cout << "\n [2] Sciences.";
		cout << "\n [3] History.";
		cout << "\n [4] Religious.";
		cout << "\n [5] Others.\n";

		cout << "\n Category number: ";
		return (clsBook::enCategorys)clsInputValidate::ReadNumberBetween<short>(1, 5, " Category number: ");
	}

	static clsBook _ReadNewBook()
	{
		clsBook Book = clsBook::getNewBookObject(_ReadIdNumber());
		
		cout << "\n Book Name      : ";
		Book.Name = clsInputValidate::ReadString();

		cout << " Author Name    : ";
		Book.Author = clsInputValidate::ReadString();
		
		Book.Category = _ReadCategory();

		cout << " Day Price      : ";
		Book.DayPrice = clsInputValidate::ReadNumberBetween<float>(.5, FLT_MAX, " Day Price  : ");

		return Book;
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
		cout << left << fixed << setw(9) << setprecision(3) << Book.DayPrice << "|";
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
		cout << left << setw(43) << "           Add New Book Screen" << "|\n";
		cout << left << setw(37) << " " << "==============================================\n";
	}

	static void _AddNewBook()
	{
		clsBook Book = _ReadNewBook();

		_PrintBook(Book);

		char Sure = 'N';

		cout << "\n Are you sure you want to add this book? Y/N? ";
		cin >> Sure;

		if (toupper(Sure) == 'Y')
		{
			clsBook::enSaveResult Result = Book.Save();

			switch (Result)
			{

			case clsBook::enSaveResult::svSucceeded:
			{
				cout << " \n Book added successfully.\n";
				break;
			}

			case clsBook::enSaveResult::svFaildIDExist:
			{
				cout << " \n Book adding faild.\n";
				break;
			}

			default:
			{
				cout << " \n Book adding faild.\n";
				break;
			}

			}
		}

		else
		{
			cout << "\n Book adding canceled.\n";
		}

	}

public:

	static void ShowAddNewBookScreen()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pAddNewBook))
			return;

		char AddMore = 'N';

		do
		{
			_PrintMenuHedar();

			_AddNewBook();

			cout << "\n Do you want to add more books? Y/N? ";
			cin >> AddMore;

		} while (toupper(AddMore) == 'Y');

	}

};

