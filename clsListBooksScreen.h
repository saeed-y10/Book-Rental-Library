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

class clsListBooksScreen : protected clsScreen
{

private:

	enum enPrintCategory;

	static string _getStatusName(bool Status)
	{
		return (Status ? "Available" : "Rented");
	}

	static void _PrintBookLine(clsBook Book)
	{
		cout << " |" << left << setw(7) << Book.ID() << "|";
		cout << left << setw(30) << Book.Name << "|";
		cout << left << setw(30) << Book.Author << "|";
		cout << left << setw(10) << Book.getCategoryName() << "|";
		cout << left << fixed << setw(10) << setprecision(2) << Book.DayPrice << "|";
		cout << left << setw(10) << _getStatusName(Book.IsAvailable()) << "|";
		
		if (Book.IsAvailable())
			cout << left << setw(13) << " " << "|\n";
		else
			cout << left << setw(13) << Book.Renter.ReturnDate() << "|\n";
	}

	static void _PrintMenuHeder()
	{
		cout << endl;

		cout << left << setw(37) << " " << "==============================================\n";
		cout << left << setw(37) << " " << "| ";
		cout << left << setw(43) << "            List Books Screen" << "|\n";
		cout << left << setw(37) << " " << "==============================================\n";
	}

	static void _PrintBooksList(vector<clsBook> vBooks)
	{
		cout << " ______________________________________________________________________________________________________________________\n\n";
		cout << " |" << left << setw(7) << "ID";
		cout << "|" << left << setw(30) << "Name";
		cout << "|" << left << setw(30) << "Author";
		cout << "|" << left << setw(10) << "Category";
		cout << "|" << left << setw(10) << "Day Price";
		cout << "|" << left << setw(10) << "Status";
		cout << "|" << left << setw(13) << "Return Date" << "|\n";
		cout << " ______________________________________________________________________________________________________________________\n\n";

		if (vBooks.empty())
			cout << " |" << left << setw(116) << "There are no books in database." << "|\n";

		else
		{
			for (clsBook &Book : vBooks)
			{
				_PrintBookLine(Book);
			}
		}

		cout << " ______________________________________________________________________________________________________________________" << endl;
	}

	static short _ReadPrintOption()
	{
		cout << "\n\n books categorys:";
		cout << "\n [1] All.";
		cout << "\n [2] Novel.";
		cout << "\n [3] Sciences.";
		cout << "\n [4] History.";
		cout << "\n [5] Religious.";
		cout << "\n [6] Others.\n";

		cout << "\n Enter category number? ";
		short Option = clsInputValidate::ReadNumberBetween<short>(1, 6, " Enter category number ? ");

		return Option - 1;
	}

public:

	static void ShowListBooksScreen()
	{
		if (!clsScreen::CheckAccessRights(clsUser::enPermissions::pListBooks))
			return;

		clsUtil::ResetScreen();
		_PrintMenuHeder();

		short PrintOption = _ReadPrintOption();
		vector<clsBook> vBooks;

		if (PrintOption == 0)
			vBooks = clsBook::getBooksList();

		else
			vBooks = clsBook::getBooksList((clsBook::enCategorys)PrintOption);

		_PrintBooksList(vBooks);
	}

};

