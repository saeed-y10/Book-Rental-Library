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

class clsFindRenterScreen : protected clsScreen
{

private:

	static void _PrintMenuHeder()
	{
		cout << endl;

		cout << left << setw(37) << " " << "==============================================\n";
		cout << left << setw(37) << " " << "| ";
		cout << left << setw(43) << "            Find Renter Screen" << "|\n";
		cout << left << setw(37) << " " << "==============================================\n";
	}

	static string _getStatusName(bool Status)
	{
		return (Status ? "Available" : "Rented");
	}

	static void _PrintBookDetails(clsBook Book)
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

	static void _PrintRenterDetails(clsBook Book)
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

	static void _FindRenter()
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

	}

	static void _ShowFindRenterScreen()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pManageRenters))
			return;

		char Answer = 'N';

		do
		{
			clsUtil::ResetScreen();
			
			_PrintMenuHeder();

			_FindRenter();

			cout << "\n Do you want to find more renters? Y/N? ";
			cin >> Answer;

		} while (toupper(Answer) == 'Y');
	
	}

public:

	static void ShowFindRenterScreen()
	{
		_ShowFindRenterScreen();
	}

};

