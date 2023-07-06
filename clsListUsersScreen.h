#pragma once

#include "clsScreen.h"
#include "clsUser.h"

class clsListUsersScreen : protected clsScreen
{

private:

	static void _PrintUserRecordLine(clsUser User)
	{
		cout << " |" << left << setw(12) << User.Username;
		cout << "|" << left << setw(30) << User.FullName();
		cout << "|" << left << setw(20) << User.Phone;
		cout << "|" << left << setw(26) << User.Email;
		cout << "|" << left << setw(12) << User.Password;
		cout << "|" << left << setw(11) << User.Permissions << "|";
	}

public:

	static void ShowListUsersScreen()
	{
		if (!CheckAccessRights(clsUser::pManageUsers))
		{
			return;
		}

		vector<clsUser> vUsers = clsUser::GetUsersList();

		string Title = "\t\t   Users List Screen";
		string SubTitle = "\t\t     (" + to_string(vUsers.size()) + ") User(s).";

		_DrawScreenHeader(Title, SubTitle);

		cout << "\n ______________________________________________________________________________________________________________________\n\n";
		cout << " |" << left << setw(12) << "Username";
		cout << "|" << left << setw(30) << "Full Name";
		cout << "|" << left << setw(20) << "Phone";
		cout << "|" << left << setw(26) << "Email";
		cout << "|" << left << setw(12) << "Password";
		cout << "|" << left << setw(11) << "Permissions" << "|\n";
		cout << " ______________________________________________________________________________________________________________________\n\n";


		if (vUsers.size() == 0)
		{
			cout << " | " << left << setw(115) << "Sorry There Are No Users in The System!" << "|\n";
		}

		else
		{
			for (clsUser User : vUsers)
			{
				_PrintUserRecordLine(User);
				cout << endl;
			}
		}

		cout << " ______________________________________________________________________________________________________________________\n";
	}

};

