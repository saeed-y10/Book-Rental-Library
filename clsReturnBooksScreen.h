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

class clsReturnBooksScreen : protected clsScreen
{

private:

	static void _PrintMenuHeder()
	{
		cout << endl;

		cout << left << setw(37) << " " << "==============================================\n";
		cout << left << setw(37) << " " << "| ";
		cout << left << setw(43) << "           Return Books Screen" << "|\n";
		cout << left << setw(37) << " " << "==============================================\n";
	}

	static void _PrintBookDetails(clsBook &Book)
	{
		cout << endl;

		cout << left << setw(35) << " " << "-----------------------------------------------------\n";
		cout << left << setw(35) << " " << "|" << left << setw(51) << "                    Book Name" << "|\n";
		cout << left << setw(35) << " " << "-----------------------------------------------------\n";

		cout << left << setw(35) << " " << "|" << left << setw(51) << Book.Name << "|\n";
		cout << left << setw(35) << " " << "-----------------------------------------------------\n";

		cout << left << setw(35) << " " << "|" << left << setw(25) << "Book ID" << "|" << left << setw(25) << Book.ID() << "|\n";
		cout << left << setw(35) << " " << "-----------------------------------------------------\n";

		cout << left << setw(35) << " " << "|" << left << setw(25) << "Day Price" << "|" << left << fixed << setw(25) << setprecision(2) << Book.Renter.DayPrice << "|\n";
		cout << left << setw(35) << " " << "-----------------------------------------------------\n";

		cout << left << setw(35) << " " << "|" << left << setw(25) << "Rent Days" << "|" << left << setw(25) << Book.Renter.RentDays << "|\n";
		cout << left << setw(35) << " " << "-----------------------------------------------------\n";

		cout << left << setw(35) << " " << "|" << left << setw(25) << "Rent Date" << "|" << left << setw(25) << Book.Renter.RentDate() << "|\n";
		cout << left << setw(35) << " " << "-----------------------------------------------------\n";

		cout << left << setw(35) << " " << "|" << left << setw(25) << "Return Date" << "|" << left << setw(25) << Book.Renter.ReturnDate() << "|\n";
		cout << left << setw(35) << " " << "-----------------------------------------------------\n";

		cout << left << setw(35) << " " << "|" << left << setw(25) << "Day Penalty" << "|" << left << fixed << setw(25) << setprecision(2) << Book.Renter.PenaltyPerDay() << "|\n";
		cout << left << setw(35) << " " << "-----------------------------------------------------\n";

		cout << left << setw(35) << " " << "|" << left << setw(25) << "Delay Days" << "|" << left << setw(25) << Book.Renter.DelayDays() << "|\n";
		cout << left << setw(35) << " " << "-----------------------------------------------------\n";

		cout << left << setw(35) << " " << "|" << left << setw(25) << "Total Penalty" << "|" << left << fixed << setw(25) << setprecision(2) << Book.Renter.TotalPenalty() << "|\n";
		cout << left << setw(35) << " " << "-----------------------------------------------------\n";

		cout << left << setw(35) << " " << "|" << left << setw(25) << "Total Bill" << "|" << left << fixed << setw(25) << setprecision(2) << Book.Renter.TotalBill() << "|\n";
		cout << left << setw(35) << " " << "-----------------------------------------------------" << endl;
	}

	static void _PrintRenterDetails(clsBook &Book)
	{
		cout << endl;

		cout << left << setw(35) << " " << "-----------------------------------------------------\n";
		cout << left << setw(35) << " " << "|" << left << setw(51) << "                  Renter Details" << "|\n";
		cout << left << setw(35) << " " << "-----------------------------------------------------\n";

		cout << left << setw(35) << " " << "|" << left << setw(25) << "First Name" << "|" << left << setw(25) << Book.Renter.FirstName << "|\n";
		cout << left << setw(35) << " " << "-----------------------------------------------------\n";

		cout << left << setw(35) << " " << "|" << left << setw(25) << "Last Name" << "|" << left << setw(25) << Book.Renter.LastName << "|\n";
		cout << left << setw(35) << " " << "-----------------------------------------------------\n";

		cout << left << setw(35) << " " << "|" << left << setw(25) << "Email" << "|" << left << setw(25) << Book.Renter.Email << "|\n";
		cout << left << setw(35) << " " << "-----------------------------------------------------\n";

		cout << left << setw(35) << " " << "|" << left << setw(25) << "Phone" << "|" << left << setw(25) << Book.Renter.Phone << "|\n";
		cout << left << setw(35) << " " << "-----------------------------------------------------\n";
	}


	static void _ReturnBooks()
	{
		cout << "\n\n Read Renter Info:\n";
		cout << "\n Enter First Name: ";
		string FirstName = clsInputValidate::ReadString();

		cout << " Enter Last Name : ";
		string LastName = clsInputValidate::ReadString();

		vector<clsBook> vBooks = clsBook::getBooksList(FirstName, LastName);

		if (vBooks.empty())
		{
			cout << "\n Renter is not found.\n";
			return;
		}

		_PrintRenterDetails(vBooks[0]);

		for (clsBook& Book : vBooks)
		{
			_PrintBookDetails(Book);
		}

		cout << "\n " << vBooks.size() << " Books(s).\n";

		char Answer = 'N';

		cout << "\n Are you sure to return these books? Y/N? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			short Counter = 1;
			
			cout << endl;

			for (clsBook &Book : vBooks)
			{
				
				if (Book.ReturnBook())
				{
					cout << " Book " << Counter << " returned successfully.\n";
				}

				else
				{
					cout << " Book " << Counter << " return faild.\n ";
				}

				Counter++;
			}

		}

		else
		{
			cout << "\n Books return canceled.\n";
		}

	}

	static void _ShowReturnBooksScreen()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pManageRenters))
			return;

		char Answer = 'N';

		do
		{
			clsUtil::ResetScreen();

			_PrintMenuHeder();

			_ReturnBooks();

			cout << "\n Do you want to return more books? Y/N? ";
			cin >> Answer;

		} while (toupper(Answer) == 'Y');

	}

public:

	static void ShowReturnBooksScreen()
	{
		_ShowReturnBooksScreen();
	}

};

