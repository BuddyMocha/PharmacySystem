#pragma once
#include "Store_Customer_Employee_Purchase.h"
#include <vector>

struct Warehouse
{
	std::vector<Item> inventory;
};

class Company{
private:
	Warehouse warehouse;
	int month, day, year;
	std::vector<std::string> dataLogs;
	std::vector<Store> storeChain;
	vector<Item> stockableItems;
	vector<Insurance> insuranceProviders;
	//Batch file class(s) can be added here


public:
	Store addStore();
	void deleteStore(Store);
	Item addItemToStock();
	void deleteItemForStock(Item i);
	void sendItems(std::vector<Item> order, Store destination);
	void endDay();
	void beginDay();

};

