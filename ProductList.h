//****************************************************************************************************
//
//			Project Title:		Short Line POS		
//	
//			Class Name:			Product
//
//			File:				ProductList.h
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
//			ClerkList.cpp, Station.h, Station.cpp, Product.h, Product.cpp, ProductList.cpp,
//			Customer.h, Customer.cpp, StationDriver.cpp, EntryFailException.h
//
//****************************************************************************************************

#ifndef PRODUCTLIST_H
#define PRODUCTLIST_H

#include <list>
#include <algorithm>
#include "Product.h"

//****************************************************************************************************

class ProductList
{
private:
	list<Product> PList;
	int prodCount;

public:
	explicit ProductList(int = 0);
	bool readProducts();
	bool addProduct(Product&);
	void displayProducts();
	bool findProduct(Product &);
	bool editProduct(Product &);
	bool removeProduct(const Product&);
	bool removeAll();
	bool removeInventory(ProductList&);
	bool writeProducts();
	bool empty();
	fstream& writeReceipt(fstream&);
	int getProdCount() const;
};

#endif