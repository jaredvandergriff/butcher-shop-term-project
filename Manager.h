//****************************************************************************************************
//
//			Project Title:		Short Line POS		
//	
//			Class Name:			Manager
//
//			File:				Manager.h
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
//			Person.h, Person.cpp, Clerk.h, Clerk.cpp, Manager.cpp, ClerkList.h, ClerkList.cpp,
//			Station.h, Station.cpp, Product.h, Product.cpp, ProductList.h, ProductList.cpp,
//			Customer.h, Customer.cpp, StationDriver.cpp, EntryFailException.h
//
//****************************************************************************************************

#ifndef MANAGER_H
#define MANAGER_H

#include "Clerk.h"
#include "Customer.h"
#include "Station.h"

//****************************************************************************************************

class Manager: public Clerk
{
public:
	explicit Manager(int = 0, string = "", string = "", string = "");
	int getCustomerNum() const;
	bool setCustomerNum(int);
	bool resetCustomerNum();
	virtual void print() const override;
};

#endif