//****************************************************************************************************
//
//			Project Title:		Short Line POS		
//	
//			Class Name:			EntryFailException
//
//			File:				EntryFailException.h
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
//			ClerkList.cpp, Station.cpp, Product.h, Product.cpp, ProductList.h,
//			ProductList.cpp, Customer.h, Customer.cpp, StationDriver.cpp
//
//****************************************************************************************************

#ifndef ENTRYFAILEXCEPTION_H
#define ENTRYFAILEXCEPTION_H

//****************************************************************************************************

#include <stdexcept>

using namespace std;

//****************************************************************************************************

class EntryFailException : public runtime_error
{
public:
	EntryFailException() : runtime_error
		("You have entered an incorrect value too many times. Exiting.\n"){}
};

#endif