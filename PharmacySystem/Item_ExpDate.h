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

//may be turned to struct and have store manage item quantity
struct Item
{
	float price;
	//MUST STILL IMPLIMENT
	std::string name;
	int dosage;
	//
	int idNum, quantity, defaultStoreQuantity;
	int requiredRestock;    //The quantity at which the item must be refilled
	int restockQuantity;    //The quantity to refill the item to
	std::vector<ExpirationDate> expirationDates;
	//Item(int idNum, int quantity, float price, int requiredStock, int restockQuantity, std::vector<ExpirationDate> expDates);
	Item(int idNum, int defaultStoreQuantity, int requiredStock, int restockQuantity);
	std::string allDataToString();
	std::string toString();
	std::string checkoutString();
	Item removeQuantity(int quantity);
	void addQuantity(Item stock);
};
