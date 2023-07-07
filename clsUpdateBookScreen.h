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

class clsUpdateBookScreen : protected clsScreen
{

private:

	static int _ReadIdNumber()
	{
		cout << "\n Enter Book ID? ";
		int ID = clsInputValidate::ReadNumberBetween<int>(1, INT_MAX, " Enter Book ID? ");

		return ID;
	}

	static clsBook::enCategorys _ReadCategory()
	{
		cout << "\n Books Categorys:\n";
		cout << "\n [1] Novel.";
		cout << "\n [2] Sciences.";
		cout << "\n [3] History.";
		cout << "\n [4] Religious.";
		cout << "\n [5] Others.\n";

		cout << " Category number: ";
		return (clsBook::enCategorys)clsInputValidate::ReadNumberBetween<short>(1, 5, " Category number: ");
	}

	static void _ReadBookData(clsBook &Book)
	{
		cout << "\n Update Book Info: \n";
		cout << " ___________________________________\n";

		cout << " Book Name      : ";
		Book.Name = clsInputValidate::ReadString();

		cout << " Author Name    : ";
		Book.Author = clsInputValidate::ReadString();

		Book.Category = _ReadCategory();

		cout << " Day Price      : ";
		Book.DayPrice = clsInputValidate::ReadNumberBetween<float>(.5, FLT_MAX, " Day Price  : ");
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
		cout << left << setw(43) << "             Update Book Screen" << "|\n";
		cout << left << setw(37) << " " << "==============================================\n";
	}

	static void _UpdateBook()
	{
		clsBook Book = clsBook::Find(_ReadIdNumber());

		if (Book.IsEmpty())
		{
			cout << "\n Book is not found.\n";
			return;
		}

		if (!Book.IsAvailable())
		{
			cout << "\n Book is rented you cannot update it.\n";
		}

		_PrintBook(Book);

		char Sure = 'N';

		cout << "\n Are you sure to update this book? Y/N? ";
		cin >> Sure;

		if (toupper(Sure) == 'Y')
		{
			_ReadBookData(Book);

			clsBook::enSaveResult Result = Book.Save();

			switch (Result)
			{

			case clsBook::enSaveResult::svSucceeded:
			{
				_PrintBook(Book);

				cout << "\n Book updated successfully.\n";
				break;
			}
			
			case clsBook::enSaveResult::svFaildIDnotExist:
			{
				cout << "\n Book update faild \"ID not exist in database\".\n";
				break;
			}

			case clsBook::enSaveResult::svFaildEmpty:
			{
				cout << "\n Book update faild \"object mode empty\".\n";
				break;
			}

			default:
			{
				cout << "\n Book update faild.\n";
				break;
			}

			}
		}

		else
		{
			cout << "\n Book update canceled.\n";
			return;
		}
	}

public:

	static void _ShowUpdateBookScreen()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pUpdateBook))
			return;

		char Sure = 'N';

		do
		{
			_PrintMenuHedar();

			_UpdateBook();

			cout << "\n Do you want to update more books? Y/N? ";
			cin >> Sure;

		} while (toupper(Sure) == 'Y');

	}

};

