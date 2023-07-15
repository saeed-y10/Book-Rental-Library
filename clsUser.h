#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "clsString.h"
#include "clsUtil.h"
#include "clsPerson.h"
#include "clsUser.h"

using namespace std;

class clsUser : public clsPerson
{
private:

	struct stLoginRegisterRecord;

	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };

	enMode _Mode;
	string _Username;
	string _Password;
	int _Permissions;
	bool _MarkForDelete = false;

	static clsUser _ConvertLineToUserOpject(string Line, string Seperator = "#//#")
	{
		vector<string> vLine = clsString::Split(Line, Seperator);

		return clsUser(enMode::UpdateMode, vLine[0], vLine[1], vLine[2], vLine[3], vLine[4], vLine[5], clsUtil::DecryptText(vLine[6]), stoi(vLine[7]));
	}

	static string _ConvertUserObjectToLine(clsUser User, string Seperator = "#//#")
	{
		string DataLine = "";

		DataLine += User.FirstName + Seperator;
		DataLine += User.LastName + Seperator;
		DataLine += User.Gender + Seperator;
		DataLine += User.Email + Seperator;
		DataLine += User.Phone + Seperator;
		DataLine += User.Username + Seperator;
		DataLine += clsUtil::EncryptText(User.Password) + Seperator;
		DataLine += to_string(User.Permissions);

		return DataLine;
	}

	static vector<clsUser> _LoadUsersDataFromFile(string FileName = "Users.txt")
	{
		vector<clsUser> _vUsers;

		fstream File;

		File.open(FileName, ios::in);

		if (File.is_open())
		{
			string Line;

			while (getline(File, Line))
			{
				clsUser User = _ConvertLineToUserOpject(Line);

				_vUsers.push_back(User);
			}

			File.close();
		}

		return _vUsers;
	}

	static void _SaveUsersDataToFile(vector<clsUser> vUsers, string FileName = "Users.txt")
	{
		fstream File;

		File.open(FileName, ios::out);

		if (File.is_open())
		{
			string Line;

			for (clsUser User : vUsers)
			{
				if (User.MarkedForDelete() == false)
				{
					Line = _ConvertUserObjectToLine(User);

					File << Line << endl;
				}

			}

			File.close();
		}
	}

	void _AddDataLineToFile(string DataLine, string FileName = "Users.txt")
	{
		fstream File;

		File.open(FileName, ios::out | ios::app);

		if (File.is_open())
		{
			File << DataLine << endl;

			File.close();
		}
	}

	static clsUser _GetEmptyUserObject()
	{
	  	return clsUser(enMode::EmptyMode, "", "", "", "", "", "", "", 0);
	}

	bool _Delete()
	{
		vector<clsUser> vUsers = _LoadUsersDataFromFile();

		for (clsUser& User : vUsers)
		{
			if (User.Username == _Username)
			{
				User._MarkForDelete = true;
				
				*this = _GetEmptyUserObject();

				_SaveUsersDataToFile(vUsers);

				return true;
			}
		}

		return false;
	}

	void _Update()
	{
		vector<clsUser> vUsers = _LoadUsersDataFromFile();

		for (clsUser& User : vUsers)
		{
			if (User.Username == _Username)
			{
				User = *this;
				break;
			}
		}

		_SaveUsersDataToFile(vUsers);
	}

	void _AddNewUser()
	{
		_AddDataLineToFile(_ConvertUserObjectToLine(*this));
	}

	string _PrepareLoginRegisterRecoed(string Seperator = "#//#")
	{
		string LoginRecord = "";

		LoginRecord += clsDate::GetSystemDateTimeString() + Seperator;
		LoginRecord += Username + Seperator;
		LoginRecord += clsUtil::EncryptText(Password) + Seperator;
		LoginRecord += to_string(Permissions);

		return LoginRecord;
	}

	static clsUser::stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(string Line, string Seperator = "#//#")
	{
		stLoginRegisterRecord Record;

		vector<string> vLine = clsString::Split(Line, Seperator);

		Record.DateTime = vLine[0];
		Record.Username = vLine[1];
		Record.Password = clsUtil::DecryptText(vLine[2]);
		Record.Permissions = stoi(vLine[3]);

		return Record;
	}

	static vector<stLoginRegisterRecord> _LoadLoginRegisterDataFromFile(string FileName = "RegisterLogin.txt")
	{
		vector<stLoginRegisterRecord> vLoginReister;

		fstream File;

		File.open(FileName, ios::in);

		if (File.is_open())
		{
			string Line;
			stLoginRegisterRecord LoginRegister;

			while (getline(File, Line))
			{
				LoginRegister = _ConvertLoginRegisterLineToRecord(Line);

				vLoginReister.push_back(LoginRegister);
			}

			File.close();
		}

		return vLoginReister;
	}

public:

	clsUser(enMode Mode, string FirstName, string LastName, string Gender, string Email, string Phone, string Username, string Password, int Permissions)
		: clsPerson(FirstName, LastName, Gender, Email, Phone)
	{
		_Mode = Mode;
		_Username = Username;
		_Password = Password;
		_Permissions = Permissions;
	}

	enum enPermissions
	{
		pAll = -1,
		pListBooks = 1,
		pFindBook = 2,
		pRentBook = 4,
		pReturnBook = 8,
		pAddNewBook = 16,
		pUpdateBook = 32,
		pDeleteBook = 64,
		pManageRenters = 128,
		pManageUsers = 256,
	};

	struct stLoginRegisterRecord
	{
		string DateTime;
		string Username;
		string Password;
		int Permissions;
	};

	void SetUsername(string Username)
	{
		_Username = Username;
	}

	string GetUsername()
	{
		return _Username;
	}
	__declspec(property(get = GetUsername, put = SetUsername)) string Username;

	void SetPassword(string Password)
	{
		_Password = Password;
	}

	string GetPassword()
	{
		return _Password;
	}
	__declspec(property(get = GetPassword, put = SetPassword)) string Password;

	void SetPermissions(int Permissions)
	{
		_Permissions = Permissions;
	}

	int GetPermissions()
	{
		return _Permissions;
	}
	__declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;

	enum enSaveResult
	{
		svEmptyFaild = 0,
		svSucceeded = 1,
		svFaildUsernameExist = 2,
		svFaildUsernameDontExist = 3,
	};

	bool IsEmpty()
	{
		return _Mode == enMode::EmptyMode;
	}

	bool MarkedForDelete()
	{
		return _MarkForDelete;
	}

	static clsUser Find(string Username)
	{
		vector<clsUser> vUsers;

		fstream File;

		File.open("Users.txt", ios::in);

		if (File.is_open())
		{
			string Line;

			while (getline(File, Line))
			{
				clsUser User = _ConvertLineToUserOpject(Line);

				vUsers.push_back(User);

				if (User.Username == Username)
				{
					File.close();

					return User;
				}

			}

			File.close();
		}


		return _GetEmptyUserObject();
	}

	static clsUser Find(string Username, string Password)
	{
		vector<clsUser> vUsers;

		fstream File;

		File.open("Users.txt", ios::in);

		if (File.is_open())
		{
			string Line;

			while (getline(File, Line))
			{
				clsUser User = _ConvertLineToUserOpject(Line);

				vUsers.push_back(User);

				if (User.Username == Username && User.Password == Password)
				{
					File.close();

					return User;
				}

			}

			File.close();
		}


		return _GetEmptyUserObject();
	}

	static bool IsUserExist(string Username)
	{
		return !(Find(Username).IsEmpty());
	}

	static clsUser GetNewUserObject(string Username)
	{
		if (IsUserExist(Username))
		{
			return _GetEmptyUserObject();
		}

		else
		{
			return clsUser(enMode::AddNewMode, "", "", "", "", "", Username, "", 0);
		}
	}

	enSaveResult Save()
	{
		switch (_Mode)
		{

		case enMode::EmptyMode:
		{
			if (IsEmpty())
			{
				return enSaveResult::svEmptyFaild;
		    }
		}

		case enMode::UpdateMode:
		{
			if (IsUserExist(_Username))
			{
				_Update();

				return enSaveResult::svSucceeded;
			}

			else
			{
				return enSaveResult::svFaildUsernameDontExist;
			}
		}

		case enMode::AddNewMode:
		{
			if (IsUserExist(_Username))
			{
				return enSaveResult::svFaildUsernameExist;
			}

			else
			{
				_AddNewUser();

				_Mode = enMode::UpdateMode;

				return enSaveResult::svSucceeded;
			}
		}

		default:
			return enSaveResult::svEmptyFaild;

		}

	}

	bool Delete()
	{
		vector<clsUser> vUsers = _LoadUsersDataFromFile();

		for (clsUser& User : vUsers)
		{
			if (User.Username == _Username)
			{
				User._MarkForDelete = true;
				break;
			}
		}

		_SaveUsersDataToFile(vUsers);
		
		*this = _GetEmptyUserObject();

		return true;
	}

	static vector<clsUser> GetUsersList()
	{
		return _LoadUsersDataFromFile();
	}

	bool CheckAccessPermissions(enPermissions Permission)
	{
		if (this->Permissions == enPermissions::pAll)
			return true;

		if ((Permission & this->Permissions) == Permission)
			return true;

		else
			return false;
	}

	void RegisterLogin()
	{
		string DataLine = _PrepareLoginRegisterRecoed();

		fstream File;

		File.open("RegisterLogin.txt", ios::out | ios::app);

		if (File.is_open())
		{
			File << DataLine << endl;

			File.close();
		}
	}
	
	static vector<stLoginRegisterRecord> GetLoginRegisterList()
	{
		vector<stLoginRegisterRecord> vLoginReisters;

		fstream File;

		File.open("RegisterLogin.txt", ios::in);

		if (File.is_open())
		{
			string Line;
			stLoginRegisterRecord LoginRegister;

			while (getline(File, Line))
			{
				LoginRegister = _ConvertLoginRegisterLineToRecord(Line);

				vLoginReisters.push_back(LoginRegister);
			}

			File.close();
		}

		return _LoadLoginRegisterDataFromFile();
	}

};

