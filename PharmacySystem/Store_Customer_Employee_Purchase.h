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

struct Employee
{
	std::string name, username, password;
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
	Store(std::string name, int idNum, int priority, std::vector<Employee> employees);
	//Getters and setters for private vars
	//Priority
	int getPriority();
	void setPriority(int priority);
	//Inventory
	void addItemtoInv(Item item);
	std::vector<Item> getItemList();
		//Overloaded, first definition takes a specific quantity of an item, the second removes the item from inventory completely
	Item removeItemFromInv(Item item, int quantity);
	Item removeItemFromInv(Item item);
	//Restock order list
	std::vector<Item> getOrderList();
	void addToOrder(Item item);
	//Employee
	std::vector<Employee> getEmployees();
	//Customer
	void addCustomer(Customer newCustomer);
	Customer getCustomer(int idNum);
	std::vector<Customer> getCustomerList();






};

#endif Store_H