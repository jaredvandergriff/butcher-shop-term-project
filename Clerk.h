//****************************************************************************************************
//
//			Project Title:		Short Line POS		
//	
//			Class Name:			Clerk
//
//			File:				Clerk.h
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
//			Person.h, Person.cpp, Clerk.cpp, Manager.h, Manager.cpp, ClerkList.h, ClerkList.cpp,
//			Station.h, Station.cpp, Product.h, Product.cpp, ProductList.h, ProductList.cpp,
//			Customer.h, Customer.cpp, StationDriver.cpp, EntryFailException.h
//
//****************************************************************************************************

#ifndef CLERK_H
#define CLERK_H

#include "Person.h"
#include "Customer.h"
#include <fstream>

using namespace std;

//****************************************************************************************************

class Clerk: public Person
{
protected:
	int employeeID;
	string password;

public:
	explicit Clerk(int = 0, string = "", string = "", string = "");
	void setEmpID(int);
	void setPassword(const string&);
	int getEmpID() const;
	string getPassword() const;
	void iterateCustNum();
	bool operator < (const Clerk&);
	bool operator == (const Clerk&);
	virtual void print() const override;
	friend ostream& operator << (ostream&, const Clerk&);
};

#endif