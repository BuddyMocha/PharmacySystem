#pragma once
#include <string>
#include <vector>

struct ExpirationDate
{
	int month, day, year, quantity;
};

//may be turned to struct and have store manage item quantity
class Item
{
private:
	std::string name;
	float price;
	int idNum, quantity;
	int requiredRestock;    //The quantity at which the item must be refilled
	int restockQuantity;    //The quantity to refill the item to
	std::vector<ExpirationDate> expirationDates;
public:
	std::vector<Item> removeQuantity(int n);	//Function definition for item is in Store class

};
