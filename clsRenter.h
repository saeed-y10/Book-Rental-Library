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

public:

	clsRenter(string FirstName,string LastName, string Email, string Phone, short RentDays, clsDate RentDate = clsDate())
		: clsPerson(FirstName, LastName, Email, Phone), _RentDate(RentDate), _ReturnDate()
	{
		_RentDate = RentDate;
		_ReturnDate = clsDate::IncreaceDateByNDays(RentDays, _RentDate);
		_RentDays = RentDays;

		if (DayPrice <= .0)
			DayPrice = 1;

		_DayPrice = DayPrice;
	}

	static clsRenter getEmptyRenterObject()
	{
		return clsRenter(" ", " ", " ", " ", 0, clsDate(1, 1, 1));
	}

	void setDayPrice(float DayPrice)
	{
		if (DayPrice <= .0)
			DayPrice = 1;

		_DayPrice = DayPrice;
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

	void AddDaysToRent(short Days)
	{
		if (IsDelayReturn())
			return;

		if (Days < 1)
			return;

		setRentDays(_RentDays + Days);
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
		return clsDate().IsDateAfterDate2(_ReturnDate);
	}

	short DelayDays()
	{
		if (_ReturnDate.IsDateBeforeDate2(clsDate()))
			return clsDate::GetDiffrenceInDays(_ReturnDate, clsDate());

		return 0;
	}

	float PenaltyPerDay()
	{
		return _DayPrice * 2;
	}

	float TotalPenalty()
	{
		return (float)DelayDays() * PenaltyPerDay();
	}

	float TotalBill()
	{
		return (float)(_RentDays * _DayPrice) + TotalPenalty();
	}

};