#pragma once

#include <iostream>
#include <iomanip>
#include "clsUtil.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "Global.h"
#include "clsListBooksScreen.h"
#include "clsFindBookScreen.h"
#include "clsRentBookScreen.h"
#include "clsReturnBookScreen.h"
#include "clsAddNewBookScreen.h"
#include "clsUpdateBookScreen.h"
#include "clsDeleteBookScreen.h"
#include "clsManageUsersScreen.h"
#include "clsManageRentersScreen.h"

using namespace std;

class clsMainScreen : protected clsScreen
{
private:

	static void _PrintMainMenuHeader()
	{
		_DrawScreenHeader("\t\t       Main Menu");

		cout << endl;

		cout << left << setw(37) << " " << "==============================================\n";
		cout << left << setw(37) << " " << "| ";
		cout << left << setw(43) << "                Main Menu" << "|\n";
		cout << left << setw(37) << " " << "==============================================\n";

		cout << left << setw(37) << " " << "| ";
		cout << left << setw(43) << "[1] List Books." << "|\n";

		cout << left << setw(37) << " " << "| ";
		cout << left << setw(43) << "[2] Find Book." << "|\n";

		cout << left << setw(37) << " " << "| ";
		cout << left << setw(43) << "[3] Rent Book." << "|\n";

		cout << left << setw(37) << " " << "| ";
		cout << left << setw(43) << "[4] Return Book." << "|\n";

		cout << left << setw(37) << " " << "| ";
		cout << left << setw(43) << "[5] Add New Book." << "|\n";

		cout << left << setw(37) << " " << "| ";
		cout << left << setw(43) << "[6] Update Book." << "|\n";

		cout << left << setw(37) << " " << "| ";
		cout << left << setw(43) << "[7] Delete Book." << "|\n";

		cout << left << setw(37) << " " << "| ";
		cout << left << setw(43) << "[8] Manage Renters." << "|\n";

		cout << left << setw(37) << " " << "| ";
		cout << left << setw(43) << "[9] Manage Users." << "|\n";

		cout << left << setw(37) << " " << "| ";
		cout << left << setw(43) << "[10] Logout." << "|\n";

		cout << left << setw(37) << " " << "| ";
		cout << left << setw(43) << "[11] Exit." << "|\n";

		cout << left << setw(37) << " " << "==============================================\n\n";
	}

	static void _PrintGoBackToMainMenu()
	{
		cout << "\n Press Any Key To Go Back To Main Menu...\n";

		system("pause>0");
	}

	enum enMainMenuOptions
	{
		eListBooks = 1,
		eFindBook = 2,
		eRentBook = 3,
		eReturnBook = 4,
		eAddNewBook = 5,
		eUpdateBook = 6,
		eDeleteBook = 7,
		eManageRenters = 8,
		eManageUsers = 9,
		eLogout = 10,
		eExit = 11,
	};

	static void _Logout()
	{
		CurrentUser = clsUser::Find("", "");
	}

	static enMainMenuOptions _ReadMainMenuOption()
	{
		short Option;

		cout << "\t\t\t\t     Choose What Do You Want To Do? [1 To 11]? ";

		Option = clsInputValidate::ReadNumberBetween<short>(1, 11, "\t\t\t\t     Choose What Do You Want To Do? [1 To 11]? ");

		return (enMainMenuOptions)Option;
	}

	static void _ShowListBooksScreen()
	{
		clsListBooksScreen::ShowListBooksScreen();
	}

	static void _ShowFindBookScreen()
	{
		clsFindBookScreen::ShowFindBookScreen();
	}

	static void _ShowRentBookScreen()
	{
		clsRentBookScreen::ShowRentBookScreen();
	}

	static void _ShowRenturnBookScreen()
	{
		clsReturnBookScreen::ShowReturnBookScreen();
	}

	static void _AddNewBookScreen()
	{
		clsAddNewBookScreen::ShowAddNewBookScreen();
	}

	static void _ShowUpdateBookScreen()
	{
		clsUpdateBookScreen::_ShowUpdateBookScreen();
	}

	static void _ShowDeleteBookScreen()
	{
		clsDeleteBookScreen::ShowDeleteBookScreen();
	}

	static void _ShowManageRentersScreen()
	{
		clsManageRentersScreen::ShowManageRentersMenu();
	}

	static void _ShowManageUsersScreen()
	{
		clsManageUsersScreen::ShowManageUsersMenu();
	}

	static void _PerformMainMenuOption(enMainMenuOptions Option)
	{
		switch (Option)
		{
		
		case enMainMenuOptions::eListBooks:
		{
			_ShowListBooksScreen();

			_PrintGoBackToMainMenu();

			break;
		}

		case enMainMenuOptions::eFindBook:
		{
			_ShowFindBookScreen();
	
			_PrintGoBackToMainMenu();

			break;
		}

		case enMainMenuOptions::eRentBook:
		{
			_ShowRentBookScreen();

			_PrintGoBackToMainMenu();

			break;
		}

		case enMainMenuOptions::eReturnBook:
		{
			_ShowRenturnBookScreen();

			_PrintGoBackToMainMenu();

			break;
		}

		case enMainMenuOptions::eAddNewBook:
		{
			_AddNewBookScreen();
			
			_PrintGoBackToMainMenu();

			break;
		}

		case enMainMenuOptions::eUpdateBook:
		{
			_ShowUpdateBookScreen();
			
			_PrintGoBackToMainMenu();

			break;
		}

		case enMainMenuOptions::eDeleteBook:
		{
			_ShowDeleteBookScreen();

			_PrintGoBackToMainMenu();

			break;
		}

		case enMainMenuOptions::eManageRenters:
		{
			_ShowManageRentersScreen();

			_PrintGoBackToMainMenu();

			break;
		}

		case enMainMenuOptions::eManageUsers:
		{
			_ShowManageUsersScreen();

			_PrintGoBackToMainMenu();

			break;
		}

		case enMainMenuOptions::eLogout:
		{
			_Logout();

			break;
		}

		case enMainMenuOptions::eExit:
		{
			exit(1);
		}

		default:
			exit(1);
		}
	}

public:

	static void ShowMainMenu()
	{
		enMainMenuOptions Option = enMainMenuOptions::eExit;

		do
		{
			_PrintMainMenuHeader();

			Option = _ReadMainMenuOption();

			_PerformMainMenuOption(Option);

		} while (Option != enMainMenuOptions::eExit && Option != enMainMenuOptions::eLogout);

	}

};

