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
//			ClerkList.cpp, Station.h, Product.h, Product.cpp, ProductList.h,
//			ProductList.cpp, Customer.h, Customer.cpp, StationDriver.cpp, EntryFailException.h
//
//****************************************************************************************************

#include "Station.h"

double Station::dailyTotal = 0.0;

Station::Station(int stationNum, bool availFlag)
{
	this->stationNum = stationNum;
	this->availFlag = availFlag;
}

//****************************************************************************************************

void Station::setStationNum(int stationNum)
{
	this->stationNum = stationNum;
}

//****************************************************************************************************

void Station::setCurrentCustomer(int currCustNum)
{
	this->currCustNum = currCustNum;
}

//****************************************************************************************************

void Station::setAvail(bool availFlag)
{
	this->availFlag = availFlag;
}

//****************************************************************************************************

int Station::getStationNum() const
{
	return stationNum;
}

//****************************************************************************************************

bool Station::getAvail() const
{
	return availFlag;
}

//****************************************************************************************************

int Station::getCurrentCustomer() const
{
	return currCustNum;
}

//****************************************************************************************************

double Station::getDailyTotal()
{
	return dailyTotal;
}

//****************************************************************************************************

void Station::setDailyTotal(double dT)
{
	dailyTotal = dT;
}

//****************************************************************************************************

void Station::incrementDailyTotal(double orderTotal)
{
	dailyTotal += orderTotal;
}

//****************************************************************************************************

void Station::recordDailyTotal()
{
	string time = getTime();
	fstream outFile;
	outFile.open("Dailytotal.txt", ios::out);
	if(!outFile)
		cerr << "Error opening Dailytotal.txt" << endl;
	outFile << Station::getDailyTotal() << endl
			<< time << endl;
}

//****************************************************************************************************

string Station::getTime()
{
	struct tm newtime;
	char am_pm[] = "AM";
	__time64_t long_time;
	char timebuf[29];
	errno_t err;
	
	// Get time as 64-bit integer.
	_time64(&long_time);
	// Convert to local time.
	err = _localtime64_s(&newtime, &long_time);
	if (err)
	{
		printf("Invalid argument to _localtime64_s.");
		exit(1);
	}
	if (newtime.tm_hour > 12) // Set up extension.
		strcpy_s(am_pm, sizeof(am_pm), "PM");
	if (newtime.tm_hour > 12) // Convert from 24-hour
		newtime.tm_hour -= 12; // to 12-hour clock.
	if (newtime.tm_hour == 0) // Set hour to 12 if midnight.
		newtime.tm_hour = 12;
			// Convert to an ASCII representation.
	err = asctime_s(timebuf, 26, &newtime);
	if (err)
	{
		cout << "Invalid argument to asctime_s.";
		exit(1);
	}
	timebuf[19] = '\0';
	strcat_s(timebuf, " ");
	strcat_s(timebuf, am_pm);
	return timebuf;
}