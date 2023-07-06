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

class clsReturnBookScreen : protected clsScreen
{

private:

	static int _ReadIdNumber()
	{
		cout << "\n Enter Book ID number? ";

		return clsInputValidate::ReadNumber<int>(" Enter ID number? ");
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

	static void _PrintRenterDetails(clsRenter Renter)
	{
		cout << endl;

		cout << left << setw(35) << " " << "-----------------------------------------------------\n";
		cout << left << setw(35) << " " << "|" << left << setw(51) << "                  Renter Details" << "|\n";
		cout << left << setw(35) << " " << "-----------------------------------------------------\n";

		cout << left << setw(35) << " " << "|" << left << setw(25) << "First Name" << "|" << left << setw(25) << Renter.FirstName << "|\n";
		cout << left << setw(35) << " " << "-----------------------------------------------------\n";

		cout << left << setw(35) << " " << "|" << left << setw(25) << "Last Name" << "|" << left << setw(25) << Renter.LastName << "|\n";
		cout << left << setw(35) << " " << "-----------------------------------------------------\n";

		cout << left << setw(35) << " " << "|" << left << setw(25) << "Email" << "|" << left << setw(25) << Renter.Email << "|\n";
		cout << left << setw(35) << " " << "-----------------------------------------------------\n";

		cout << left << setw(35) << " " << "|" << left << setw(25) << "Phone" << "|" << left << setw(25) << Renter.Phone << "|\n";
		cout << left << setw(35) << " " << "-----------------------------------------------------\n";

		cout << left << setw(35) << " " << "|" << left << setw(25) << "Day Price" << "|" << left << fixed << setw(25) << setprecision(2) << Renter.DayPrice << "|\n";
		cout << left << setw(35) << " " << "-----------------------------------------------------\n";

		cout << left << setw(35) << " " << "|" << left << setw(25) << "Rent Days" << "|" << left << setw(25) << Renter.RentDays << "|\n";
		cout << left << setw(35) << " " << "-----------------------------------------------------\n";

		cout << left << setw(35) << " " << "|" << left << setw(25) << "Rent Date" << "|" << left << setw(25) << Renter.RentDate() << "|\n";
		cout << left << setw(35) << " " << "-----------------------------------------------------\n";

		cout << left << setw(35) << " " << "|" << left << setw(25) << "Return Date" << "|" << left << setw(25) << Renter.ReturnDate() << "|\n";
		cout << left << setw(35) << " " << "-----------------------------------------------------\n";

		cout << left << setw(35) << " " << "|" << left << setw(25) << "Day Penalty" << "|" << left << fixed << setw(25) << setprecision(2) << Renter.PenaltyPerDay() << "|\n";
		cout << left << setw(35) << " " << "-----------------------------------------------------\n";

		cout << left << setw(35) << " " << "|" << left << setw(25) << "Delay Days" << "|" << left << setw(25) << Renter.DelayDays() << "|\n";
		cout << left << setw(35) << " " << "-----------------------------------------------------\n";

		cout << left << setw(35) << " " << "|" << left << setw(25) << "Total Penalty" << "|" << left << fixed << setw(25) << setprecision(2) << Renter.TotalPenalty() << "|\n";
		cout << left << setw(35) << " " << "-----------------------------------------------------\n";

		cout << left << setw(35) << " " << "|" << left << setw(25) << "Total Bill" << "|" << left << fixed << setw(25) << setprecision(2) << Renter.TotalBill() << "|\n";
		cout << left << setw(35) << " " << "-----------------------------------------------------" << endl;
	}

	static void _PrintMenuHedar()
	{
		cout << endl;

		cout << left << setw(37) << " " << "==============================================\n";
		cout << left << setw(37) << " " << "| ";
		cout << left << setw(43) << "          Return Books Screen" << "|\n";
		cout << left << setw(37) << " " << "==============================================\n";
	}

	static void _ReturnBook()
	{
		clsBook Book = clsBook::Find(_ReadIdNumber());

		if (Book.IsEmpty())
		{
			cout << "\n Book is not found.\n";
			return;
		}

		if (Book.IsAvailable())
		{
			cout << "\n Book is not rented.\n";
			return;
		}

		_PrintBook(Book);

		_PrintRenterDetails(Book.Renter);
		
		char Sure = 'N';

		cout << "\n Are you sure you want to return this book? Y/N? ";
		cin >> Sure;

		if (toupper(Sure) == 'Y')
		{
			if (Book.ReturnBook())
			{
				cout << " \n Book returned successfully.\n";
			}

			else
			{
				cout << "\n Book return Faild.\n";
			}
		}

		else
		{
			cout << "\n Book return canceled.\n";
		}

	}

	static void _ShowReturnBookScreen()
	{
		_PrintMenuHedar();

		_ReturnBook();
	}

public:

	static void ShowReturnBookScreen()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pReturnBook))
			return;

		char RentMore = 'N';

		do
		{
			clsUtil::ResetScreen();

			_ShowReturnBookScreen();

			cout << "\n Do you want to return more books? Y/N? ";
			cin >> RentMore;

		} while (toupper(RentMore) == 'Y');

	}

};

