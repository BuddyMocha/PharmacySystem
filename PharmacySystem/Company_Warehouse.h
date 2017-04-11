#pragma once
#include "Store_Customer_Insurance_Purchase.h"
#include <vector>

struct Warehouse
{
	std::vector<Item> inventory;
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
	//Batch file class(s) can be added here


public:
	Store addStore();
	void deleteStore(Store);
	Item addItemToStock();
	void deleteItemFromStock(Item i);
	void sendItems(std::vector<Item> order, Store destination);
	void endDay();
	void beginDay();

	//Employee
	std::vector<Employee> getEmployees();
	void addEmployee(Employee e);
		//Checks for allowed employee credentials, returns allowed or denied
	bool verifyEmployee(std::string username, std::string password);

};

