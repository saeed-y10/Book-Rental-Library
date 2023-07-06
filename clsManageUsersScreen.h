#pragma once

#include <iostream>
#include <iomanip>
#include "clsUtil.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsListUsersScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"

class clsManageUsersScreen : protected clsScreen
{

private:
	
	static void _GoBackToManageUsersMenuOption()
	{
		cout << "\n Press Any Key To Go Back To Manage Users Menu...\n";

		system("pause>0");
	}

	enum enManageUsersMenuOptions
	{
		eListUsersOption = 1,
		eAddNewUserOption = 2,
		eDeleteUserOption = 3,
		eUpdateUserOption = 4,
		eFindUserOption = 5,
		eBackToMainMenu = 6,
	};

	static enManageUsersMenuOptions _ReadManageUsersMenuOption()
	{
		cout << "\t\t\t\t     Choose What Do You Want To Do? [1 To 6]? ";

		short Option = clsInputValidate::ReadNumberBetween<short>(1, 6, "\t\t\t\t     Choose What Do You Want To Do? [1 To 6]? ");

		return (enManageUsersMenuOptions)Option;
	}

	static void _PrintMenuHedar()
	{
		clsUtil::ResetScreen();

		_DrawScreenHeader("\t\t   Manage Users Menu");

		cout << endl;

		cout << left << setw(37) << " " << "==============================================\n";
		cout << left << setw(37) << " " << "| ";
		cout << left << setw(42) << "           Manage Users Menu" << " |\n";
		cout << left << setw(37) << " " << "==============================================\n";

		cout << left << setw(37) << " " << "| ";
		cout << left << setw(42) << "[1] List Users." << " |\n";

		cout << left << setw(37) << " " << "| ";
		cout << left << setw(42) << "[2] Add New User." << " |\n";

		cout << left << setw(37) << " " << "| ";
		cout << left << setw(42) << "[3] Delete User." << " |\n";

		cout << left << setw(37) << " " << "| ";
		cout << left << setw(42) << "[4] Update User." << " |\n";

		cout << left << setw(37) << " " << "| ";
		cout << left << setw(42) << "[5] Find User." << " |\n";

		cout << left << setw(37) << " " << "| ";
		cout << left << setw(42) << "[6] Go Back." << " |\n";

		cout << left << setw(37) << " " << "==============================================\n" << endl;
	}

	static void _PerformManageUsersMenuOption(enManageUsersMenuOptions Option)
	{
		switch (Option)
		{
		case enManageUsersMenuOptions::eListUsersOption:
		{
			clsListUsersScreen::ShowListUsersScreen();

			_GoBackToManageUsersMenuOption();

			break;
		}

		case enManageUsersMenuOptions::eAddNewUserOption:
		{
			clsAddNewUserScreen::ShowAddNewClientScreen();

			break;
		}

		case enManageUsersMenuOptions::eDeleteUserOption:
		{
			clsDeleteUserScreen::ShowDeleteUserScreen();

			break;
		}

		case enManageUsersMenuOptions::eUpdateUserOption:
		{
			clsUpdateUserScreen::ShowUpdateUserScreen();

			break;
		}

		case enManageUsersMenuOptions::eFindUserOption:
		{
			clsFindUserScreen::ShowFindUserScreen();

			_GoBackToManageUsersMenuOption();

			break;
		}

		default:
		{
			break;
		}

		}
	}

	static void _ShowManageUsersMenu()
	{
		if (!CheckAccessRights(clsUser::pManageUsers))
		{
			return;
		}

		enManageUsersMenuOptions Option = enManageUsersMenuOptions::eBackToMainMenu;

		do
		{
			_PrintMenuHedar();

			_PerformManageUsersMenuOption(Option);
		
		} while (Option != enManageUsersMenuOptions::eBackToMainMenu);
		
	}

public:

	static void ShowManageUsersMenu()
	{
		_ShowManageUsersMenu();
	}

};

