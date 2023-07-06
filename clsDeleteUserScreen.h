#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsDeleteUserScreen : protected clsScreen
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
		cout << "\n________________________________________\n\n";
	}

	static void _DeleteUser()
	{
		string Username;

		cout << "\n Enter Username? ";
		Username = clsInputValidate::ReadString();

		clsUser User = clsUser::Find(Username);

		if (User.IsEmpty())
		{
			cout << "\n User is not found.\n";
			
			return;
		}

		if (Username == "Admin")
		{
			cout << "\n You cannot delete this user!\n";

			return;
		}

		_PrintUser(User);

		char Answer = 'N';

		cout << " Are you sure to delete this user? Y/N? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			if (User.Delete())
			{
				cout << "\n User deleted successfully.\n";

				_PrintUser(User);
			}

			else
			{
				cout << "\n Error user was not deleted.\n";
			}
		}

		else
		{
			cout << "\n User delete canceled.\n";
		}
	}

public:

	static void ShowDeleteUserScreen()
	{
		if (!CheckAccessRights(clsUser::pManageUsers))
		{
			return;
		}

		string Title = "\t\t  Delete User Screen";


		char Answer = 'N';

		do
		{
			_DrawScreenHeader(Title);

			_DeleteUser();

			cout << "\n Do you want to delete another user? Y/N? ";
			cin >> Answer;

		} while (toupper(Answer) == 'Y');
		
	}

};

