#pragma once
#include "Store_Customer_Insurance_Purchase.h"

struct Warehouse
{
	std::vector<Item> inventory;
	Item* getItem(int idNum);
};

struct Employee
{
	std::string name, username, password;
};

class Company{
private:
	Warehouse warehouse;
	int month, day, year;
	struct tm date;
	std::vector<std::string> dataLogs;
	std::vector<Store> storeChain;
	std::vector<Item> stockableItems;
	std::vector<Insurance> insuranceProviders;
	std::vector<Employee> employeeList;
	std::vector<Customer> customers;
	std::string currentUser;
	bool loggedIn = false;
	//Batch file class(s) can be added here


public:
	Company(Warehouse warehouse, int day, int month, int year, std::vector<Store> stores, std::vector<Item> items, std::vector<Insurance> insurance);
	Company();
	//getters & setters
	//Store
	void addStore(Store s);
	void deleteStore(int id);
	Store* getStore(int id);
	//Item
	void addItemToStock(Item i);
	void deleteItemFromStock(int id);
	bool isItemInStock(int id);
	std::vector<Item>* getItemList();
	void sendItems(std::vector<Item> order, Store destination);
	//Employee
	std::vector<Employee> getEmployees();
	void addEmployee(Employee e);
	bool getLoggedIn();
	std::string getCurrentUser();
	//Insurance
	std::vector<Insurance> getInsuranceList();
	Insurance* getInsurance(int idNum);
	void addInsurance(Insurance i);
	//Customer
	int customerNum = 0;
	void addCustomer(Customer newCustomer);
	void createCustomer();
	Customer* getCustomer(std::string phoneNum);
	std::vector<Customer> getCustomerList();
	//Warehouse
	bool addInventoryToWarehouse(Item item);
	//Dates
	int getDay();
	int getMonth();
	int getYear();


	//Checks for allowed employee credentials, returns bool allowed or denied
	bool verifyEmployee();
	void employeeLogin();
	void readEmployeeFile();

	//Class functions
	void endDay();
	void beginDay();

	//Major Transaction method, likely will have sub-methods
	void transaction();

	//Finds all purchases related to a customer
	std::vector<Purchase> findCustomerPurchases(Customer c);
	//Formats a chart to display a store's purchases, but would likely be better at Company level
	std::string displayPurchases(int year);
	//Date functionalities
	void updateDate();
	void datePlusDays(int days);
	void getTodaysDate();
	void setupDate();


};

