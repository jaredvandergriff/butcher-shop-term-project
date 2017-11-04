//****************************************************************************************************
//
//			Project Title:		Short Line POS		
//	
//			Class Name:			Person
//
//			File:				Person.cpp
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
//			Person.h, Clerk.h, Clerk.cpp, Manager.h, Manager.cpp, ClerkList.h, ClerkList.cpp,
//			Station.h, Station.cpp, Product.h, Product.cpp, ProductList.h, ProductList.cpp,
//			Customer.h, Customer.cpp, StationDriver.cpp, EntryFailException.h
//
//****************************************************************************************************

#include "Person.h"

//****************************************************************************************************

void Person::setEmpLName(const string& lName)
{
	this->lName = lName;
}

//****************************************************************************************************

void Person::setEmpFName(const string& fName)
{
	this->fName = fName;
}

//****************************************************************************************************

string Person::getEmpLName() const
{
	return lName;
}

//****************************************************************************************************

string Person::getEmpFName() const
{
	return fName;
}