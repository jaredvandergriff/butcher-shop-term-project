//****************************************************************************************************
//
//			Project Title:		Short Line POS		
//	
//			Class Name:			Product
//
//			File:				ProductList.cpp
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
//			Customer.h, Customer.cpp, StationDriver.cpp, EntryFailException.h
//
//****************************************************************************************************

#include "ProductList.h"

#include <iostream>
#include <iomanip>

//****************************************************************************************************

ProductList::ProductList(int prodCount)
{
	this -> prodCount = prodCount;
}

//****************************************************************************************************

bool ProductList::readProducts()
{
	Product product;
	int num;
	string name;
	float price;
	float lbsInventory;

	fstream inFile("ProdList.txt", ios::in);
	if(!inFile)
		return false;
	else
	{
		inFile >> num;
		inFile.ignore();
		getline(inFile, name);
		inFile >> price;
		inFile >> lbsInventory;

		product.setProdNum(num);
		product.setProdName(name);
		product.setProdPrice(price);
		product.setProdLbsInventory(lbsInventory);

		while(!inFile.eof())
		{
			PList.push_back(product);
			prodCount++;
			inFile >> num;
			inFile.ignore();
			getline(inFile, name);
			inFile >> price;
			inFile >> lbsInventory;

			product.setProdNum(num);
			product.setProdName(name);
			product.setProdPrice(price);
			product.setProdLbsInventory(lbsInventory);
		}
		return true;
	}
	inFile.close();
}

//****************************************************************************************************

bool ProductList::addProduct(Product& p)
{
	bool added = true;
	try
	{
		PList.push_back(p);
	}
	catch(bad_alloc)
	{
		added = false;
	}
	if(added)
		prodCount++;
	return added;
}

//****************************************************************************************************

void ProductList::displayProducts()
{
	cout << endl;
	if(PList.empty())
	{
		cout << "No products available. The product list is empty" << endl << endl;
	}
	else	
	{
		for(list<Product>::iterator it = PList.begin(); it != PList.end(); it++)
		{
			cout << "Product ID: " << it->getProdNum() << endl;
			cout << "Name: " << it->getProdName() << endl;
			cout << "Price per pound: " << setprecision(2) << fixed << "$" << it->getProdPrice() << endl;
			cout << "Pounds in inventory: " << it->getProdLbsInventory() << endl << endl;
		}
		cout << endl;
	}
}

//****************************************************************************************************

bool ProductList::findProduct(Product& p)
{
	bool found = false;
	if(PList.empty())
	{
		cout << "The product list is empty." << endl << endl;
		return found;
	}
	auto it = find(PList.begin(), PList.end(), p);
	if(it != PList.end())
	{
		found = true;
		p = *it;
	}
	return found;
}

//****************************************************************************************************

bool ProductList::editProduct(Product& p)
{
	bool edited = false;
	if(PList.empty())
	{
		cout << "The product list is empty." << endl << endl;
		return edited;
	}
	auto it = find(PList.begin(), PList.end(), p);
	if(it != PList.end())
	{
		*it = p;
		edited = true;
	}
	return edited;
}

//****************************************************************************************************

bool ProductList::removeProduct(const Product& p)
{
	if(PList.empty())
		return false;
	bool removed = true;
	try
	{
		PList.remove(p);
	}
	catch(exception e)
	{
		removed = false;
	}
	if(removed)
		prodCount--;
	return removed;
}

//****************************************************************************************************

bool ProductList::removeAll()
{
	if(PList.empty())
		return true;
	while(!PList.empty())
		PList.pop_front();
	return PList.empty();
}

//****************************************************************************************************

bool ProductList::removeInventory(ProductList& oL)
{
	Product orderP;
	Product inventoryP;
	bool success = false;
	float lbs;

	for(list<Product>::iterator it = oL.PList.begin(); it != oL.PList.end(); it++)
	{
		orderP = *it;
		inventoryP = *it;
		success = (findProduct(inventoryP));
		if(success)
		{
			lbs = orderP.getProdWeight();
			float difference = inventoryP.getProdLbsInventory() - lbs;
			if(difference < 0)
			{
				success = false;
				cout << "There is not enough inventory to cover this order." << endl << endl;
				return success;
			}
			inventoryP.setProdLbsInventory(difference);
			success = editProduct(inventoryP);
		}
	}
	return success;
}

//****************************************************************************************************

bool ProductList::writeProducts()
{
	fstream outFile("ProdList.txt", ios::out);
	if(!outFile)
		return false;
	else
	{
		copy(PList.begin(), PList.end(), ostream_iterator<Product>(outFile));
		outFile.close();
		return true;
	}
}

//****************************************************************************************************

bool ProductList::empty()
{
	return PList.empty();
}

//****************************************************************************************************

fstream& ProductList::writeReceipt(fstream& out)
{
	for(list<Product>::iterator it = PList.begin(); it != PList.end(); it++)
	{
		out << setw(40) << setfill(' ') << left << it->getProdName() 
		<< right << setprecision(2) << fixed << "$" << it->getProdPrice()  << "/lb." << endl
		<< right << setprecision(3) << fixed << it->getProdWeight() << " lbs." << endl;
	}
	return out;
}

//****************************************************************************************************

int ProductList::getProdCount() const
{
	return prodCount;
}
