#pragma once
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include<algorithm>


struct ExpirationDate
{
	ExpirationDate(int day, int month, int year, int quantity);
	int month, day, year, quantity;
	std::string toString();
	bool operator <(ExpirationDate expDate);
	bool operator ==(const ExpirationDate expDate);
};

struct Purchase;
//may be turned to struct and have store manage item quantity
struct Item
{
	float price;
	//MUST STILL IMPLIMENT
	std::string name;
	int dosage;
	//
	std::vector<Purchase> purchases;
	int vendorCode;
	int idNum, quantity, defaultStoreQuantity;
	int requiredRestock;    //The quantity at which the item must be refilled
	int restockQuantity;    //The quantity to refill the item to
	std::vector<ExpirationDate> expirationDates;
	//Item(int idNum, int quantity, float price, int requiredStock, int restockQuantity, std::vector<ExpirationDate> expDates);
	Item(int idNum, int defaultStoreQuantity, int requiredStock, int restockQuantity);
	Item(int idNum, int quantity, float price, int requiredRestock, int restockQuantity, std::vector<ExpirationDate> expDate);
	Item(int vendorCode, int idNum, int quantity, std::vector<ExpirationDate> expDate);
	Item() {}
	std::string allDataToString();
	std::string toString();
	std::string checkoutString();
	Item removeQuantity(int quantity);
	void addQuantity(Item stock);
	std::string getPurchaseHistory();
};

struct Insurance
{
	std::string name;
	int idNum;
	float copay;
	Insurance(int id, std::string name, float copay);
	std::string toString();
};


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
	std::string toString();
	std::string toNoCustomerString();
};
