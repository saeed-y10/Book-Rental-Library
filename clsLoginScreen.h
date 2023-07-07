#pragma once

#include <iostream>
#include "clsUtil.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsUser.h"
#include "clsMainScreen.h"
#include "Global.h"

class clsLoginScreen : protected clsScreen
{

private:

	static bool _Login()
	{
		string Username;
		string Password;

		short FaildLoginCount = 0;
		bool LoginFailed = false;

		do
		{

			if (LoginFailed)
			{
				if (FaildLoginCount == 5)
				{
					cout << "\n You Are Locked After 5 Faild Trail(s).\n";

					return false;
				}

				else
				{
					cout << "\n Invalid Username/Password!";
					cout << "\n You Have " << 5 - FaildLoginCount << " Trail(s) To Login." << "\n";
				}
			}

			cout << "\n Username : ";
			Username = clsInputValidate::ReadString();

			cout << " Password : ";
			Password = clsInputValidate::ReadString();

			CurrentUser = clsUser::Find(Username, Password);

			if (CurrentUser.IsEmpty())
			{
				FaildLoginCount++;

				LoginFailed = true;
			}

			else 
				LoginFailed = false;

		} while (LoginFailed);

		CurrentUser.RegisterLogin();

		clsMainScreen::ShowMainMenu();
		
		return true;
	}

public:
	 
	static bool ShowLoginScreen()
	{
		do
		{
			clsUtil::ResetScreen();

			_DrawScreenHeader("\t\t     Login Screen");

		} while (_Login());

		return false;
	}

};

