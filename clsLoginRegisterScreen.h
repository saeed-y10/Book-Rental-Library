#pragma once

#include <iostream>
#include <iomanip>
#include "clsUtil.h"
#include "clsScreen.h"
#include "clsUser.h"

class clsLoginRegisterScreen : protected clsScreen
{

private:

	static void _PrintLoginRegisterRecordLine(clsUser::stLoginRegisterRecord LoginRegister)
	{
		cout << " |" << left << setw(47) << LoginRegister.DateTime;
		cout << "|" << left << setw(22) << LoginRegister.Username;
		cout << "|" << left << setw(22) << LoginRegister.Password;
		cout << "|" << left << setw(22) << LoginRegister.Permissions << "|";
	}

public:

	static void ShowLoginRegisterScreen()
	{
		if (!CheckAccessRights(clsUser::pShowLoginRegister))
		{
			return;
		}

		vector<clsUser::stLoginRegisterRecord> vLoginRegisters = clsUser::GetLoginRegisterList();

		string Title = "\t\t  Login Register Screen";
		string SubTitle = "\t\t     (" + to_string(vLoginRegisters.size()) + ") Record(s).";

		clsUtil::ResetScreen();

		_DrawScreenHeader("\t\t  Login Register Screen");

		cout << "\n ______________________________________________________________________________________________________________________\n\n";
		cout << " |" << left << setw(47) << "Date/Time";
		cout << "|" << left << setw(22) << "Username";
		cout << "|" << left << setw(22) << "Password";
		cout << "|" << left << setw(22) << "Permissions" << "|\n";
		cout << " ______________________________________________________________________________________________________________________\n\n";

		if (vLoginRegisters.size() == 0)
		{
			cout << " | " << left << setw(115) << "No Logins Available in The System!" << "|\n";
		}

		else
		{
			for (clsUser::stLoginRegisterRecord LoginRegister : vLoginRegisters)
			{
				_PrintLoginRegisterRecordLine(LoginRegister);

				cout << endl;
			}
		}

		cout << " ______________________________________________________________________________________________________________________\n";
	}

};

