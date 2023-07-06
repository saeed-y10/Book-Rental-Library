#pragma once

#include <iostream>
#include <iomanip>
#include "clsUtil.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsListRentersScreen.h"

using namespace std;

class clsManageRentersScreen : protected clsScreen
{

private:

	static void _GoBackToManageRentersMenuOption()
	{
		cout << "\n Press Any Key To Go Back To Manage Renters Menu...\n";

		system("pause>0");
	}

	enum enManageRentersMenuOptions
	{
		eListRenters = 1,
		eFindRenter = 2,
		eUpdateRenter = 3,
		eReturnBooks = 4,
		eGoBack = 5,
	};

	static enManageRentersMenuOptions _ReadManageRentersMenuOption()
	{
		cout << "\t\t\t\t     Choose What Do You Want To Do? [1 To 5]? ";

		short Option = clsInputValidate::ReadNumberBetween<short>(1, 5, "\t\t\t\t     Choose What Do You Want To Do? [1 To 5]? ");

		return (enManageRentersMenuOptions)Option;
	}

	static void _PrintMenuHedar()
	{
		clsUtil::ResetScreen();

		_DrawScreenHeader("\t\t   Manage Renters Menu");

		cout << endl;

		cout << left << setw(37) << " " << "==============================================\n";
		cout << left << setw(37) << " " << "| ";
		cout << left << setw(42) << "          Manage Renters Menu" << " |\n";
		cout << left << setw(37) << " " << "==============================================\n";

		cout << left << setw(37) << " " << "| ";
		cout << left << setw(42) << "[1] List Renters." << " |\n";

		cout << left << setw(37) << " " << "| ";
		cout << left << setw(42) << "[2] Find Renter." << " |\n";

		cout << left << setw(37) << " " << "| ";
		cout << left << setw(42) << "[3] Update Renter." << " |\n";

		cout << left << setw(37) << " " << "| ";
		cout << left << setw(42) << "[4] Return Books." << " |\n";

		cout << left << setw(37) << " " << "| ";
		cout << left << setw(42) << "[5] Go Back." << " |\n";

		cout << left << setw(37) << " " << "==============================================\n" << endl;
	}

	static void _ShowListRentersScreen()
	{
		clsListRentersScreen::ShowListRentersScreen();
	}

	static void _ShowFindRenterScreen()
	{

	}

	static void _ShowUpdateRenterScreen()
	{

	}

	static void _ShowReturnBooksScreen()
	{

	}

	static void _PerformManageRentersMenuOption(enManageRentersMenuOptions Option)
	{
		switch (Option)
		{
		case enManageRentersMenuOptions::eListRenters:
		{
			_ShowListRentersScreen();

			_GoBackToManageRentersMenuOption();

			break;
		}

		case enManageRentersMenuOptions::eFindRenter:
		{
			break;
		}

		case enManageRentersMenuOptions::eUpdateRenter:
		{

			break;
		}

		case enManageRentersMenuOptions::eReturnBooks:
		{
			break;
		}

		case enManageRentersMenuOptions::eGoBack:
		{
			break;
		}

		default:
		{
			return;

			break;
		}

		}
	}

	static void _ShowManageRentersMenu()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pManageRenters))
			return;

		enManageRentersMenuOptions Option = enManageRentersMenuOptions::eGoBack;

		do
		{
			_PrintMenuHedar();

			Option = _ReadManageRentersMenuOption();

			_PerformManageRentersMenuOption(Option);

		} while (Option != enManageRentersMenuOptions::eGoBack);

	}

public:

	static void ShowManageRentersMenu()
	{
		_ShowManageRentersMenu();
	}

};

