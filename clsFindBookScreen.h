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

using namespace std;

class clsFindBookScreen : protected clsScreen
{

private:

	enum enSearchOption
	{
		eByID = 1,
		eByName = 2,
		eByAuthor = 3,
		eGoBack = 4,
	};

	static int _ReadIdNumber()
	{
		cout << "\n Enter Book ID number? ";

		return clsInputValidate::ReadNumber<int>(" Enter ID number? ");
	}

	static string _ReadString(string Message)
	{
		cout << Message;
		return clsInputValidate::ReadString();
	}

	static enSearchOption _ReadSearchOption()
	{
		cout << "\n Search options:";
		cout << "\n [1] By ID.";
		cout << "\n [2] By book name.";
		cout << "\n [3] By author name.";
		cout << "\n [4] Go back.\n";

		cout << "\n Enter option number? ";
		short Option = clsInputValidate::ReadNumberBetween<short>(1, 4, " Enter option number ? ");

		return (enSearchOption)Option;
	}

	static string _getStatusName(bool Status)
	{
		return (Status ? "Available" : "Rented");
	}

	static void _PrintBookLine(clsBook Book)
	{
		cout << " |" << left << setw(7) << Book.ID() << "|";
		cout << left << setw(38) << Book.Name << "|";
		cout << left << setw(35) << Book.Author << "|";
		cout << left << setw(9) << Book.getCategoryName() << "|";
		cout << left << fixed << setw(9) << setprecision(2) << Book.DayPrice << "|";
		cout << left << setw(9) << _getStatusName(Book.IsAvailable()) << "|";

		if (Book.IsAvailable())
			cout << left << setw(13) << " " << "|\n";
		else
			cout << left << setw(13) << Book.Renter.ReturnDate() << "|\n";
	}

	static void _PrintBooksList(vector<clsBook> vBooks)
	{
		if (vBooks.empty())
		{
			cout << "\n books is not found." << endl;
			return;
		}

		cout << " ______________________________________________________________________________________________________________________\n\n";
		cout << " |" << left << setw(7) << "ID";
		cout << "|" << left << setw(38) << "Name";
		cout << "|" << left << setw(25) << "Author";
		cout << "|" << left << setw(9) << "Category";
		cout << "|" << left << setw(9) << "Day Price";
		cout << "|" << left << setw(9) << "Status";
		cout << "|" << left << setw(13) << "Return Date" << "|\n";
		cout << " ______________________________________________________________________________________________________________________\n\n";

		if (vBooks.empty())
			cout << " |" << left << setw(116) << "There are no books in database." << "|\n";

		else
		{
			for (clsBook& Book : vBooks)
			{
				_PrintBookLine(Book);
			}
		}

		cout << " ______________________________________________________________________________________________________________________" << endl;
	}

	static void _PrintBooksList(clsBook Book)
	{
		if (Book.IsEmpty())
		{
			cout << "\n Book is not found." << endl;
			return;
		}

		cout << " ______________________________________________________________________________________________________________________\n\n";
		cout << " |" << left << setw(7) << "ID";
		cout << "|" << left << setw(30) << "Name";
		cout << "|" << left << setw(30) << "Author";
		cout << "|" << left << setw(10) << "Category";
		cout << "|" << left << setw(10) << "Day Price";
		cout << "|" << left << setw(10) << "Status";
		cout << "|" << left << setw(13) << "Return Date" << "|\n";
		cout << " ______________________________________________________________________________________________________________________\n\n";

		if (Book.IsEmpty())
			cout << " |" << left << setw(116) << "Book is not found." << "|\n";

		else
			_PrintBookLine(Book);

		cout << " ______________________________________________________________________________________________________________________" << endl;
	}

	static void _PrintMenuHedar()
	{
		cout << endl;

		cout << left << setw(37) << " " << "==============================================\n";
		cout << left << setw(37) << " " << "| ";
		cout << left << setw(43) << "            Find Books Screen" << "|\n";
		cout << left << setw(37) << " " << "==============================================\n";
	}

	static void _ShowFindBookScreen()
	{
		clsUtil::ResetScreen();

		_PrintMenuHedar();

		enSearchOption Option = _ReadSearchOption();

		vector<clsBook> vBooks;

		if (Option == enSearchOption::eByID)
		{
			clsBook Book = clsBook::Find(_ReadIdNumber());

			_PrintBooksList(Book);
		}

		else if (Option == enSearchOption::eByName)
		{
			vBooks = clsBook::Find(_ReadString("\n Enter book name? "));

			_PrintBooksList(vBooks);
		}

		else if (Option == enSearchOption::eByAuthor)
		{
			string AuthorName = _ReadString("\n Enter author name: ");

			vBooks = clsBook::FindByAuthor((AuthorName));

			_PrintBooksList(vBooks);
		}

		else
			return;
	}

public:

	static void ShowFindBookScreen()
	{
		if (!clsScreen::CheckAccessRights(clsUser::enPermissions::pFindBook))
			return;

		char FindAgain = 'N';

		do
		{
			_ShowFindBookScreen();

			cout << "\n Do you want to find more books? Enter Y/N? ";
			cin >> FindAgain;

		} while (toupper(FindAgain) == 'Y');

	}

};

