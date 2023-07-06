#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsFindUserScreen : protected clsScreen
{

private:

	static void _PrintUser(clsUser User)
	{
		cout << "\n User Card:\n";
		cout << "________________________________________\n";
		cout << "\n First Name  : " << User.FirstName;
		cout << "\n Last Name   : " << User.LastName;
		cout << "\n Full Name   : " << User.FullName();
		cout << "\n Email       : " << User.Email;
		cout << "\n Phone       : " << User.Phone;
		cout << "\n Username    : " << User.Username;
		cout << "\n Password    : " << User.Password;
		cout << "\n Permissions : " << User.Permissions;
		cout << "\n________________________________________\n";
	}

	static void _FindUser()
	{
		string Username;

		cout << "\n Enter Username? ";
		Username = clsInputValidate::ReadString();

		/*while (!clsUser::IsUserExist(Username))
		{
			cout << "\nUser is not Found, Enter Another One: ";
			Username = clsInputValidate::ReadString();
		}*/

		clsUser User = clsUser::Find(Username);

		if (User.IsEmpty())
		{
			cout << "\n User is not found.\n";
			return;
		}

		_PrintUser(User);
	}

public:

	static void ShowFindUserScreen()
	{
		if (!CheckAccessRights(clsUser::pManageUsers))
		{
			return;
		}

		string Title = "\t\t   Find User Screen";
		char Answer = 'N';

		do
		{
			_DrawScreenHeader(Title);

			_FindUser();

			cout << "\n Do you want to find another user? Y/N? ";
			cin >> Answer;

		} while (toupper(Answer) == 'Y');
		
	}

};

