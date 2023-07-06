#pragma once


#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include "clsPerson.h"
#include "clsRenter.h"
#include "clsDate.h"
#include "clsString.h"
#include "clsUtil.h"

using namespace std;

class clsBook
{

private:

	// enum declaration
	enum enCategorys;
	
	// all book modes
	enum enMode
	{
		eEmpty = 0,
		eNew = 1,
		eUpdate = 2,
	};

	// convert book record to string
	static string _ConvertBookObjectToLine(clsBook Book, string Seperator = "#//#")
	{
		string Line = "";

		Line = to_string(Book._Available) + Seperator;
		Line += to_string(Book._ID) + Seperator;
		Line += clsUtil::EncryptText(Book._Name) + Seperator;
		Line += clsUtil::EncryptText(Book._Author) + Seperator;
		Line += to_string(Book._Category) + Seperator;
		Line += to_string(Book.DayPrice) + Seperator;
		Line += clsUtil::EncryptText(Book.Renter.FirstName) + Seperator;
		Line += clsUtil::EncryptText(Book.Renter.LastName) + Seperator;
		Line += clsUtil::EncryptText(Book.Renter.Email) + Seperator;
		Line += clsUtil::EncryptText(Book.Renter.Phone) + Seperator;
		Line += clsUtil::EncryptText(to_string(Book.Renter.RentDays)) + Seperator;
		Line += clsUtil::EncryptText(Book.Renter.RentDate());

		return Line;
	}
	
	// converts string to book record
	static clsBook _ConvertLineToBookObject(string Line, string Seperator = "#//#")
	{
		vector<string> vLine = clsString::Split(Line, Seperator);
		
		clsRenter Renter(clsUtil::DecryptText(vLine[6]), clsUtil::DecryptText(vLine[7]), clsUtil::DecryptText(vLine[8]), clsUtil::DecryptText(vLine[9]), stoi(clsUtil::DecryptText(vLine[10])), clsDate(clsUtil::DecryptText(vLine[11])));
		clsBook Book(enMode::eUpdate, stoi(vLine[1]), clsUtil::DecryptText(vLine[2]), clsUtil::DecryptText(vLine[3]), (enCategorys)stoi(vLine[4]), stof(vLine[5]), Renter);

		Book._Available = stoi(vLine[0]);

		return Book;
	}
	
	// load all books from file
	static vector<clsBook> _LoadBooksDataFromFile(bool OnlyAvailable = false, string FileName = "Books.txt")
	{
		vector<clsBook> vBooks;

		fstream File;

		File.open(FileName, ios::in);

		if (File.is_open())
		{
			string Line = "";

			while (getline(File, Line))
			{
				clsBook Book = _ConvertLineToBookObject(Line);

				if (OnlyAvailable)
				{
					if (Book.IsAvailable())
					{
						vBooks.push_back(Book);
					}
				}

				else
				{
					vBooks.push_back(Book);
				}
			}

			File.close();
		}

		return vBooks;
	}

	// load books dat by category from file
	static vector<clsBook> _LoadBooksDataFromFile(enCategorys Category, bool OnlyAvailable = false, string FileName = "Books.txt")
	{
		vector<clsBook> vBooks;

		fstream File;

		File.open(FileName, ios::in);

		if (File.is_open())
		{
			string Line = "";

			while (getline(File, Line))
			{
				clsBook Book = _ConvertLineToBookObject(Line);

				if (Book.Category == Category)
				{
					if (OnlyAvailable)
					{
						if (Book.IsAvailable())
						{
							vBooks.push_back(Book);
						}
					}

					else
					{
						vBooks.push_back(Book);
					}
				}

			}

			File.close();
		}

		return vBooks;
	}

	// load books dat by author name from file
	static vector<clsBook> _LoadBooksDataFromFile(string Author, bool OnlyAvailable = false, string FileName = "Books.txt")
	{
		vector<clsBook> vBooks;

		fstream File;

		File.open(FileName, ios::in);

		if (File.is_open())
		{
			string Line = "";

			while (getline(File, Line))
			{
				clsBook Book = _ConvertLineToBookObject(Line);

				if (Book.Author == Author)
				{
					if (OnlyAvailable)
					{
						if (Book.IsAvailable())
						{
							vBooks.push_back(Book);
						}
					}

					else
					{
						vBooks.push_back(Book);
					}
					
				}

			}

			File.close();
		}

		return vBooks;
	}

	// save books data to file
	static void _SaveBooksDataToFile(vector<clsBook> vBooks,  string FileName = "Books.txt")
	{
		fstream File;

		File.open(FileName, ios::out);

		if (File.is_open())
		{
			string Line;

			for (clsBook &Book : vBooks)
			{
				if (Book.IsAvailable())
					Book.Renter = clsRenter::getEmptyRenterObject();

				if (Book._MarkForDelete == false)
				{
					Line = _ConvertBookObjectToLine(Book);

					File << Line << endl;
				}

			}

			File.close();
		}

	}

	// add new record to file
	static void _AddDataLineToFile(string DataLine, string FileName)
	{
		fstream File;

		File.open(FileName, ios::app | ios::out);

		if (File.is_open())
		{
			File << DataLine << endl;

			File.close();
		}
	}

	// return empty book object
	static clsBook _getEmptyBookObject()
	{
		return clsBook(enMode::eEmpty, 0, "", "", enCategorys::eOthers, 0, clsRenter::getEmptyRenterObject());
	}

	// update current book and update book object in database
	void _Update()
	{
		vector<clsBook> vBooks = _LoadBooksDataFromFile();

		for (clsBook &Book : vBooks)
		{
			if (Book.ID() == ID())
			{
				Book = *this;
				break;
			}
		}

		_SaveBooksDataToFile(vBooks);
	}

	// add new book object to database
	void _AddNew()
	{
		if (IsAvailable())
			Renter = clsRenter::getEmptyRenterObject();

		_AddDataLineToFile(_ConvertBookObjectToLine(*this), "Books.txt");
	}
	
	enMode _Mode;
	int _ID;
	string _Name;
	enCategorys _Category;
	string _Author;
	float _DayPrice;
	bool _Available;
	bool _MarkForDelete;

public:

	// constructor
	clsBook(enMode Mode, int ID, string Name, string Author, enCategorys Categorys, float DayPrice, clsRenter Renter = clsRenter::getEmptyRenterObject())
		: Renter(Renter)
	{
		if (Name == "" || Name == " ")
			Author = "Unknown";

		if (Author == "" || Author == " ")
			Author = "Unknown";

		if (DayPrice <= .0)
			DayPrice = 1;

		this->Renter.DayPrice = DayPrice;
		_Mode = Mode;
		_ID = ID;
		_Name = Name;
		_Category = Categorys;
		_Author = Author;
		_DayPrice = DayPrice;
		Renter.DayPrice = _DayPrice;
		_Available = true;
		_MarkForDelete = false;
	}

	// renter object
	clsRenter Renter;

	// all books categorys
	enum enCategorys
	{
		eNovel = 1,
		eSciences = 2,
		eHistory = 3,
		eReligious = 4,
		eOthers = 5,
	};

	// all save result
	enum enSaveResult
	{
		svFaildEmpty = 0,
		svSucceeded = 1,
		svFaildIDExist = 2,
		svFaildINotExist = 3,
	};

	// delete the book from database
	bool Delete()
	{
		vector<clsBook> vBooks = _LoadBooksDataFromFile();

		for (clsBook& Book : vBooks)
		{
			if (Book.ID() == ID())
			{
				Book._MarkForDelete = true;
				break;
			}
		}

		*this = _getEmptyBookObject();

		_SaveBooksDataToFile(vBooks);

		return true;
	}

	// method to update or add new book to database
	enSaveResult Save()
	{
		switch (_Mode)
		{
		case clsBook::eEmpty:
		{
			return enSaveResult::svFaildEmpty;
		}

		case clsBook::eNew:
		{
			if (IsIDNumberExist(ID()))
			{
				return enSaveResult::svFaildIDExist;
			}

			else
			{
				_AddNew();

				_Mode = enMode::eUpdate;

				return enSaveResult::svSucceeded;
			}
		}

		case clsBook::eUpdate:
		{
			/*if (!IsBookExist(ID()))
			{
				return enSaveResult::svFaildIDnotExist;
			}

			else
			{*/
			
			_Update();

			return enSaveResult::svSucceeded;
			
			//}
		}

		default:
		{
			return enSaveResult::svFaildEmpty;
		}

		}
	}

	// search for book by id and return clsbook if Book is found or return empty clsbook 
	static clsBook Find(int ID)
	{
		fstream File;

		File.open("Books.txt", ios::in);

		if (File.is_open())
		{
			string Line = "";

			while (getline(File, Line))
			{
				clsBook Book = _ConvertLineToBookObject(Line);

				if (Book.ID() == ID)
				{
					File.close();

					return Book;
				}
			}

			File.close();
		}

		return _getEmptyBookObject();
	}

	// Find by book name and return clsBook object
	static vector<clsBook> Find(string BookName)
	{
		fstream File;

		File.open("Books.txt", ios::in);

		vector<clsBook> vBooks;

		if (File.is_open())
		{
			string Line = "";

			while (getline(File, Line))
			{
				clsBook Book = _ConvertLineToBookObject(Line);

				if (Book.Name == BookName)
				{
					File.close();

					vBooks.push_back(Book);
				}
			}

			File.close();
		}

		return vBooks;
	}

	// Find by author name and return clsBook object
	static vector<clsBook> FindByAuthor(string AuthorName)
	{
		vector<clsBook> vBooks;

		fstream File;

		File.open("Books.txt", ios::in);

		if (File.is_open())
		{
			string Line = "";

			while (getline(File, Line))
			{
				clsBook Book = _ConvertLineToBookObject(Line);

				if (Book.Author == AuthorName)
				{
					vBooks.push_back(Book);
				}

			}

			File.close();
		}

		return vBooks;
	}
	
	// check is book id exist in database and return true or false
	static bool IsIDNumberExist(int ID)
	{
		return !(Find(ID).IsEmpty());
	}

	// return empty clsbook object
	static clsBook getNewBookObject(int ID)
	{
		return clsBook(enMode::eNew, ID, "", "", enCategorys::eOthers, 1, clsRenter::getEmptyRenterObject());
	}

	// Check is book mode is empty
	bool IsEmpty()
	{
		return _Mode == enMode::eEmpty;
	}

	// Check is book deleted
	bool IsMarkedForDelete()
	{
		return _MarkForDelete;
	}

	// clsBook object modes
	enMode Mode()
	{
		return _Mode;
	}

	// read only property
	int ID()
	{
		return _ID;
	}

	// set property
	void setName(string Name)
	{
		_Name = Name;
	}

	// get property
	string getName()
	{
		return _Name;
	}
	__declspec(property(get = getName, put = setName)) string Name;

	// set property
	void setCategory(enCategorys Category)
	{
		_Category = Category;
	}

	// get property
	enCategorys getCategory()
	{
		return _Category;
	}
	__declspec(property(get = getCategory, put = setCategory)) enCategorys Category;

	// get book category name
	string getCategoryName()
	{
		switch (_Category)
		{
		case enCategorys::eNovel:
			return "Novel";

		case enCategorys::eHistory:
			return "History";

		case enCategorys::eReligious:
			return "Religious";

		case enCategorys::eSciences:
			return "Sciences";

		default:
			return "Others";
		}
	}

	// set property
	void setAuthor(string Author)
	{
		_Author = Author;
	}

	// get property
	string getAuthor()
	{
		return _Author;
	}
	__declspec(property(get = getAuthor, put = setAuthor)) string Author;

	// set property
	void setDayPrice(float DayPrice)
	{
		if (DayPrice <= .0)
			DayPrice = 1;

		_DayPrice = DayPrice;
		Renter.DayPrice = DayPrice;
	}

	// get property
	float getDayPrice()
	{
		return _DayPrice;
	}
	__declspec(property(get = getDayPrice, put = setDayPrice)) float DayPrice;

	// check is book available
	bool IsAvailable()
	{
		return _Available;
	}

	// rent a book
	bool RentBook(string FirstName, string LastName, string Email, string Phone, short RentDays)
	{
		if (!IsAvailable())
			return false;

		Renter = clsRenter(FirstName, LastName, Email, Phone, RentDays);
		Renter.DayPrice = _DayPrice;
		_Available = false;

		_Update();

		return true;
	}

	// return the rented book
	bool ReturnBook()
	{
		if (IsAvailable())
			return false;

		_Available = true;
		Renter = clsRenter::getEmptyRenterObject();

		_Update();

		return true;
	}

	// return all books in database
	static vector<clsBook> getBooksList(bool OnlyAvailable = false)
	{
		return _LoadBooksDataFromFile(OnlyAvailable);
	}

	// return all books in database by category
	static vector<clsBook> getBooksList(enCategorys Category, bool OnlyAvailable = false)
	{
		return _LoadBooksDataFromFile(Category, OnlyAvailable);
	}

	// return all books in database by author name
	static vector<clsBook> getBooksList(string Author, bool OnlyAvailable = false)
	{
		return _LoadBooksDataFromFile(Author, OnlyAvailable);
	}

	static vector<clsBook> getRentedBooksList()
	{
		vector<clsBook> vBooks;

		fstream File;

		File.open("Books.txt", ios::in);

		if (File.is_open())
		{
			string Line = "";

			while (getline(File, Line))
			{
				clsBook Book = _ConvertLineToBookObject(Line);

				if (!Book.IsAvailable())
				{
					vBooks.push_back(Book);
				}
			}

			File.close();
		}

		return vBooks;
	}

};

