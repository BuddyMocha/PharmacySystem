#pragma once
#include "Item_ExpDate.h"
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

public:
	Store addStore();
	void deleteStore(Store);

};

