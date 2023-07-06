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

class clsListRentersScreen : protected clsScreen
{

private:

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

		cout << left << setw(35) << " " << "|" << left << setw(25) << "Book Name" << "|" << left << setw(25) << Book.Name << "|\n";
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

	static void _PrintRenterLine(clsBook Book)
	{
		cout << " |" << left << setw(7) << Book.ID() << "|";
		cout << left << setw(19) << Book.Renter.FirstName << "|";
		cout << left << setw(19) << Book.Renter.LastName << "|";
		cout << left << fixed << setw(9) << setprecision(2) << Book.DayPrice << "|";
		cout << left << setw(10) << Book.Renter.DelayDays() << "|";
		cout << left << fixed << setw(9) << setprecision(2) << Book.Renter.TotalPenalty() << "|";
		cout << left << fixed << setw(9) << setprecision(2) << Book.Renter.TotalBill() << "|";

		if (Book.IsAvailable())
		{
			cout << left << setw(13) << " " << "|";
			cout << left << setw(13) << " " << "|\n";
		}

		else
		{
			cout << left << setw(13) << Book.Renter.RentDate() << "|";
			cout << left << setw(13) << Book.Renter.ReturnDate() << "|\n";
		}

	}

	static void _PrintRentersList()
	{
		cout << " ______________________________________________________________________________________________________________________\n\n";
		cout << " |" << left << setw(7) << "Book ID";
		cout << "|" << left << setw(19) << "First Name";
		cout << "|" << left << setw(19) << "Last Name";
		cout << "|" << left << setw(9) << "Day Price";
		cout << "|" << left << setw(9) << "Delay Day"; 
		cout << "|" << left << setw(9) << "Penalty";
		cout << "|" << left << setw(9) << "Total Bill";
		cout << "|" << left << setw(13) << "Rent Date";
		cout << "|" << left << setw(13) << "Return Date" << "|\n";
		cout << " ______________________________________________________________________________________________________________________\n\n";

		vector<clsBook> vBooks = clsBook::getRentedBooksList();

		if (vBooks.empty())
			cout << " |" << left << setw(116) << " There are no renters in database." << "|\n";

		else
		{
			for (clsBook& Book : vBooks)
			{
				_PrintRenterLine(Book);
			}
		}

		cout << " ______________________________________________________________________________________________________________________" << endl;
	}

	static void _PrintHedar()
	{
		clsUtil::ResetScreen();

		cout << endl;

		cout << left << setw(37) << " " << "==============================================\n";
		cout << left << setw(37) << " " << "| ";
		cout << left << setw(42) << "             List Renters Menu" << " |\n";
		cout << left << setw(37) << " " << "==============================================\n";
	}

	static void _ShowListRentersScreen()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pManageRenters))
			return;

		_PrintHedar();

		_PrintRentersList();
	}

public:

	static void ShowListRentersScreen()
	{
		_ShowListRentersScreen();
	}

};

