// Book Rental Library.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Programmer: Saeed Lahmdi

#include <iostream>
#include "clsBook.h";

using namespace std;

int main()
{
    clsBook Book = clsBook::Find(2);

    if (Book.IsEmpty())
        cout << "Book is not found.\n";

    else
    {
        cout << "Name  : " << Book.Name << endl;
        cout << "Author: " << Book.Author << endl;
    }

    return 0;
}