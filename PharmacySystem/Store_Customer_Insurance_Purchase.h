#pragma once

#include "Item_ExpDate.h"
struct Insurance
{
	std::string name;
	int idNum;
	float copay;
	Insurance(int id, std::string name, float copay);
	std::string toString();
};

struct Purchase;

struct Customer
{
	std::string name, address, phoneNum;
	int numReferrals;
	Insurance* insurance;
	std::vector<Purchase*> purchases;
	Customer(std::string name, std::string address, std::string phoneNum, Insurance* insurance);
	std::string toString();
	std::string getPurchaseHistory();
};

//storeNumber can be retrieved from encapsulating store
struct Purchase
{
	bool referred;
	int day, month, year;
	Customer* customer;
	float cost;
	std::vector<Item> transaction;
	Purchase(bool referred, int day, int month, int year, Customer* customer, float cost, std::vector<Item> transaction);
};

class Store
{
private:
	std::string name;
	int idNum, priority;
	std::vector<Item> inventory;

	std::string streetAddress;
	std::string city;
	std::string state;
	int zipCode;

	//Holds the number of items requested to be restocked the next day
	std::vector<Item> currentOrder;
	std::vector<Purchase> transactions;
public:
	//Constructor for new store
	Store(int idNum, std::string streetAddress, std::string city, std::string state, int zipCode, int priority);

	//Getters and setters for private vars
	//ID
	int getID();
	//Priority
	int getPriority();
	void setPriority(int priority);
	//Inventory
	void addItemtoInv(Item item);
	std::vector<Item> getItemList();
	Item* getItem(int idNum);
	//Overloaded, the first definition is to completely remove the item from the inventory, the second is just to remove a quantity of items. Both return what was removed.
	Item removeItemFromInv(int idNum);
	Item removeItemFromInv(int idNum, int quantity);
	//Restock order list, get is overloaded to easily find a specific item in the list or retrieve full list
	std::vector<Item> getOrderList();
	Item getOrderList(int idNum);
	void addToOrder(Item item);
	//Purchases
	void addPurchase(Purchase p);
	std::vector<Purchase>& getPurchaseList();

	//Class Functions
	void editItemData();
	//Ran daily to remove expired items, and will return a string to log removed items
	std::string removeExpiredItems(int day, int month, int year);

};
