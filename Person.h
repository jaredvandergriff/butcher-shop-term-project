//****************************************************************************************************
//
//			Project Title:		Short Line POS		
//	
//			Class Name:			Person
//
//			File:				Person.h
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
//			Person.cpp, Clerk.h, Clerk.cpp, Manager.h, Manager.cpp, ClerkList.h, ClerkList.cpp,
//			Station.h, Station.cpp, Product.h, Product.cpp, ProductList.h, ProductList.cpp,
//			Customer.h, Customer.cpp, StationDriver.cpp, EntryFailException.h
//
//****************************************************************************************************

#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iostream>

using namespace std;

//****************************************************************************************************

class Person
{
protected:
	string lName;
	string fName;

public:
	void setEmpLName(const string&);
	void setEmpFName(const string&);
	string getEmpLName() const;
	string getEmpFName() const;
	virtual void print() const = 0;
};

#endif