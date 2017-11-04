//****************************************************************************************************
//
//			Project Title:		Short Line POS		
//	
//			Class Name:			Station
//
//			File:				Station.h
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
//			ProductList.cpp, Customer.h, Customer.cpp, StationDriver.cpp, EntryFailException.h
//
//****************************************************************************************************

#ifndef STATION_H
#define STATION_H

#include "ClerkList.h"
#include "ProductList.h"
#include "Customer.h"
#include <ctime>

//****************************************************************************************************

class Station
{
private:
	int stationNum;
	bool availFlag;
	int currCustNum;
	static double dailyTotal;

public:
	explicit Station(int = 0, bool = true);
	void setStationNum(int);
	void setAvail(bool);
	void setCurrentCustomer(int);
	int getStationNum() const;
	bool getAvail() const;
	int getCurrentCustomer() const;
	static double getDailyTotal();
	static void setDailyTotal(double);
	static void incrementDailyTotal(double);
	void recordDailyTotal();
	string getTime();
};

#endif