// PharmacySystem.cpp : Defines the entry point for the console application.
//Pharmacy System Main Menu: Includes functions related to logging onto the Pharmacy system

#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>

#include "stdafx.h"
#include "Item_ExpDate.h"
#include "Company_Warehouse.h"

using namespace std;

#include "checkFile.h"//checks for existing file AND empty file
#include "checkHeader.h"//checks header and rejects text file if conditions not met
#include "checkTrailer.h"//checks trailer

#include "AddDeleteStore.h"
#include "StoreUpdate.h"
#include "ItemReceived.h"
#include "VendorOrder.h"//function for processing vendororder.txt
#include "Items.h"
#include "Reports.h"//function for processing reports.txt

#include "batch2program.h"


#include "PharmacyFunctions.h"//William's stuff

int main()
{
	Company company;
	/*
	Customer c((std::string)"Bob", (std::string) "Address", (std::string)"1231231232", new Insurance(1, "Blue Cross", .10));
	std::vector<ExpirationDate> exp = { ExpirationDate(10,11,18,2) };
	std::vector<Item> i= { Item(1, 2, 2.00f, 10, 20, exp), Item(3, 2, 2.50f, 15, 25, exp) };
	Purchase p(false, 31, 12, 96, &c, 21.42f, i);
	c.purchases.push_back(&p);
	cout << c.getPurchaseHistory() << endl;
	company.addCustomer(c);

	
	Store s(1, (std::string) "address", (std::string) "city", (std::string) "state", 12345, 1);
	std::vector<ExpirationDate> exp = { ExpirationDate(10,11,18,2) };
	s.addItemtoInv(Item(1, 2, 2.00f, 10, 20, exp));
	company.addStore(s);
	*/
	ofstream fout("ERRORS.TXT");
	fout.clear();

	vector<addDeleteStoreClass> addDeleteStore;
	vector<itemReceivedClass> itemReceived;
	vector<storeUpdateClass> storeUpdate;
	vector<vendorOrderClass> vendorOrder;
	vector<itemsClass> items;
	vector<reportsClass> reports;//vector or reports class that will hold yearlySales.txt information

	int addDeleteStoreSeq = 102;
	int storeUpdateSeqCREATESTORE = 52;
	int storeUpdateSeqINVENTORYREVIEW = 52;
	int storeUpdateSeqONLINEREQUEST = 52;
	int itemReceivedSeq = 9999;
	int itemReceivedSeqDELSTORE = 9999;
	int itemsSeq = 9999;
	int vendorOrderSeq = 5001;
	int reportsSeq = 0;//expected sequence number of reports.txt (number will be increased by yearlySales.h)
	std::string input;
	int choice;
	bool systemOn = true;
	//employee login here
	company.employeeLogin();

	if (company.getLoggedIn() == false)
	{
		return 0;
	}
	company.getTodaysDate();
	company.setupDate();

	while (systemOn != false)
	{
		cout << endl;
		cout << "Current User: " << company.getCurrentUser() << endl;;
		cout << "Todays Date: " << company.getMonth() << "/" << company.getDay() << "/" << company.getYear() << endl;
		cout << endl;
		cout << "********Pharmacy System*********\n";
		cout << "********************************\n";
		cout << " 1 - Customer Report Generation \n";
		cout << " 2 - Enter Transaction \n";
		cout << " 3 - Historical Sales Info \n";
		cout << " 4 - Store Data \n";
		cout << " 5 - Add, Delete, Edit Item Data \n";
		cout << " 6 - Employee Login \n";
		cout << " 7 - End Day (Process Batch Files) \n";
		cout << " 8 - Exit.\n";
		cout << endl;
		cout << " Enter your choice and press return: ";

		while (!(cin >> choice))
		{
			cout << endl;
			cout << "Please choose a valid option: ";
			cin >> choice;
			cin.clear();
			cin.ignore(100, '\n');
		}

		vector<Store> stores;

		switch (choice)
		{
		case 1:
			cout << endl;
			cout << "***Customer Report Generation***\n";
			cout << "********************************\n";
			// rest of code here
			company.customerReportGen();
			break;
		case 2:
			cout << endl;
			cout << "*******Enter Transaction********\n";
			cout << "********************************\n";
			company.transaction();
			break;
		case 3:
			cout << endl;
			cout << "*****Historical Sales Info******\n";
			cout << "********************************\n";
			// rest of code here
			company.historicalSales();
			break;
		case 4:
			cout << endl;
			cout << "***********Store Data************\n";
			cout << "********************************\n";
			// rest of code here
			cout << "Please input the ID for the store you wish to view." << endl;
			cin >> choice;
			if (company.getStore(choice) != nullptr)
			{
				cout << company.getStore(choice)->toString() << endl;
			}
			break;
		case 5:
			cout << endl;
			cout << "**Add, Delete, Edit Item Data***\n";
			cout << "********************************\n";
			cout << "Please input the store ID for the items you wish to edit." << endl;
			cin >> choice;
			if (company.getStore(choice) != nullptr)
			{
				company.getStore(choice)->editItemData();
			}
			break;
		case 6:
			cout << endl;
			cout << "*********Change Employee Logged in*********\n";
			cout << "*******************************************\n";
			// rest of code here
			company.employeeLogin();
			break;
		case 7:
			cout << endl;
			cout << "*End Day (Process Batch Files)**\n";
			cout << "********************************\n";
			cout << company.removeExpiredItems() << endl;

			addDeleteStore.clear();
			itemReceived.clear();
			vendorOrder.clear();
			items.clear();
			reports.clear();
			storeUpdate.clear();

			addDeleteStore = AddDeleteStore(addDeleteStore, addDeleteStoreSeq);
			
			itemReceived = ItemReceived(itemReceived, itemReceivedSeq, "itemreceived.txt");
			//itemReceived = ItemReceived(itemReceived, itemReceivedSeqDELSTORE, "itemreceivedDELSTORE.txt");
			vendorOrder = VendorOrder(vendorOrder, vendorOrderSeq);
			items = Items(items, itemsSeq);
			reports = Reports(reports, reportsSeq);//processes reports.txt

			addStoreAndItems2company(addDeleteStore, company);
			items2warehouse(itemReceived, company);

			writeStoreUpdateCREATESTORE(addDeleteStore, storeUpdateSeqCREATESTORE);

			storeUpdate = StoreUpdate(storeUpdate, storeUpdateSeqCREATESTORE, "storeupdateCREATESTORE.txt");
			//storeUpdate = StoreUpdate(storeUpdate, storeUpdateSeqINVENTORYREVIEW, "storeupdateINVENTORYREVIEW.txt");
			//storeUpdate = StoreUpdate(storeUpdate, storeUpdateSeqONLINEREQUEST, "storeupdateONLINEREQUEST.txt");

			warehouse2store(storeUpdate, company);
			/*Bra
			stores = company.getStoreChain();
			for (int i = 0; i < stores.size(); i++)
			{
				cout << stores[i].getID() << endl;
			}
			*/
			deleteStore(addDeleteStore, company, itemReceivedSeqDELSTORE);

			//Date plus one day
			company.datePlusDays(1);
			//Change current date to new date
			company.updateDate();

			// check expiration dates
			// process batch files
			// rest of code here
			sampleProgram();
			break;
		case 8:
			cout << endl;
			cout << "******System Shutting Down******\n";
			cout << "********************************\n";
			systemOn = false;
			break;
		default:
			cout << endl;
			cout << "Not a Valid Choice. \n";
			cout << "Choose again.\n";
			//cin >> choice;
			break;
		}
	}
	
	return 0;
}

/*
//Tester main
//Does NOT use namespace std, will need slight edits


/*
int main()
{
	Warehouse testStock;
	ExpirationDate testDate1 = ExpirationDate(12, 12, 16, 3);
	ExpirationDate testDate2 = ExpirationDate(13, 12, 17, 7);
	ExpirationDate testDate3 = ExpirationDate(13, 11, 18, 7);
	ExpirationDate testDate4 = ExpirationDate(14, 12, 17, 7);
	ExpirationDate testDate5 = ExpirationDate(12, 12, 17, 7);
	std::vector<ExpirationDate> testDateVector1;
	testDateVector1.push_back(testDate1);
	testDateVector1.push_back(testDate2);
	testDateVector1.push_back(testDate3);
	testDateVector1.push_back(testDate4);
	testDateVector1.push_back(testDate5);

	ExpirationDate testDate6 = ExpirationDate(17, 8, 17, 3);
	ExpirationDate testDate7 = ExpirationDate(19, 12, 17, 7);
	ExpirationDate testDate8 = ExpirationDate(13, 11, 18, 7);
	ExpirationDate testDate9 = ExpirationDate(14, 2, 16, 7);
	ExpirationDate testDate10 = ExpirationDate(11, 5, 17, 7);
	std::vector<ExpirationDate> testDateVector2;
	testDateVector2.push_back(testDate6);
	testDateVector2.push_back(testDate7);
	testDateVector2.push_back(testDate8);
	testDateVector2.push_back(testDate9);
	testDateVector2.push_back(testDate10);

	Item testItem1 = Item(1, 31, 1.25f, 5, 15, testDateVector1);
	Item testItem2 = Item(1, 31, 1.25f, 5, 15, testDateVector2);

	std::cout << testItem1.allDataToString() << "\n" << std::endl;
	std::cout << testItem2.allDataToString() << "\n" << std::endl;
	std::cout << "Adding quantities" << "\n" << std::endl;
	testItem1.addQuantity(testItem2);
	std::cout << testItem1.allDataToString() << std::endl;

	testStock.inventory.push_back(testItem1);

	Store store = Store(1, 0);
	store.addItemtoInv(testItem1);

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


	
	//Customer testCustomer = Customer("Brad", "1212 B-Ball Ct.", "7345559059", company.getInsurance(1));
	//company.addCustomer(testCustomer);
	//company.transaction();


	system("PAUSE");
    return 0;
}

*/
