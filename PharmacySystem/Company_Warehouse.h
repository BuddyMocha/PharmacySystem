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
	std::vector<std::string> dataLogs;
	std::vector<Store> storeChain;
	std::vector<Item> stockableItems;
	std::vector<Insurance> insuranceProviders;
	std::vector<Employee> employeeList;
	std::vector<Customer> customers;
	//Batch file class(s) can be added here


public:
	Company(Warehouse warehouse, int day, int month, int year, std::vector<Store> stores, std::vector<Item> items, std::vector<Insurance> insurance);
	//getters & setters
	//Store
	Company();

	std::vector<Store> getStoreChain()
	{
		return storeChain;
	}

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


	//Checks for allowed employee credentials, returns bool allowed or denied
	bool verifyEmployee(std::string username, std::string password);

	//Class functions
	void endDay();
	void beginDay();

	//Major Transaction method, likely will have sub-methods
	void transaction();

	//Finds all purchases related to a customer
	std::vector<Purchase> findCustomerPurchases(Customer c);
	//Formats a chart to display a store's purchases, but would likely be better at Company level
	std::string displayPurchases(int year);

	

};

