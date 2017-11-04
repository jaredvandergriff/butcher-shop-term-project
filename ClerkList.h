//****************************************************************************************************
//
//			Project Title:		Short Line POS		
//	
//			Class Name:			ClerkList
//
//			File:				ClerkList.h
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
//			Person.h, Person.cpp, Clerk.h, Clerk.cpp, Manager.h, Manager.cpp, ClerkList.cpp,
//			Station.h, Station.cpp, Product.h, Product.cpp, ProductList.h, ProductList.cpp,
//			Customer.h, Customer.cpp, StationDriver.cpp, EntryFailException.h
//
//****************************************************************************************************

#ifndef CLERKLIST_H
#define CLERKLIST_H

#include <list>
#include <algorithm>
#include "Manager.h"

//****************************************************************************************************

class ClerkList
{
private:
	list<Clerk> CList;

public:
	bool readClerks();
	bool validateClerk(Clerk&);
	bool addClerk(const Clerk&);
	bool removeClerk(Clerk);
	bool lookup(Clerk&);
	bool writeClerks();
};

#endif