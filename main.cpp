// Book Rental Library.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Programmer: Saeed Lahmdi

#include <iostream>
#include "clsBook.h";
#include "clsLoginScreen.h"
#include "clsFindBookScreen.h"
#include "clsInputValidate.h"

using namespace std;

int main()
{

    clsLoginScreen::ShowLoginScreen();
    
    return 0;
}