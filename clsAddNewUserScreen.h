#pragma once

#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsAddNewUserScreen : protected clsScreen
{
private:

	static int _ReadPermissions()
	{
		int Permissions = 0;

		char Answer = 'N';

		cout << "\n Do You Want To Give Full Access? Y/N? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			return clsUser::enPermissions::pAll;
		}

		cout << "\n Do You Want To Give Access To:\n";

		cout << "\n Show Books List? Y/N? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			Permissions = clsUser::enPermissions::pListBooks;
		}

		cout << "\n Find Books? Y/N? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			Permissions += clsUser::enPermissions::pFindBook;
		}

		cout << "\n Rent Books? Y/N? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			Permissions += clsUser::enPermissions::pRentBook;
		}

		cout << "\n Return Books? Y/N? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			Permissions += clsUser::enPermissions::pReturnBook;
		}

		cout << "\n Add New Books? Y/N? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			Permissions += clsUser::enPermissions::pAddNewBook;
		}

		cout << "\n Update Books? Y/N? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			Permissions += clsUser::enPermissions::pUpdateBook;
		}

		cout << "\n Delete Books? Y/N? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			Permissions += clsUser::enPermissions::pDeleteBook;
		}

		cout << "\n Manage Renters? Y/N? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			Permissions += clsUser::enPermissions::pManageRenters;
		}

		cout << "\n Manage Users? Y/N? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			Permissions += clsUser::enPermissions::pManageUsers;
		}

		return Permissions;
	}

	static void _ReadUserInfo(clsUser& User)
	{
		cout << "\n Enter First Name   : ";
		User.FirstName = clsInputValidate::ReadString();
		
		cout << " Enter Last Name    : ";
		User.LastName = clsInputValidate::ReadString();

		cout << " Enter Email        : ";
		User.Email = clsInputValidate::ReadString();

		cout << " Enter Phone Number : ";
		User.Phone = clsInputValidate::ReadString();

		cout << " Enter Password     : ";
		User.Password = clsInputValidate::ReadString();

		cout << "\n Read Permissions:\n";
		User.Permissions = _ReadPermissions();
	}

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

	static void _AddNewUser()
	{
		string Username;

		cout << "\n Enter Username? ";
		Username = clsInputValidate::ReadString();

		if (clsUser::IsUserExist(Username))
		{
			cout << "\n Username is already exist.\n";

			return;
		}

		clsUser NewUser = clsUser::GetNewUserObject(Username);

		cout << "\n Adding new user:\n";
		cout << "________________________________________\n";

		_ReadUserInfo(NewUser);

		cout << "________________________________________\n";

		_PrintUser(NewUser);

		char Answer = 'N';

		cout << "\n Are you sure to add this user? Y/N? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			clsUser::enSaveResult SaveResult = NewUser.Save();

			switch (SaveResult)
			{
			case clsUser::enSaveResult::svSucceeded:
			{
				cout << "\n User added successfully.\n";
				break;
			}

			case clsUser::enSaveResult::svEmptyFaild:
			{
				cout << "\n User add faild, \"object is empty\".\n";
				break;
			}

			case clsUser::enSaveResult::svFaildUsernameExist:
			{
				cout << "\n User add faild, \"Username is exist\".\n";
				break;
			}

			}
		}

		else
		{
			cout << "\n User add canceled.\n";
		}

	}

public:

	static void ShowAddNewClientScreen()
	{
		if (!CheckAccessRights(clsUser::pManageUsers))
		{
			return;
		}

		char AddMore = 'N';
		
		string Title = "\t\t Add New User Screen";

		do
		{
			_DrawScreenHeader(Title);

			_AddNewUser();

			cout << "\n Do you wnat to add more users? Y/N? ";
			cin >> AddMore;

		} while (toupper(AddMore == 'Y'));
	}

};

