//****************************************************************************************************
//
//			Project Title:		Short Line POS		
//	
//			Class Name:			Customer
//
//			File:				Customer.h
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
//			ClerkList.cpp, Station.h, Station.cpp, Product.h, Product.cpp, ProductList.h,
//			ProductList.cpp, Customer.cpp, StationDriver.cpp, EntryFailException.h
//
//****************************************************************************************************

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>

using namespace std;

//****************************************************************************************************

class Customer
{
private:
	float orderTotal;
	int assignedStation;
	int custNum;
	static int count;

public:
	explicit Customer(float = 0.0, int = 0);
	void setOrderTotal(float);
	void setStation(int);
	void setCustNum(int);
	float getOrderTotal() const;
	int getStation() const;
	int getCustNum() const;
	static bool setCount(int);
	static int getCount();
	static void resetCount();
};

#endif