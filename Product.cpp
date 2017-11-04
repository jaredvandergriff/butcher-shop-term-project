//****************************************************************************************************
//
//			Project Title:		Short Line POS		
//	
//			Class Name:			Product
//
//			File:				Product.cpp
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
//			ClerkList.cpp, Station.h, Station.cpp, Product.h, ProductList.h, ProductList.cpp,
//			Customer.h, Customer.cpp, StationDriver.cpp, EntryFailException.h
//
//****************************************************************************************************

#include "Product.h"

//****************************************************************************************************

Product::Product(int prodNum, string prodName, double prodPrice, float prodWeight, float lbsInventory)
{
	this -> prodNum = prodNum;
	this -> prodName = prodName;
	this -> prodPrice = prodPrice;
	this -> prodWeight = prodWeight;
	this -> lbsInventory = lbsInventory;
}

//****************************************************************************************************

void Product::setProdNum(int prodNum)
{
	this -> prodNum = prodNum;
}

//****************************************************************************************************

void Product::setProdName(const string& prodName)
{
	this -> prodName = prodName;
}

//****************************************************************************************************

void Product::setProdPrice(double prodPrice)
{
	this -> prodPrice = prodPrice;
}

//****************************************************************************************************

void Product::setProdWeight(float prodWeight)
{
	this -> prodWeight = prodWeight;
}

//****************************************************************************************************

void Product::setProdLbsInventory(float lbsInventory)
{
	this -> lbsInventory = lbsInventory;
}

//****************************************************************************************************

int Product::getProdNum() const
{
	return prodNum;
}

//****************************************************************************************************

string Product::getProdName() const
{
	return prodName;
}

//****************************************************************************************************

double Product::getProdPrice() const
{
	return prodPrice;
}

//****************************************************************************************************

float Product::getProdWeight() const
{
	return prodWeight;
}

//****************************************************************************************************

float Product::getProdLbsInventory() const
{
	return lbsInventory;
}

//****************************************************************************************************

Product& Product::operator = (const Product& p)
{
	this -> prodNum = p.prodNum;
	this -> prodName = p.prodName;
	this -> prodPrice = p.prodPrice;
	this -> prodWeight = p.prodWeight;
	this -> lbsInventory = p.lbsInventory;
	return *this;
}

//****************************************************************************************************

bool Product::operator == (const Product& p)
{
	if(prodNum == p.prodNum)
		return true;
	else
		return false;
}
	
//****************************************************************************************************

bool Product::operator >= (const Product& p)
{
	if(prodNum >= p.prodNum)
		return true;
	else
		return false;
}

//****************************************************************************************************

ostream& operator << (ostream& out, const Product& p)
{
	out << p.prodNum << endl << p.prodName << endl << p.prodPrice << endl << p.lbsInventory 
		 << endl << endl;
	return out;
}