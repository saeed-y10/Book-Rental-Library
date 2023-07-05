#pragma once

#include <iostream>
#include <iomanip>
#include "clsDate.h"
#include "clsUser.h"
#include "Global.h"

using namespace std;

class clsScreen
{

private:

	static void _PrintAccessDenied()
	{
		clsUtil::ResetScreen();

		cout << "\a" << endl;

		cout << left << setw(37) << " " << "==============================================\n";
		cout << left << setw(37) << " " << "| ";
		cout << left << setw(42) << "             Access Denied" << " |\n";
		cout << left << setw(37) << " " << "==============================================\n";

		cout << left << setw(37) << " " << "| ";
		cout << left << setw(42) << "You Dont Have The Permissions To Do This." << " |\n";

		cout << left << setw(37) << " " << "| ";
		cout << left << setw(42) << "Please Contact With Your Manager." << " |\n";

		cout << left << setw(37) << " " << "==============================================\n\n";
	}

protected:

	static void _DrawScreenHeader(string Title, string SubTitle = "")
	{
		clsUtil::ResetScreen();

		cout << "\t\t\t\t     " << "______________________________________________\n\n";
		cout << "\t\t\t\t     " << Title << "\n";
		
		if (SubTitle != "")
			cout << "\t\t\t\t     " << SubTitle << "\n";
		
		cout << "\t\t\t\t     " << "______________________________________________\n\n";

		cout << "\t\t\t\t     User: " << CurrentUser.Username << "\n";
		cout << "\t\t\t\t     Date: " << clsDate::ToString(clsDate()) << "\n\n";
	}

	static bool CheckAccessRights(clsUser::enPermissions Permission)
	{
		if (CurrentUser.CheckAccessPermissions(Permission))
		{
			return true;
		}

		else
		{
			_PrintAccessDenied();
			return false;
		}
	}

};

