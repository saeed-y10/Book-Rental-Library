#pragma once

#include <iostream>
#include "clsDate.h"
#include "clsString.h"

using namespace std;

class clsInputValidate
{
public:

	template <typename T> static bool IsNumberBetween(T Number, T From, T To)
	{
		return (Number >= From && Number <= To);
	}

	template <typename T> static T ReadNumber(string ErrorMessage)
	{
		T Number = 0;

		while (!(cin >> Number))
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << ErrorMessage;
		}

		return Number;
	}

	template <typename T> static T ReadNumberBetween(T From, T To, string ErrorMessage)
	{
		T Number = 0;

		Number = ReadNumber<T>(ErrorMessage);

		while (!IsNumberBetween(Number, From, To))
		{
			cout << ErrorMessage;
			Number = ReadNumber<T>(ErrorMessage);
		}

		return Number;
	}

	static bool IsDateBetween(clsDate Date, clsDate From, clsDate To)
	{
		//if Date >= From && Date <= To
		/*if ((clsdate::IsDateAfterDate2(Date, From) || clsdate::IsDateEqualDate2(Date, From))
			&&
			(clsdate::IsDateBeforeDate2(Date, To) || clsdate::IsDateEqualDate2(Date, To)))
			return true;

		//if Date >= To && Date <= From
		if ((clsdate::IsDateAfterDate2(Date, To) || clsdate::IsDateEqualDate2(Date, To))
			&&
			(clsdate::IsDateBeforeDate2(Date, From) || clsdate::IsDateEqualDate2(Date, From)))
			return true;

		return false;*/

		if (clsDate::IsDateAfterDate2(From, To))
			clsDate::Swap(From, To);

		return !(clsDate::IsDateBeforeDate2(Date, From) || clsDate::IsDateAfterDate2(Date, To));
	}

	static bool IsValidDate(short Day, short Month, short Year)
	{
		return clsDate::IsValid(Day, Month, Year);
	}

	static bool IsValidDate(clsDate Date)
	{
		return clsDate::IsValid(Date);
	}

	static string ReadString()
	{
		string str;

		do
		{
			getline(cin >> ws, str);

		} while (str == "");

		return str;
	}

	static clsDate ReadDate(string ErrorMessage)
	{
		string Date;

		do
		{
			cout << "Enter Date Like 1/2/2020? ";
			Date = ReadString();

		} while (IsValidDate(clsDate(Date)));

		return clsDate(Date);
	}

	/*static bool IsNumberBetween(short Number, short From, short To)
	{
		return (Number >= From && Number <= To);
	}

	static bool IsNumberBetween(int Number, int From, int To)
	{
		return (Number >= From && Number <= To);
	}

	static bool IsNumberBetween(float Number, float From, float To)
	{
		return (Number >= From && Number <= To);
	}

	static bool IsNumberBetween(double Number, double From, double To)
	{
		return (Number >= From && Number <= To);
	}*/

	/*static int ReadIntNumber(string ErrorMessage)
	{
		int Number = 0;

		while (!(cin >> Number))
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << ErrorMessage;
		}

		return Number;
	}

	static int ReadIntNumberBetween(int From, int To, string ErrorMessage)
	{
		int Number = 0;

		Number = ReadIntNumber(ErrorMessage);

		while (!IsNumberBetween(Number, From, To))
		{
			cout << ErrorMessage;
			Number = ReadIntNumber(ErrorMessage);
		}

		return Number;
	}

	static double ReadDbNumber(string ErrorMessage)
	{
		double Number = 0;

		while (!(cin >> Number))
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << ErrorMessage;
		}

		return Number;
	}

	static double ReadDbNumberBetween(double From, double To, string ErrorMessage)
	{
		double Number = 0;

		Number = ReadDbNumber(ErrorMessage);

		while (!IsNumberBetween(Number, From, To))
		{
			cout << ErrorMessage;
			Number = ReadDbNumber(ErrorMessage);
		}

		return Number;
	}*/

};

