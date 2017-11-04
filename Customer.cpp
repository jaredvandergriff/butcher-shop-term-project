//****************************************************************************************************
//
//			Project Title:		Short Line POS		
//	
//			Class Name:			Customer
//
//			File:				Customer.cpp
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
//			ProductList.cpp, Customer.h, StationDriver.cpp, EntryFailException.h
//
//****************************************************************************************************

#include "Customer.h"
#include <iostream>

int Customer::count = -1;

//****************************************************************************************************

Customer::Customer(float orderTotal, int assignedStation)
{
	count++;
	this->orderTotal = orderTotal;
	this->assignedStation = assignedStation;
	if(count >= 200)
		count = 1;
	custNum = count;
}

//****************************************************************************************************

void Customer::setOrderTotal(float orderTotal)
{
	this->orderTotal = orderTotal;
}
	
//****************************************************************************************************

void Customer::setStation(int assignedStation)
{
	this->assignedStation = assignedStation;
}

//****************************************************************************************************

void Customer::setCustNum(int custNum)
{
	this->custNum = custNum;
}

//****************************************************************************************************

float Customer::getOrderTotal() const
{
	return orderTotal;
}
	
//****************************************************************************************************

int Customer::getStation() const
{
	return assignedStation;
}

//****************************************************************************************************

int Customer::getCustNum() const
{
	return custNum;
}
	
//****************************************************************************************************

bool Customer::setCount(int n)
{
	if(n < 0 || n > 199)
		return false;
	count = n;
	return true;
}
	
//****************************************************************************************************

int Customer::getCount()
{
	return count;
}

//****************************************************************************************************

void Customer::resetCount()
{
	count = 0;
}