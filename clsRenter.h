#pragma once

#include <string>
#include "clsPerson.h"
#include "clsDate.h"

using namespace std;

class clsRenter : public clsPerson
{

private:

	short _RentDays;
	float _DayPrice;
	clsDate _RentDate;
	clsDate _ReturnDate;
	float _PenaltyPerDay;

public:

	clsRenter(string FirstName, string MiddleName, string LastName, string Email, string Phone, short RentDays, clsDate RentDate = clsDate())
		: clsPerson(FirstName, MiddleName, LastName, Email, Phone), _RentDate(RentDate), _ReturnDate()
	{
		_RentDate = RentDate;
		_ReturnDate = clsDate::IncreaceDateByNDays(RentDays, _RentDate);
		_RentDays = RentDays;
		_DayPrice = 0;
		_PenaltyPerDay = _DayPrice * 2;
	}

	static clsRenter getEmptyRenterObject()
	{
		return clsRenter(" ", " ", " ", " ", " ", 0, clsDate(1, 1, 1));
	}

	void setDayPrice(float DayPrice)
	{
		if (DayPrice <= .0)
			DayPrice = 1;

		_DayPrice = DayPrice;
		_PenaltyPerDay = _DayPrice * 2;
	}

	float getDayPrice()
	{
		return _DayPrice;
	}
	__declspec(property(get = getDayPrice, put = setDayPrice)) float DayPrice;

	short getRentDays()
	{
		return _RentDays;
	}

	void setRentDays(short RentDays)
	{
		_RentDays = RentDays;
		_ReturnDate = clsDate::IncreaceDateByNDays(_RentDays, _RentDate);
	}
	__declspec(property(get = getRentDays, put = setRentDays)) short RentDays;

	string RentDate()
	{
		return _RentDate.ToString();
	}

	string ReturnDate()
	{
		return _ReturnDate.ToString();
	}

	short DaysToReturn()
	{
		if (!clsDate().IsDateBeforeDate2(_ReturnDate))
			return 0;

		return  clsDate().GetDiffrenceInDays(_ReturnDate);
	}

	bool IsDelayReturn()
	{
		clsDate CurrentDate;

		return CurrentDate.IsDateAfterDate2(_ReturnDate);
	}

	short DelayDays()
	{
		short DelayDays = clsDate::GetDiffrenceInDays(_ReturnDate, clsDate());

		return (DelayDays < 0) ? 0 : DelayDays;
	}

	float PenaltyPerDay()
	{
		return _PenaltyPerDay;
	}

	float TotalDelayPenalty()
	{
		return (float)DelayDays() * PenaltyPerDay();
	}

	float TotalPrice()
	{
		return (float)_RentDays * _DayPrice;
	}

};