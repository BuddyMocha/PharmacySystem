#pragma once

#ifndef Store_H
#define Store_H
#include "Item.h"
#include <vector>
struct Insurance
{
	std::string name;
	float copay;
};

struct Customer
{
	std::string name, address;
	int phoneNum, id;
	Insurance insurance;
};

struct Employee
{
	std::string name, username, password;
};

struct Purchase
{
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
	Store(std::string name, int idNum, int priority, std::vector<Employee> employees);
};

#endif Store_H