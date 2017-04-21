// PharmacySystem.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Item_ExpDate.h"
#include "Company_Warehouse.h"
#include <iostream>


int main()
{
	Warehouse testStock;
	ExpirationDate testDate1 = ExpirationDate(12, 12, 17, 3);
	ExpirationDate testDate2 = ExpirationDate(13, 12, 17, 7);
	std::vector<ExpirationDate> testDateVector;
	testDateVector.push_back(testDate1);
	testDateVector.push_back(testDate2);

	Item testItem = Item(1, 10, 1.25f, 5, 15, testDateVector);

	testStock.inventory.push_back(testItem);

	Store store = Store(1, 0);
	store.addItemtoInv(testItem);

	std::vector<Store> testStoreVector;
	testStoreVector.push_back(store);

	Insurance testInsurance(1, .01f);
	std::vector<Insurance> testInsuranceVector;
	testInsuranceVector.push_back(testInsurance);

	Company company = Company(testStock, 13, 4, 17, testStoreVector, testStock.inventory, testInsuranceVector);
	Employee employee;
	employee.name = "John";
	employee.username = "username";
	employee.password = "password";

	//std::cout << company.getStore(1)->getItem(1)->allDataToString() << std::endl;

	//std::cout << company.getStore(1)->getItem(1)->removeQuantity(4).allDataToString() << std::endl;

	//std::cout << company.getStore(1)->getItem(1)->allDataToString() << std::endl;


	
	Customer testCustomer = Customer("Brad", "1212 B-Ball Ct.", "7345559059", company.getInsurance(1));
	company.addCustomer(testCustomer);
	company.transaction();

	system("PAUSE");
    return 0;
}

