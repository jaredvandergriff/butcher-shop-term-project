# butcher-shop-term-project
Term project from Webster

Short Line POS

This is a point of sale system for a butcher shop. It allows clerks and managers to login and help customers check out, manage inventory and employee accounts, and track sales throughout the day. 

Authors

Jared Vandergriff
Contributing customer/tester: Jarryd Lapp                                

Getting Started

Download ShortLinePOS.zip and extract the .cpp and .h files to a folder on your computer. Optional: Extract the already populated ClerkList.txt, ProdList.txt, Receipt.txt, and DailyTotal.txt files, or just use the program to populate these files.

Prerequisites

Run using Windows XP or later. Visual Studio 2012 or later required.
Installing
Create a new project in Visual Studio, and add the following files to the project:
Person.h
Person.cpp
Clerk.h
Clerk.cpp
Manager.h
Manager.cpp
ClerkList.h
ClerkList.cpp
Product.h
Product.cpp
ProductList.h
ProductList.cpp
Station.h
Station.cpp
EntryFailException.h
StationDriver.cpp (used to run the program)

Running the program

1. Answer prompt to type in a value for the station number to login to (1-4 are valid responses, anything else should not be accepted).
2. Enter user ID (four digits, any other entry should not be accepted).
3. Enter password (5 – 20 characters), and the system will try to validate your entry against the contents of the ClerkList.txt file. If you haven’t loaded the ClerkList.txt file, there is a hard-coded default user with the following login for testing purposes: 1111 , ADMIN
4. If logged in as a standard employee, skip to #15.
5. Choose option 1 to view manager menu options.
6. Choose option 1 to add a new employee.
	6a. Enter a new user ID (four digits, any other entry should not be accepted).
	6b. Enter a new password (5 – 20 characters).
	6c. Enter a first name (1 – 20 characters).
	6d. Enter a last name (1 – 20 characters).
	6e. System will validate that a new employee ID has been used, and display an error if not.
7. Choose option 2 to look up an existing employee by employee ID. Enter an employee ID to find. The system will validate against ClerkList.txt to find the employee.
8. Choose option 3 to remove an employee. Enter an employee ID to remove. If found, the employee record will be removed from the list, and the update will be applied to the ClerkList.txt file before the program exits.
9. Choose option 4 to add a new product.
	9a. Enter a new product name (3 – 30 characters).
	9b. Enter a price/lb. (0.50 – 50.0).
	9c. Enter lbs in inventory (1.0 – 50.0).
	9d. System will validate that a new product has been added to the list.
10. Choose option 5 to display all products.
11. Choose option 6 to remove a product. Enter a product ID to find. If found, the product record will be removed from the list, and the update will be applied to the ProdList.txt file before the program exits.
12. Choose option 7 to reset the static customer number to zero.
13. Choose option 8 to exit the program (*planning to change this so that the top-level choice to access manager menu versus employee menu is presented again).

14. Choose option 2 to access the standard employee menu.
15. Choose option 1 to generate a new customer (this simulates a customer taking a number at the counter). This option can be chosen multiple times to populate the customer queue.
16. Choose option 2 to assign the next customer in the queue to the station currently logged in.
17. Choose option 3 to display the customer currently assigned.
18. Choose option 4 to begin the checkout process.
19. Choose option 1 in the checkout menu to display all products available to add to the order.
20. Choose option 2 to add a product to the order.
	20a. Enter a product ID to add to the order. If found the product information will be displayed.
	20b. Enter the purchase amount to add to the order (more than 0.125 and can’t exceed 50.0).
	20c. Choose whether to add additional products (enter Y/N).
21. Choose option 3 to proceed with the checkout process.
	21a. Choose payment option (either 1 for cash or 2 for credit).
	21b. Enter the amount tendered (cannot zero or less, cannot exceed the amount due + 100).
	21c. If the amount tendered does not cover the total, the system will prompt for additional 	payment until the amount tendered meets or exceeds the total.
	21d. Checkout will proceed, with a receipt generated in Receipt.txt, and the daily total recorded 	in DailyTotal.txt.

License

This project is licensed under the MIT License 
