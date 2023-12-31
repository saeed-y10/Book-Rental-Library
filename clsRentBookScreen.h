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

class clsRentBookScreen : protected clsScreen
{

private:

	struct stRenterInfo
	{
		string FirstName = "";
		string LastName = "";
		string Gender = "";
		string Email = "";
		string Phone = "";
		short RentDays = 0;
	};

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
		cout << endl;

		cout << left << setw(37) << " " << "==============================================\n";
		cout << left << setw(37) << " " << "| ";
		cout << left << setw(43) << "           Rent Books Screen" << "|\n";
		cout << left << setw(37) << " " << "==============================================\n";
	}

	static stRenterInfo _ReadRenterInfo()
	{
		stRenterInfo Info;

		cout << "\n Read Renter Info: \n";
		cout << " ___________________________________\n";

		cout << " First Name      : ";
		Info.FirstName = clsInputValidate::ReadString();

		cout << " Last Name       : ";
		Info.LastName = clsInputValidate::ReadString();

		do
		{
			cout << " Gender          : ";
			Info.Gender = clsInputValidate::ReadString();

			Info.Gender = clsString::UpperAllLetters(Info.Gender);

		} while (Info.Gender != "MALE" && Info.Gender != "FEMALE" && Info.Gender != "M" && Info.Gender != "F");

		cout << " Email           : ";
		Info.Email = clsInputValidate::ReadString();

		cout << " Phone           : ";
		Info.Phone = clsInputValidate::ReadString();

		cout << " Rent Days (1/30): ";
		Info.RentDays = clsInputValidate::ReadNumberBetween<short>(1, 30, " Rent Days (1/30): ");

		return Info;
	}

	static void _RentBook()
	{
		clsBook Book = clsBook::Find(_ReadIdNumber());

		if (Book.IsEmpty())
		{
			cout << "\n Book is not found.\n";
			return;
		}

		if (!Book.IsAvailable())
		{
			cout << "\n Book is already rented.\n";
			return;
		}

		_PrintBook(Book);

		char Sure = 'N';

		cout << "\n Are you sure you want to rent this book? Y/N? ";
		cin >> Sure;

		if (toupper(Sure) == 'Y')
		{
			stRenterInfo Info = _ReadRenterInfo();

			if (Book.RentBook(Info.FirstName, Info.LastName, Info.Gender, Info.Email, Info.Phone, Info.RentDays))
			{
				cout << " \n Book rented successfully.\n";

				_PrintBook(Book);
			}

			else
			{
				cout << "\n Book rent Faild.\n";
			}
		}

		else
		{
			cout << "\n Book rent canceled.\n";
		}

	}

	static void _ShowRentBookScreen()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pRentBook))
			return;

		char RentMore = 'N';

		do
		{
			clsUtil::ResetScreen();

			_PrintMenuHedar();

			_RentBook();
			
			cout << "\n Do you want to rent more books? Y/N? ";
			cin >> RentMore;

		} while (toupper(RentMore) == 'Y');

	}

public:

	static void ShowRentBookScreen()
	{
			_ShowRentBookScreen();
	}

};

