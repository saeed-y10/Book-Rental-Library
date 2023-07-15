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

class clsUpdateRenterScreen : protected clsScreen
{

private:

	struct stRenterInfo
	{
		string FirstName = "";
		string LastName = "";
		string Gender = "";
		string Email = "";
		string Phone = "";
	};

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

	static void _PrintBooksList(vector<clsBook> vBooks)
	{
		cout << "\n ______________________________________________________________________________________________________________________\n\n";
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

	static void _PrintMenuHeder()
	{
		cout << endl;

		cout << left << setw(37) << " " << "==============================================\n";
		cout << left << setw(37) << " " << "| ";
		cout << left << setw(43) << "            Update Renter Screen" << "|\n";
		cout << left << setw(37) << " " << "==============================================\n";
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

		cout << left << setw(35) << " " << "|" << left << setw(25) << "Gender" << "|" << left << setw(25) << Book.Renter.Gender << "|\n";
		cout << left << setw(35) << " " << "-----------------------------------------------------\n";

		cout << left << setw(35) << " " << "|" << left << setw(25) << "Email" << "|" << left << setw(25) << Book.Renter.Email << "|\n";
		cout << left << setw(35) << " " << "-----------------------------------------------------\n";

		cout << left << setw(35) << " " << "|" << left << setw(25) << "Phone" << "|" << left << setw(25) << Book.Renter.Phone << "|\n";
		cout << left << setw(35) << " " << "-----------------------------------------------------\n";
	}

	static stRenterInfo _ReadRenterInfo()
	{
		stRenterInfo Info;

		cout << "\n Update Renter Info: \n";
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
		
		return Info;
	}

	static void _UpdateRenter()
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

		cout << "\n Renter Books:";
		_PrintBooksList(vBooks);

		char Answer = 'N';

		cout << "\n Are you sure to update this renter? Y/N? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			stRenterInfo Info = _ReadRenterInfo();

			vector<clsBook::enSaveResult> vResults;

			for (clsBook& Book : vBooks)
			{
				Book.Renter.FirstName = Info.FirstName;
				Book.Renter.LastName = Info.LastName;
				Book.Renter.Email = Info.Email;
				Book.Renter.Phone = Info.Phone;

				vResults.push_back(Book.Save());
			}

			cout << endl;
			short Counter = 1;

			for (clsBook::enSaveResult &Result : vResults)
			{
				switch (Result)
				{
				case clsBook::enSaveResult::svSucceeded:
				{
					cout << " Book " << Counter << " details updated successfully.\n";
					break;
				}

				default:
				{
					cout << " Book " << Counter << " details update faild.\n";
					break;
				}

				}

				Counter++;
			}

		}

		else
		{
			cout << "\n Renter update canceled.\n";
		}

	}

	static void _ShowRentBookScreen()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pRentBook))
			return;

		char Answer = 'N';

		do
		{
			clsUtil::ResetScreen();

			_PrintMenuHeder();

			_UpdateRenter();

			cout << "\n Do you want to update more renters? Y/N? ";
			cin >> Answer;

		} while (toupper(Answer) == 'Y');
	}

public:

	static void ShowRentBookScreen()
	{
		_ShowRentBookScreen();
	}

};

