#pragma once

#ifndef Store_H
#define Store_H
#include "Item_ExpDate.h"
#include <vector>
struct Insurance
{
	std::string name;
	int id;
	float copay;
};

struct Customer
{
	std::string name, address;
	int phoneNum, id, numReferrals;
	Insurance insurance;
};


//storeNumber can be retrieved from encapsulating store
struct Purchase
{
	int day, month, year; 
	Customer customer;
	float cost;
	std::vector<Item> transaction;
};

class Store
{
private:
	std::string name;
	int idNum, priority;
	std::vector<Item> inventory;

	//Holds the number of items requested to be restocked the next day
	std::vector<Item> currentOrder;

	std::vector<Employee> employees;
	std::vector<Customer> customers;
	std::vector<Purchase> transactions;
public:
	//Constructor for new store
	Store(std::string name, int idNum, int priority);

	//Getters and setters for private vars
	//ID
	int getID();
	//Priority
	int getPriority();
	void setPriority(int priority);
	//Inventory
	void addItemtoInv(Item item);
	std::vector<Item> getItemList();
		//Overloaded, first definition takes a specific quantity of an item, the second removes the item from inventory completely
	Item removeItemFromInv(Item item, int quantity);
	Item removeItemFromInv(Item item);
	//Restock order list, get is overloaded to easily find a specific item in the list or retrieve full list
	std::vector<Item> getOrderList();
	Item getOrderList(Item i);

	void addToOrder(Item item);
	//Customer
	void addCustomer(Customer newCustomer);
	Customer getCustomer(int idNum);
	std::vector<Customer> getCustomerList();
	//Purchases
	void addPurchase(Purchase p);
	std::vector<Purchase> getPurchaseList();

	//Class Functions
	//Finds all purchases related to a customer
	std::vector<Purchase> findCustomerPurchases(Customer c);
	//Formats a chart to display a store's purchases, but would likely be better at Company level
	std::string displayPurchases(int year);
	//Major Transaction method, likely will have sub-methods
	Purchase transaction(Customer c, std::vector<Item> purchase);
	//Ran daily to remove expired items, and will return a string to log removed items
	std::string removeExpiredItems(int month, int day, int year);




};

#endif Store_H