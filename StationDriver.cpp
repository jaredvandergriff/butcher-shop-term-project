//****************************************************************************************************
//
//			Project Title:		Short Line POS		
//	
//			Class Name:			Driver
//
//			File:				StationDriver.cpp
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
//			ProductList.cpp, Customer.h, Customer.cpp, EntryFailException.h
//
//****************************************************************************************************

#include "Station.h"
#include "EntryFailException.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <queue>
#include <cmath>

//****************************************************************************************************

ostream& title(ostream&);
void displayMenu(ClerkList&, ProductList&, Station&);
void checkFail(const int, int);
void clerkMenu(Customer&, queue<Customer>&, Station&, Manager*, ProductList&);
void managerMenu(ClerkList&, ProductList&, Station&, Manager*, const int);
bool validateID(Manager*, const int);
bool validatePassword(Manager*, const int);
bool readCL(ClerkList&);
void addC(ClerkList&);
void displayC(ClerkList&);
void removeC(ClerkList&);
void writeCL(ClerkList&);
void readPL(ProductList&);
bool addP(ProductList&);
void displayP(ProductList&);
bool editP(ProductList&, const int);
bool editPPrice(ProductList&, Product&, const int);
bool editPLbs(ProductList&, Product&, const int);
bool removeP(ProductList&);
bool writePL(ProductList&);
bool setCustNum(Manager*);
bool setStationAvail(Station&, Customer&, queue<Customer>&);
bool assignCustomer(Customer&, Station&);
void displayCustomerNum(Station&);
bool advanceCustomerNum(Manager*);
void checkout(Station&, Customer&, Clerk&, ProductList&, double);
double addToOrder(ProductList&, ProductList&, double);
double calcTax(double, double);
bool processPayment(ProductList&, ProductList&, Station&, Customer&, const string&, double, double);
void generateReceipt(ProductList&, Station&, int, const string&, double, double, double);
bool logout();
int numOfDigits(int);
bool validateFloat(string&, float&);
bool validateDouble(string&, double&);
bool validateInt(string&, int&);
double round(double, int);

//****************************************************************************************************

int main()
{
	try
	{
	Station station;
	ClerkList SLClerkList;
	ProductList SLProductList;
	displayMenu(SLClerkList, SLProductList, station);
	}
	catch(EntryFailException &ef)
	{
		cerr << ef.what();
		return 0;
	}

	return 0;
}

//****************************************************************************************************

ostream & title(ostream & output)

{

  return output   
	  << "   _____ __               __     __    _               ____  ____  _____" << endl
      << "  / ___// /_  ____  _____/ /_   / /   (_)___  ___     / __ \\/ __ \\/ ___/" << endl
      << "  \\__ \\/ __ \\/ __ \\/ ___/ __/  / /   / / __ \\/ _ \\   / /_/ / / / /\\__ \\ " << endl
      << " ___/ / / / / /_/ / /  / /_   / /___/ / / / /  __/  / ____/ /_/ /___/ / " << endl
      << "/____/_/ /_/\\____/_/   \\__/  /_____/_/_/ /_/\\___/  /_/    \\____//____/  " << endl
      << endl << endl;
}

//****************************************************************************************************

void displayMenu(ClerkList& slcl, ProductList& slpl, Station& s)
{
	int failstate = 0;
	int stationNum;
	string temp;
	const int FAIL_LIMIT = 10;
	const int NUM_STATIONS = 4;
	

	cout << title;
	cout << "Please enter the station you wish to login to (1-" << NUM_STATIONS << ")." << endl;
	cout << "Enter station number: ";
	getline(cin, temp);
	while(temp.find(' ') != string::npos || !validateInt(temp, stationNum) || stationNum < 1 
										 || stationNum > NUM_STATIONS)
	{
		failstate++;
		try
		{
			checkFail(FAIL_LIMIT, failstate);
		}
		catch(EntryFailException &ef)
		{
			throw ef;
		}
		cout << "You have entered an incorrect value. The system only supports up to " 
			 << NUM_STATIONS << " stations. Please try again: ";
		getline(cin, temp);
	}
	failstate = 0;
	s.setStationNum(stationNum);

	cout << "You are accessing station number " << s.getStationNum() << "." << endl << endl;
	
	Manager manager;
	Manager* m = &manager;

	readCL(slcl);
	readPL(slpl);

	bool login = false;

	do
	{
		validateID(m, FAIL_LIMIT);
		validatePassword(m, FAIL_LIMIT);
		login = slcl.validateClerk(*m);
		if(!login)
			cout << "You have entered an incorrect username or password. "
				 << "Please try again." << endl << endl;
	}while(!login);

	Customer cust;
	queue<Customer> custQ;
	char choice;
		
	cout << "Welcome " << m->getEmpFName() << " " << m->getEmpLName() << endl;
	if(m->getEmpID() %10 != 1)
	{
		cout << "You have standard employee access." << endl << endl;
		clerkMenu(cust, custQ, s, m, slpl);
	}
	else if(m->getEmpID() %10 == 1)
	{		
		cout << "You have manager access." << endl << endl;
		do
		{
			cout << "Select manager or standard employee options: " << endl << endl;
			cout << "1 - Manager options" << endl << "2 - Clerk options" 
				 << endl << "3 - Logout" << endl << endl;
			cout << "Enter choice: ";
			getline(cin, temp);
			while(temp.length() != 1)
			{
				cout << "Your choice must be one character. Please try again: ";
				temp[0] = 0;
				getline(cin, temp);
			}
			choice = temp[0];
		
			switch(choice)
			{
				case '1':
					managerMenu(slcl, slpl, s, m, FAIL_LIMIT);
					break;

				case '2':
					clerkMenu(cust, custQ, s, m, slpl);
					break;

				case '3':
					if(logout())
						break;
					else
					{
						choice = ' ';
						break;
					}

				default:
					cout << "You did not enter a valid choice. "
						 << "Please enter a valid choice." << endl << endl;
					break;
			}

		}while(choice != '3');
	}
}

//****************************************************************************************************

void checkFail(const int FL, int fs)
{
	if(fs >= FL)
		throw EntryFailException();
}

//****************************************************************************************************

bool validateID(Manager* m, const int FAIL_LIMIT)
{
	int ID;
	string temp;
	int failstate = 0;
	const int VALID_NUM = 4;
	cout << "Please login below: " << endl;
	cout << "Employee ID: ";
	getline(cin, temp);
	while(temp.find(' ') != string::npos || !validateInt(temp, ID) || ID < 0 
										 || numOfDigits(ID) != VALID_NUM)
	{
		failstate++;
		try
		{
			checkFail(FAIL_LIMIT, failstate);
		}
		catch(EntryFailException &ef)
		{
			cerr << ef.what();
			throw &ef;
		}
		cout << "You have entered an invalid employee number. Employee numbers must be four digits. "
			 << "Please try again: ";
		getline(cin, temp);
	}
	failstate = 0;
	m->setEmpID(ID);
	return true;
}

//****************************************************************************************************

bool validatePassword(Manager* m, const int FAIL_LIMIT)
{
	string pword;
	int failstate = 0;
	cout << endl << "Password: ";
	getline(cin, pword);
	while(pword.length() < 5 || pword.length() > 20 || pword.find(' ') != string::npos)
	{
		failstate++;
		try
		{
			checkFail(FAIL_LIMIT, failstate);
		}
		catch(EntryFailException &ef)
		{
			cerr << ef.what();
			throw &ef;
		}
		cout << "Passwords must be at least five and no greater than 20 characters " 
			 << "and cannot contain spaces. Please try again: ";
		getline(cin, pword);
	}
	failstate = 0;
	m->setPassword(pword);
	return true;
}

//****************************************************************************************************

void clerkMenu(Customer& cust, queue<Customer>& custQ, Station& s, Manager* m, ProductList& slpl)
{
	const double SALES_TAX_RATE = 0.04225;
	char choice;
	string temp;

	do
	{
		cout << "Please choose an option: " << endl << endl;
		cout << "1 - Generate a new customer" << endl 
			 << "2 - Assign available customers to this station" << endl  
			 << "3 - Display currently assigned customer number" << endl 
			 << "4 - Advance customer number" << endl << "5 - Checkout" << endl
			 << "6 - Logout/Cancel" << endl << endl;
	
		cout << "Enter choice: ";
		getline(cin, temp);
		while(temp.length() != 1)
		{
			cout << "Your choice must be one character. Please try again: ";
			getline(cin, temp);
		}
		choice = temp[0];
		
		switch(choice)
		{
			case '1':
			{
				Customer newCust;
				custQ.push(newCust);
				cout << "Customer number " << newCust.getCustNum() 
					 << " has been generated." << endl;
				cout << "There are currently " << custQ.size() 
					 << " customers in the queue." << endl << endl;
			}
				break;
			
			case '2':
				if(custQ.empty())
					cout << "No customers are waiting." << endl << endl;
				else if(!s.getAvail())
					cout << "You already have a customer assigned to your station." 
					     << endl << endl;
				else
					setStationAvail(s, cust, custQ);
				break;

			case '3':
				displayCustomerNum(s);
				break;

			case '4':
				advanceCustomerNum(m);
				break;

			case '5':
				if(s.getAvail() && custQ.empty())
				cout << "No customer currently assigned. There is nobody to checkout." 
					 << endl << endl;
				else
					checkout(s, cust, *m, slpl, SALES_TAX_RATE);
				break;
			
			case '6':
				writePL(slpl);
				if(logout())
					break;
				else
				{
					choice = ' ';
					break;
				}

			default:
				cout << "You did not enter a valid choice. Please enter a valid choice." 
					 << endl << endl;
				break;
		}
	}while(choice != '6');
}

//****************************************************************************************************

void managerMenu(ClerkList& slcl, ProductList& slpl, Station& s, Manager* m, const int FL)
{
	char choice;
	string temp;
	do
	{
		cout << "Please choose an option: " << endl << endl;
		cout << "1 - Add new employee" << endl << "2 - Lookup an employee" << endl  
			 << "3 - Remove an employee" << endl << "4 - Add a new product" << endl
			 << "5 - List all products" << endl << "6 - Edit a product" << endl 
			 << "7 - Remove a product" << endl << "8 - Set customer number" << endl
			 << "9 - View sales total" << endl << "0 - Cancel" << endl << endl;
	
		cout << "Enter choice: ";
		getline(cin, temp);
		while(temp.length() != 1)
		{
			cout << "Your choice must be one character. Please try again: ";
			temp[0] = ' ';
			getline(cin, temp);
		}
		choice = temp[0];
	
		switch(choice)
		{
			case '1':
				addC(slcl);
				break;
				
			case '2':
				displayC(slcl);
				break;

			case '3':
				removeC(slcl);
				break;

			case '4':
				addP(slpl);
				break;

			case '5':
				displayP(slpl);
				break;

			case '6':
				editP(slpl, FL);
				break;

			case '7':
				removeP(slpl);
				break;
		
			case '8':
				setCustNum(m);
				break;

			case '9':
				cout << "The total for today's sales is: $" << setprecision(2) 
					 << fixed << s.getDailyTotal() << endl << endl;
				break;

			case '0':
				writeCL(slcl);
				writePL(slpl);
				break;

			default:
				cout << "You did not enter a valid choice. "
					 << "Please enter a valid choice." << endl << endl;
				break;
		}
	}while(choice != '0');
}

//****************************************************************************************************

bool readCL(ClerkList& slcl)
{
	bool success = slcl.readClerks();
	if(success)
		cout << "Employees loaded successfully from ClerkList.txt file." << endl << endl;
	else
		cout << "Employees not loaded successfully. Please check file." << endl << endl;
	return success;
}

//****************************************************************************************************

void addC(ClerkList& slcl)
{
	bool success = false;
	Clerk clerk;
	Clerk *c = &clerk;
	int cID;
	string temp;
	string lname;
	string fname;
	string pword;
	const int VALID_NUM = 4;

	cout << "Enter a new employee ID: ";
	getline(cin,temp);
	while(temp.find(' ') != string::npos || !validateInt(temp, cID) || cID < 0 
										 || numOfDigits(cID) != VALID_NUM)
	{
		cout << "You have entered an invalid employee number. Employee numbers must be four digits. "
			 << "Please try again: ";
		getline(cin,temp);
	}
	cout << endl << "Enter a password for the new employee: ";
	getline(cin, pword);
	while(pword.length() < 5 || pword.length() > 20 || pword.find (' ') != string::npos)
	{
		cout << "Passwords must be at least five and no greater than 20 characters and "
			 << "cannot contain spaces. Please try again: ";
		getline(cin, pword);
	} 
	cout << endl << "Enter the new employee's first name: ";
	getline(cin, fname);
	while(fname.length() < 1 || fname.length() > 20 || fname.find (' ') != string::npos)
	{
		cout << "Names must be at least one character and no greater than 20 characters and "
			 << "cannot contain spaces. Please try again: ";
		getline(cin, fname);
	}
	cout << endl << "Enter the new employee's last name: ";
	getline(cin, lname);
	while(lname.length() < 1 || lname.length() > 20 || lname.find (' ') != string::npos)
	{
		cout << "Names must be at least one character and no greater than 20 characters and "
			 << "cannot contain spaces. Please try again: ";
		getline(cin, lname);
	}

	c->setEmpID(cID);
	c->setEmpLName(lname);
	c->setEmpFName(fname);
	c->setPassword(pword);
	
	if(slcl.lookup(*c))
		cout << "This employee ID already exists. Please try again." << endl << endl;
	else
	{
		success = slcl.addClerk(*c);
		if(success)
			cout << "Employee added successfully to the list." << endl << endl;
		else
			cout << "Employee not added successfully to the list." << endl << endl;
	}
}

//****************************************************************************************************

void displayC(ClerkList& slcl)
{
	bool found = false;
	Clerk clerk;
	Clerk* c = &clerk;
	int cID;
	string temp;
	cout << "Enter the employee number you wish to view: ";
	getline(cin, temp);
	while(temp.find(' ') != string::npos || !validateInt(temp, cID) || !cin)
	{
		cout << "You have entered an invalid employee number. Employee numbers must be four digits. "
			 << "Please try again: ";
		getline(cin, temp);
	}
	c->setEmpID(cID);
	found = slcl.lookup(*c);
	if(found)
	{
		cout  << "Found employee: " << endl << endl;
		c->print();
	}
	else
		cout << "Employee not found." << endl << endl;
}

//****************************************************************************************************

void removeC(ClerkList& slcl)
{
	bool success = false;
	Clerk c;
	int cID;
	string temp;
	const int VALID_NUM = 4;

	cout << "Enter the employee ID you wish to remove: ";
	getline(cin, temp);
	while(temp.find(' ') != string::npos || !validateInt(temp, cID) || cID < 0 
										 || numOfDigits(cID) != VALID_NUM)
	{
		cout << "You have entered an invalid employee number. Employee numbers must be four digits. "
			 << "Please try again: ";
		getline(cin, temp);
	}
	c.setEmpID(cID);
	success = slcl.removeClerk(c);

	if(success)
		cout << "Employee removed successfully from the list." << endl << endl;
	else
		cout << "Employee not found." << endl << endl;
}

//****************************************************************************************************

void writeCL(ClerkList& slcl)
{
	bool success = slcl.writeClerks();
	if(success)
		cout << "Clerk list saved." << endl << endl;
	else
		cout << "Clerk list not saved successfully." << endl << endl;
}

//****************************************************************************************************

void readPL(ProductList& sLL)
{
	bool success = false;

	success = sLL.readProducts();
	if(success)
		cout << "Products loaded successfully from ProdList.txt file." << endl << endl;
	else
		cout << "Products not loaded successfully. Please check file." << endl << endl;
}

//****************************************************************************************************

bool addP(ProductList &sLL)
{
	Product p;
	string temp;
	int num;
	string name;
	double price;
	float lbsInventory;
	bool success = false;

	num = sLL.getProdCount();
	cout << endl << "Enter product name: ";
	getline(cin, name);
	while(name.length() < 3 || name.length() > 30)
	{
		cout << "You have entered an invalid name. The product name must be at least 3 characters and"
			 << "no more than 30. Please try again: ";
		getline(cin, name);
	}
	cout << endl << "Enter product price per pound: ";
	getline(cin, temp);
	while(temp.find(' ') != string::npos || !validateDouble(temp, price) || price < 0.50 || price > 50)
	{
		cout << "You have entered an invalid price. Price must be at least 0.50 and no more than 50.0. "
			 << "Please try again: ";
		getline(cin, temp);
	}
	cout << endl << "Enter product pounds in inventory: ";
	getline(cin, temp);
	while(temp.find(' ') != string::npos || !validateFloat(temp, lbsInventory) || lbsInventory < 1 
										 || lbsInventory >= 50)
	{
		cout << "You have entered an invalid value. Pounds must be at least 1 and no more than 50. "
			 << "Please try again: ";
		getline(cin, temp);
	}
	cout << endl;

	p.setProdNum(num);
	p.setProdName(name);
	p.setProdPrice(price);
	p.setProdLbsInventory(lbsInventory);
			
	success = sLL.addProduct(p);
	if(success)
		cout << endl << "Product added successfully." << endl;
	else
		cout << endl << "Product failed to be added." << endl;
	return success;
}

//****************************************************************************************************

void displayP(ProductList& sLL)
{
	sLL.displayProducts();
}

//****************************************************************************************************

bool editP(ProductList& sLL, const int FL)
{
	Product p;
	int num;
	string temp;
	char choice = ' ';
	bool success = false;

	cout << "Enter product number: ";
	getline(cin, temp);
	while(temp.find(' ') != string::npos || !validateInt(temp, num) || num < 0)
	{
		cout << "You have entered an invalid product number. Please try again: ";
		getline(cin, temp);
	}
	temp = " ";
	cout << endl;

	p.setProdNum(num);
	success = sLL.findProduct(p);

	if(success)
	{
		cout << "Product found." << endl << endl;
		cout << "Product ID: " << p.getProdNum() << endl;
		cout << "Name: " << p.getProdName() << endl;
		cout << "Price per pound: " << setprecision(2) << fixed << "$" << p.getProdPrice() << endl;
		cout << "Pounds in inventory: " << p.getProdLbsInventory() << endl << endl;

		do
		{
			cout << "Product ID and name are not editable. If these are incorrect, delete and "
				 << "recreate the product." << endl << endl;
			cout << "Please choose a field to edit: " << endl << endl;
			cout << "1 - Price per pound" << endl << "2 - Pounds in inventory" << endl  
				 << "3 - Cancel" << endl << endl;
	
			cout << "Enter choice: ";
			getline(cin, temp);
			while(temp.length() != 1)
			{
				cout << "Your choice must be one character. Please try again: ";
				temp[0] = 0;
				getline(cin, temp);
			}
			choice = temp[0];
	
			switch(choice)
			{
				case '1':
					success = editPPrice(sLL, p, FL);
					if(success)
						cout << "Price successfully edited." << endl << endl;
					else
						cout << "Price edit failed." << endl << endl;
					choice = '3';
					break;

				case '2':
					success = editPLbs(sLL, p, FL);
					if(success)
						cout << "Inventory successfully edited." << endl << endl;
					else
						cout << "Inventory edit failed." << endl << endl;
					choice = '3';
					break;

				case '3':
					sLL.writeProducts();
					break;

				default:
					cout << "You did not enter a valid choice. Please enter a valid choice." 
						 << endl << endl;
					break;
			}
		}while(choice != '3');
	}
	else
		cout << "Product not found." << endl << endl;
	return success;
}

//****************************************************************************************************

bool editPPrice(ProductList& sLL, Product& p, const int FL)
{
	string temp;
	double price;
	int failstate = 0;
	bool success = false;

	cout << endl << "Enter product price per pound: ";
	getline(cin, temp);
	while(temp.find(' ') != string::npos || !validateDouble(temp, price) || price < 0.50 || price > 50)
	{
		failstate++;
		if(failstate >= FL)
		{
			cout << "You have entered an incorrect value too many times. Returning to previous menu." 
				 << endl << endl;
			return success;
		}
		cout << "You have entered an invalid price. Price must be at least 0.50 and no more than 50.0. "
			 << "Please try again: ";
		getline(cin, temp);
	}
	p.setProdPrice(price);
	success = sLL.editProduct(p);
	return success;
}

//****************************************************************************************************

bool editPLbs(ProductList& sLL, Product& p, const int FL)
{
	string temp;
	float lbsInventory;
	int failstate = 0;
	bool success = false;
	
	cout << endl << "Enter product pounds in inventory: ";
	getline(cin, temp);
	while(temp.find(' ') != string::npos || !validateFloat(temp, lbsInventory) || lbsInventory < 1 
										 || lbsInventory >= 50)
	{
		failstate++;
		if(failstate >= FL)
		{
			cout << "You have entered an incorrect value too many times. Returning to previous menu." 
				 << endl << endl;
			return success;
		}
		cout << "You have entered an invalid value. Pounds must be at least 1 and no more than 50. "
			 << "Please try again: ";
		getline(cin, temp);
	}
	p.setProdLbsInventory(lbsInventory);
	success = sLL.editProduct(p);
	return success;
}

//****************************************************************************************************

bool removeP(ProductList& sLL)
{
	Product p;
	int num;
	string temp;
	bool success = false;

	cout << "Enter product number: ";
	getline(cin, temp);
	while(temp.find(' ') != string::npos || !validateInt(temp, num) || num < 0)
	{
		cout << "You have entered an invalid product number. Please try again: ";
		getline(cin, temp);
	}
	cout << endl;

	p.setProdNum(num);
		
	success = sLL.removeProduct(p);
	if(success)
		cout << endl << "Product removed successfully." << endl;
	else
		cout << endl << "Product not found in the list." << endl;
	return success;
}

//****************************************************************************************************

bool writePL(ProductList& sLL)
{
	bool success = false;
	cout << "Saving product list." << endl;
	success = sLL.writeProducts();
	if(success)
	{
		cout << "Product list saved." << endl << endl;
	}
	else
	{
		cout << "Product list not saved successfully." << endl;
	}
	return success;
}

//****************************************************************************************************

bool setCustNum(Manager* m)
{
	int num;
	string temp;
	char choice;
	bool success = false;

	cout << "Current customer number for next in queue: " << m->getCustomerNum() << endl;

	cout << "Do you wish to proceed with changing the customer number? Please confirm (Y/N): ";
	cout << "Enter choice: ";
	getline(cin, temp);
	while(temp.length() != 1 || (temp[0] != 'Y' && temp[0] != 'y' && temp[0] != 'N' && temp[0] != 'n'))
	{
		cout << "Your choice must be one character, either a Y or an N. Please try again: ";
		getline(cin, temp);
	}
	choice = temp[0];
	if(choice == 'Y' || choice == 'y')
	{
		temp = " ";
		cout << "Enter correct customer number (0 - 199): ";
		getline(cin, temp);
		while(temp.find(' ') != string::npos || !validateInt(temp, num) || num < 0 || num > 199)
		{
			cout << "You have entered an invalid customer number. Please try again: ";
			getline(cin, temp);
		}
		cout << endl;
		success = m->setCustomerNum(num);
	}
	return success;
}

//****************************************************************************************************

bool setStationAvail(Station& s, Customer& cust, queue<Customer>& cQ)
{
	if(!cQ.empty())
	{
		s.setAvail(true);
		cust = cQ.front();
		cQ.pop();
		assignCustomer(cust, s);
		cout << "Customer number " << cust.getCustNum() << " assigned." << endl << endl;
		return true;	
	}
	return false;
}

//****************************************************************************************************

bool assignCustomer(Customer& cust, Station& s)
{
	if(s.getAvail())
	{
		cust.setStation(s.getStationNum());
		s.setCurrentCustomer(cust.getCustNum());
		s.setAvail(false);
		return true;
	}
	return false;
}

//****************************************************************************************************

void displayCustomerNum(Station& s)
{
	if(!s.getAvail())
		cout << "Currently serving: " << s.getCurrentCustomer() << endl << endl;
	else
		cout << "No customer currently assigned." << endl << endl;
}

//****************************************************************************************************

bool advanceCustomerNum(Manager* m)
{
	char choice = ' ';
	string temp;

	cout << "The next customer number in queue is " << m->getCustomerNum() + 1 << endl;
	cout << "Are you sure you wish to advance the customer number? Please confirm (Y/N): ";
	cout << "Enter choice: ";
	getline(cin, temp);
	while(temp.length() != 1 || (temp[0] != 'Y' && temp[0] != 'y' && temp[0] != 'N' && temp[0] != 'n'))
	{
		cout << "Your choice must be one character, either a Y or an N. Please try again: ";
		getline(cin, temp);
	}
	choice = temp[0];
	if(choice == 'Y' || choice == 'y')
	{
		m->iterateCustNum();
		return true;
	}
	return false;
}

//****************************************************************************************************

void checkout(Station& s, Customer& cust, Clerk& c, ProductList& slpl, double tax)
{
	ProductList orderList;
	string fname = c.getEmpFName();
	string lname = c.getEmpLName();
	string clerkName = fname + " " + lname;
	char choice;
	string temp;
	double subTotal = 0.0;
	
	do
	{
		if(subTotal > 0)
			cout << "Current subtotal: $" << setprecision(2) << fixed << subTotal << endl << endl;
		cout << "Please choose an option: " << endl << endl;
		cout << "1 - Display all available products" << endl << "2 - Add products to order" << endl  
			 << "3 - Proceed to checkout" << endl << "4 - Cancel" << endl << endl;
	
			cout << "Enter choice: ";
			getline(cin, temp);
			while(temp.length() != 1)
			{
				cout << "Your choice must be one character. Please try again: ";
				temp[0] = 0;
				getline(cin, temp);
			}
			choice = temp[0];
	
			switch(choice)
			{
				case '1':
					slpl.displayProducts();
					break;

				case '2':
					subTotal = addToOrder(slpl, orderList, subTotal);
					break;

				case '3':
					if(!processPayment(slpl, orderList, s, cust, clerkName, subTotal, tax) 
						|| subTotal <= 0)
						cout << "No order created for checkout. Please add products to your order." 
							 << endl << endl;
					choice = '4';
					break;

				case '4':
					break;
				
				default:
					cout << "You did not enter a valid choice. Please enter a valid choice." 
						 << endl << endl;
					break;
				}
	}while(choice != '4');
}

//****************************************************************************************************

double addToOrder(ProductList& slpl, ProductList& orderList, double subTotal)
{
	Product p;
	double prodTotal = 0.0;
	int prodID;
	string temp;
	float prodWeight;
	bool foundProd = false;
	bool enoughInventory = false;
	char yOrN = 'n';
	do
	{
		cout << "Enter a product ID to add to the customer's order: ";
		getline(cin, temp);
		while(temp.find(' ') != string::npos || !validateInt(temp, prodID) || prodID < 0)
		{
			cout << "You have entered an invalid ID. Please try again: " << endl;
			getline(cin, temp);
		}
		p.setProdNum(prodID);
		foundProd = slpl.findProduct(p);
		if(foundProd)
		{
			cout << "Product found: " << p.getProdName() << endl;
			cout << "Price per pound: $" << p.getProdPrice() << endl << endl;
			cout << "Enter purchase amount weight in pounds (decimal): ";
			getline(cin, temp);
			while(temp.find(' ') != string::npos || !validateFloat(temp, prodWeight) 
						   || prodWeight < 0.125 || prodWeight > 50)
			{
				cout << "You have entered an invalid weight value. "
					 << "Weight cannot exceed 50 pounds nor be less than 1/8 of a pound (0.125). "
					 << "Please try again: " << endl;
				getline(cin, temp);
			}
			cout << endl << endl;
			p.setProdWeight(prodWeight);
			prodTotal = prodWeight * p.getProdPrice();
			orderList.addProduct(p);
			subTotal += prodTotal;
			cout << "Current subtotal: $" << setprecision(2) << fixed << subTotal << endl << endl;
			cout << "Add another product? Y or N: ";
			cin >> yOrN;
			while(yOrN != 'Y' && yOrN != 'y' && yOrN != 'N' && yOrN != 'n')
			{
				cout << "You did not enter a Y or an N. Please try again: ";
				cin.ignore(5000, '\n');
				cin >> yOrN;
			}
			cin.ignore(5000, '\n');
		}
		else
		{
			cout << "Product not found." << endl << endl;
			cout << "Try again? Y or N: ";
			cin >> yOrN;
			while(yOrN != 'Y' && yOrN != 'y' && yOrN != 'N' && yOrN != 'n')
			{
				cout << "You did not enter a Y or an N. Please try again: ";
				cin.ignore(5000, '\n');
				cin >> yOrN;
			}
			cin.ignore(5000, '\n');
		}
	}while(yOrN == 'Y' || yOrN == 'y');
	return subTotal;
}

//****************************************************************************************************

double calcTax(double subTotal, double rate)
{
	double tax = subTotal * rate;
	return tax;
}

//****************************************************************************************************

bool processPayment(ProductList& slpl, ProductList& orderList, Station& s, Customer& cust, 
					const string& clerkName, double subTotal, double rate)
{
	if(orderList.empty() || subTotal <= 0.0)
		return false;
	double total = 0.0;
	double nearestTotal = 0.0;
	double taxCharge = calcTax(subTotal, rate);
	total = subTotal;
	total += taxCharge;
	double amount = 0.0;
	double payment = 0.0;
	double nearestPayment = 0.0;
	char choice;
	string tempCh;
	string temp;
	bool paidInFull = false;
	
	do
	{
		cout << "Current subtotal: $" << setprecision(2) << fixed << subTotal << endl;
		cout << "Tax: $" << setprecision(2) << fixed << taxCharge << endl << endl;
		cout << "Current total: $" << setprecision(2) << fixed << total << endl << endl;
		if(payment > 0)
			cout << "Current amount tendered: $" << setprecision(2) << fixed << payment 
				 << endl << endl;

		cout << "Please choose a payment option: " << endl << endl;
		cout << "1 - Cash" << endl << "2 - Credit" << endl  
			 << "3 - Submit" << endl << "4 - Cancel" << endl << endl;
	
		cout << "Enter choice: ";
		getline(cin, tempCh);
		while(tempCh.length() != 1)
		{
			cout << "Your choice must be one character. Please try again: ";
			tempCh[0] = 0;
			getline(cin, tempCh);
		}
		choice = tempCh[0];

		switch(choice)
		{
			case '1':
				cout << "Enter amount tendered: ";
				getline(cin, temp);
				while(temp.find(' ') != string::npos || !validateDouble(temp, amount) 
									|| amount < 0.01 || amount > (100 + total))
				{
					cout << "You have entered an invalid payment amount or change would exceed $100. "
						 << "Please try again: ";
					getline(cin, temp);
				}
				payment += amount;
				break;

			case '2':
				cout << "Enter amount tendered: ";
				getline(cin, temp);
				while(temp.find(' ') != string::npos || !validateDouble(temp, amount) 
									|| amount < 0.01 || amount > (100 + total))
				{
					cout << "You have entered an invalid payment amount or change would exceed $100. "
						 << "Please try again: ";
					getline(cin, temp);
				}
				payment += amount;
				break;

			case '3':
				nearestTotal = round(total, 2);
				nearestPayment = round(payment, 2);

				cout << "Amount tendered: $" << setprecision(2) << fixed << payment << endl << endl;
				if(nearestPayment < nearestTotal)
				{
					cout << "Amount tendered does not cover amount due." << endl << endl;
					paidInFull = false;
				}
				else if (nearestPayment > nearestTotal)
				{
					cout << "Change due: $" << setprecision(2) << fixed << payment - total 
						 << endl << endl;
					paidInFull = true;
				}
				else if (nearestPayment == nearestTotal)
					paidInFull = true;
				break;

			case '4':
				return false;

			default:
				cout << "You did not enter a valid choice. Please enter a valid choice." << endl;
				break;
		}

	}while(choice != '4' && !paidInFull);

	if(!slpl.removeInventory(orderList))
	{
		cout << "Cancelling order. Returning to menu." << endl;
		orderList.removeAll();
		return false;
	}
	generateReceipt(orderList, s, cust.getCustNum(), clerkName, subTotal, total, taxCharge);
	s.incrementDailyTotal(total);
	s.recordDailyTotal();
	subTotal = 0.0;

	return true;
}

//****************************************************************************************************

void generateReceipt(ProductList& orderList, Station& s, int custNum, const string& clerk, 
					 double subTotal, double total, double taxCharge)
{
	cout << "Generating receipt." << endl << endl;

	fstream outFile("Receipt.txt", ios::out);
	if(!outFile)
		cerr << "Error, receipt cannot be generated." << endl;
	else
	{
		string time = s.getTime();
		outFile << left << "Station " << left << s.getStationNum();
		outFile << setw(40) << right << "Customer# " << custNum << endl << endl;
		outFile << setw(40) << "Thank you for your business!" << endl << endl;
		outFile << setw(40) << left << "You were helped by: " << left << clerk << endl << endl;
		outFile << setw(40) << left << "Purchase summary: " << endl << endl;
		orderList.writeReceipt(outFile) << endl << endl;
		outFile << setw(40) << "Subtotal: " << setprecision(2) << fixed << "$" << subTotal << endl;
		outFile << setw(40) << "Tax: " << setprecision(2) << fixed << "$" << taxCharge << endl;
		outFile << setw(40) << "Your total was: $" << setprecision(2) << fixed << total 
				<< endl << endl;
		outFile << setw(40) << time << endl;
	}
	outFile.close();
	cout << "Station now available." << endl << endl;
	s.setAvail(true);
	s.setCurrentCustomer(0);
}

//****************************************************************************************************

bool logout()
{
	char choice = ' ';
	string temp;

	cout << "Are you sure you wish to logout? Please confirm (Y/N): ";
	cout << "Enter choice: ";
	getline(cin, temp);
	while(temp.length() != 1 || (temp[0] != 'Y' && temp[0] != 'y' && temp[0] != 'N' && temp[0] != 'n'))
	{
		cout << "Your choice must be one character, either a Y or an N. Please try again: ";
		getline(cin, temp);
	}
	choice = temp[0];
	if(choice == 'Y' || choice == 'y')
		return true;
	else
		return false;
}


//****************************************************************************************************

int numOfDigits(int num)
{
	int digits = 0;
    while (num) 
	{
        num /= 10;
        digits++;
    }
    return digits;
}

//****************************************************************************************************

bool validateFloat(string& s, float& f)
{
	istringstream in(s);
	if(in >> f)
		return true;
	return false;
}

//****************************************************************************************************

bool validateDouble(string& s, double& d)
{
	istringstream in(s);
	if(in >> d)
		return true;
	return false;
}

//****************************************************************************************************

bool validateInt(string& s, int& i)
{
	istringstream in(s);
	if(in >> i)
		return true;
	return false;
}

//****************************************************************************************************

double round(double d, int prec)
{
	double power = 1.0;
	int i;

	if (prec > 0)
		for (i = 0; i < prec; i++)
			power *= 10.0;
	else if (prec < 0)
		for (i = 0; i < prec; i++)
			power /= 10.0;

	if (d > 0)
		d = floor(d * power + 0.5) / power;
	else if (d < 0)
		d = ceil(d * power - 0.5) / power;

	if (d == -0)
		d = 0;
	
	return d;
}