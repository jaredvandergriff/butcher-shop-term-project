//****************************************************************************************************
//
//			Project Title:		Short Line POS		
//	
//			Class Name:			Product
//
//			File:				Product.h
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
//			ClerkList.cpp, Station.h, Station.cpp, Product.cpp, ProductList.h, ProductList.cpp,
//			Customer.h, Customer.cpp, StationDriver.cpp, EntryFailException.h
//
//****************************************************************************************************

#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <fstream>

using namespace std;

//****************************************************************************************************

class Product
{
private:
	int prodNum;
	string prodName;
	double prodPrice;
	float prodWeight;
	float lbsInventory;

public:
	explicit Product(int = 0, string = "", double = 0.0, float = 0.0, float = 0.0);
	void setProdNum(int);
	void setProdName(const string&);
	void setProdPrice(double);
	void setProdWeight(float);
	void setProdLbsInventory(float);
	int getProdNum() const;
	string getProdName() const;
	double getProdPrice() const;
	float getProdWeight() const;
	float getProdLbsInventory() const;
	Product& operator = (const Product&);
	bool operator == (const Product&);
	bool operator >= (const Product&);
	friend ostream& operator << (ostream&, const Product&);
};
#endif