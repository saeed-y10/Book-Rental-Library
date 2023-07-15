#pragma once

#include <iostream>
#include <string>
#include "clsString.h"

using namespace std;

class clsPerson
{

private:

	string _FirstName;
	string _LastName;
	string _Gender;
	string _Email;
	string _Phone;

public:

	clsPerson(string FirstName, string LastName, string Gender, string Email, string Phone)
	{
		_FirstName = FirstName;
		_LastName = LastName;
		SetGender(Gender);
		_Email = Email;
		_Phone = Phone;
	}

	void SetFirstName(string FirstName)
	{
		_FirstName = FirstName;
	}

	string GetFirstName()
	{
		return _FirstName;
	}
	__declspec(property(get = GetFirstName, put = SetFirstName)) string FirstName;

	void SetLastName(string LastName)
	{
		_LastName = LastName;
	}

	string GetLastName()
	{
		return _LastName;
	}
	__declspec(property(get = GetLastName, put = SetLastName)) string LastName;

	string FullName(bool Reversed = false)
	{
		if (Reversed)
			return _LastName + " " + _FirstName;

		else
			return _FirstName + " " + _LastName;
	}

	void SetGender(string Gender)
	{
		Gender = clsString::UpperAllLetters(Gender);

		if (Gender != "M" && Gender != "F" && Gender != "MALE" && Gender != "FEMALE")
			Gender = " ";

		if (Gender == "M" || Gender == "MALE")
			Gender = "Male";
		
		else if (Gender == "F" || Gender == "FEMALE")
			Gender = "Female";

		_Gender = Gender;
	}

	string GetGender()
	{
		return _Gender;
	}
	__declspec(property(get = GetGender, put = SetGender)) string Gender;

	void SetEmail(string Email)
	{
		_Email = Email;
	}

	string GetEmail()
	{
		return _Email;
	}
	__declspec(property(get = GetEmail, put = SetEmail)) string Email;

	void SetPhone(string Phone)
	{
		_Phone = Phone;
	}

	string GetPhone()
	{
		return _Phone;
	}
	__declspec(property(get = GetPhone, put = SetPhone)) string Phone;

};

