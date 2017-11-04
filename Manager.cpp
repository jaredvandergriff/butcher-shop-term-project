//****************************************************************************************************
//
//			Project Title:		Short Line POS		
//	
//			Class Name:			Manager
//
//			File:				Manager.cpp
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
//			Person.h, Person.cpp, Clerk.h, Clerk.cpp, Manager.h, ClerkList.h, ClerkList.cpp,
//			Station.h, Station.cpp, Product.h, Product.cpp, ProductList.h, ProductList.cpp,
//			Customer.h, Customer.cpp, StationDriver.cpp, EntryFailException.h
//
//****************************************************************************************************

#include "Manager.h"

//****************************************************************************************************

Manager::Manager(int employeeID, string lName, string fName, string password)
{
	this->employeeID = employeeID;
	this->lName = lName;
	this->fName = fName;
	this->password = password;
}

//****************************************************************************************************

int Manager::getCustomerNum() const
{
	return Customer::getCount();
}

//****************************************************************************************************

bool Manager::resetCustomerNum()
{
	Customer::resetCount();
	if(Customer::getCount() == 0)
		return true;
	return false;
}

//****************************************************************************************************

bool Manager::setCustomerNum(int n)
{
	if(Customer::setCount(n))
		return true;
	return false;
}

//****************************************************************************************************

void Manager::print() const
{
	cout << "Manager ID: " << employeeID << endl;
	cout << "Name: " << fName << " " << lName << endl << endl;
}