//****************************************************************************************************
//
//			Project Title:		Short Line POS		
//	
//			Class Name:			ClerkList
//
//			File:				ClerkList.cpp
//
//			Student:			Jared Vandergriff
//
//			Course Name:		COSC 4260
//
//			Date:				May 11, 2017
//
//
//			Description: 
//			This point of sale program allows users to login to a station in order to process
//			customer orders, maintain inventory, maintain an employee list, and calculate sales.
//
//			Other Files included: 
//			Person.h, Person.cpp, Clerk.h, Clerk.cpp, Manager.h, Manager.cpp, ClerkList.h,
//			Station.h, Station.cpp, Product.h, Product.cpp, ProductList.h, ProductList.cpp,
//			Customer.h, Customer.cpp, StationDriver.cpp, EntryFailException.h
//
//****************************************************************************************************

#include "ClerkList.h"
#include <iostream>

//****************************************************************************************************

bool ClerkList::readClerks()
{
	Clerk Clerk;
	int num;
	string lname;
	string fname;
	string pass;
	
	fstream inFile("ClerkList.txt", ios::in);
	if(!inFile)
		return false;
	else
	{
		inFile >> num;
		inFile.ignore();
		getline(inFile, lname);
		getline(inFile, fname);
		getline(inFile, pass);

		Clerk.setEmpID(num);
		Clerk.setEmpLName(lname);
		Clerk.setEmpFName(fname);
		Clerk.setPassword(pass);

		while(!inFile.eof())
		{
			CList.push_back(Clerk);
			inFile >> num;
			inFile.ignore();
			getline(inFile, lname);
			getline(inFile, fname);
			getline(inFile, pass);

			Clerk.setEmpID(num);
			Clerk.setEmpLName(lname);
			Clerk.setEmpFName(fname);
			Clerk.setPassword(pass);
		}
		return true;
	}
	inFile.close();
}

//****************************************************************************************************

bool ClerkList::validateClerk(Clerk& c)
{
	if(c.getEmpID() == 1111 && c.getPassword() == "ADMIN") //Check for default admin login
		return true;
	list<Clerk>::iterator i;
	for(i = CList.begin(); i != CList.end(); ++i)
	{
		if(*i == c && (i->getPassword().compare(c.getPassword()) == 0))
		{
			c.setEmpLName(i->getEmpLName());
			c.setEmpFName(i->getEmpFName());
			return true;
		}
	}
	return false;
}

//****************************************************************************************************

bool ClerkList::addClerk(const Clerk& c)
{
	bool added = true;
	try
	{
		CList.push_back(c);
	}
	catch(bad_alloc)
	{
		added = false;
	}
	return added;
}

//****************************************************************************************************

bool ClerkList::removeClerk(Clerk c)
{
	bool removed = false;
	if(lookup(c))
	{
		CList.remove(c);
		removed = true;
	}
	return removed;
}

//****************************************************************************************************

bool ClerkList::lookup(Clerk& c)
{
	bool success = false;
	list<Clerk>::iterator i;
	for(i = CList.begin(); i != CList.end(); ++i)
	{
		if(i->getEmpID() == c.getEmpID())
		{
			c.setEmpLName(i->getEmpLName());
			c.setEmpFName(i->getEmpFName());
			c.setPassword(i->getPassword());
			success = true;
		}
	}
	return success;
}

//****************************************************************************************************

bool ClerkList::writeClerks()
{
	fstream outFile("ClerkList.txt", ios::out);
	if(!outFile)
		return false;
	else
	{
		CList.sort();
		copy(CList.begin(), CList.end(), ostream_iterator<Clerk>(outFile));
		outFile.close();
		return true;
	}
	outFile.close();
}