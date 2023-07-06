#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsUpdateUserScreen : protected clsScreen
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

	static void _UpdateUserInfo(clsUser& User)
	{
		cout << "\n Update User:\n";
		cout << "________________________________________\n";
		
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

		if (User.Username == "Admin")
		{
			User.Permissions = clsUser::enPermissions::pAll;
		}

		else
		{
			cout << "\nRead Permissions:\n";
			User.Permissions = _ReadPermissions();
		}

		cout << "________________________________________\n";
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

	static void _UpdateUser()
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

		_PrintUser(User);

		char Answer = 'N';

		cout << "\n Are you sure to update this user? Y/N? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			_UpdateUserInfo(User);

			clsUser::enSaveResult SaveResult = User.Save();

			switch (SaveResult)
			{

			case clsUser::enSaveResult::svSucceeded:
			{
				cout << "\n User updated successfully.\n";
				
				_PrintUser(User);

				break;
			}

			case clsUser::enSaveResult::svEmptyFaild:
			{
				cout << "\nError user update faild \"object is empty\".\n";
				break;
			}

			case clsUser::enSaveResult::svFaildUsernameDontExist:
			{
				cout << "\nError user update faild \"Username not exist\".\n";
				break;
			}

			}

		}

		else
		{
			cout << "\n User update canceled.\n";
		}

	}

public:
	
	static void ShowUpdateUserScreen()
	{
		if (!CheckAccessRights(clsUser::pManageUsers))
		{
			return;
		}

		string Title = "\t\t  Update User Screen";

		char Answer = 'N';

		do
		{
			_DrawScreenHeader(Title);

			_UpdateUser();

			cout << "\n Do you wnat to update more users? Y/N? ";
			cin >> Answer;

		} while (toupper(Answer) == 'Y');

	}

};

