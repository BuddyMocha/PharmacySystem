#pragma once
#ifndef Company_H
#define Company_H
#include "Item.h"
#include "Store.h"
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

};

#endif