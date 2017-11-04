//****************************************************************************************************
//
//			Project Title:		Short Line POS		
//	
//			Class Name:			Clerk
//
//			File:				Clerk.cpp
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
//			Person.h, Person.cpp, Clerk.h, Manager.h, Manager.cpp, ClerkList.h, ClerkList.cpp,
//			Station.h, Station.cpp, Product.h, Product.cpp, ProductList.h, ProductList.cpp,
//			Customer.h, Customer.cpp, StationDriver.cpp, EntryFailException.h
//
//****************************************************************************************************

#include "Clerk.h"

//****************************************************************************************************

Clerk::Clerk(int employeeID, string lName, string fName, string password)
{
	this->employeeID = employeeID;
	this->lName = lName;
	this->fName = fName;
	this->password = password;
}

//****************************************************************************************************

void Clerk::setEmpID(int employeeID)
{
	this->employeeID = employeeID;
}
	
//****************************************************************************************************

void Clerk::setPassword(const string& password)
{
	this->password = password;
}

//****************************************************************************************************

int Clerk::getEmpID() const
{
	return employeeID;
}

//****************************************************************************************************

string Clerk::getPassword() const
{
	return password;
}

//****************************************************************************************************

void Clerk::iterateCustNum()
{
	int i = Customer::getCount();
	Customer::setCount(++i);
}

//****************************************************************************************************

bool Clerk::operator<(const Clerk& c)
{
	if(employeeID < c.employeeID)
		return true;
	else
		return false;
}

//****************************************************************************************************

bool Clerk::operator==(const Clerk& c)
{
	if(employeeID == c.employeeID)
		return true;
	else
		return false;
}

//****************************************************************************************************

void Clerk::print() const
{
	cout << "Clerk ID: " << employeeID << endl;
	cout << "Name: " << fName << " " << lName << endl << endl;
}

//****************************************************************************************************

ostream& operator<< (ostream& out, const Clerk& c)
{
	out << c.employeeID << endl << c.lName << endl << c.fName << endl << c.password << endl;
	return out;
}