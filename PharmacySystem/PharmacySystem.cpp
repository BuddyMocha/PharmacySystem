// PharmacySystem.cpp : Defines the entry point for the console application.
//Pharmacy System Main Menu: Includes functions related to logging onto the Pharmacy system

#include "stdafx.h"
#include "Item_ExpDate.h"
#include "Company_Warehouse.h"

/*
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>



using namespace std;

//struct Employee
//{
//	string name, username, password;
//};

vector<Employee> employeeList;
string currentUser;
bool LoggedIn = false;

//read in and store employee login info
void readEmployeeFile()
{
	ifstream file("EmployeeInfo.txt");
	vector<string> lines;
	string line;

	if (file.is_open())
	{
		while (getline(file, line))
		{
			//cout << line << '\n';
			lines.push_back(line);
		}
		file.close();

		for (unsigned int i = 0; i < lines.size(); i++)
		{
			line = lines[i];

			istringstream ss(line);
			string token;

			employeeList.push_back(Employee());

			getline(ss, token, ',');
			employeeList[i].name = token;

			getline(ss, token, ',');
			employeeList[i].username = token;

			getline(ss, token, ',');
			employeeList[i].password = token;

			//cout << Employees[i].name << endl;
			//cout << Employees[i].username << endl;
			//cout << Employees[i].password << endl;
		}
	}
	else cout << "Unable to open file";
}

//login to pharmacy system using employee info read from file
void employeeLogin()
{
	string userName;
	string password;
	bool found = false;

	readEmployeeFile();

	for (unsigned int i = 5; i > 0; i--)
	{
		cout << endl;
		cout << i << " tries remaining. \n";
		cout << "Enter your username and password.\n";
		cin >> userName >> password;


		for (unsigned int i = 0; i < employeeList.size(); i++)
		{
			if ((userName == employeeList[i].username) && (password == employeeList[i].password))
			{
				found = true;
				currentUser = employeeList[i].name;
				//cout << found << endl;
				break;
			}
		}

		if (found == true)
		{
			cout << "Access Granted. \n";
			LoggedIn = true;
			cout << "User: " << currentUser << endl;;
			break;
		}
		else
		{
			cout << "Access Denied. \n";
		}
	}
}

//sample function to show how a program could run 
//note: there is a bug that I havent figured out yet
void sampleProgram()
{
	int choice;

	cout << "Enter '0' to go back to the main menu. ";

	while (!(cin >> choice) || (choice != 0))
	{
		cout << endl;
		cout << "Please enter '0' to go back to the main menu. ";
		cin >> choice;
		cin.clear();
		cin.ignore(100, '\n');

		if (choice == 0)
		{
			break;
		}
	}
}

int main()
{
	int choice;
	bool systemOn = true;

	//employee login here
	employeeLogin();
	if (LoggedIn == false)
	{
		return 0;
	}

	while (systemOn != false)
	{
		cout << endl;
		cout << "********Pharmacy System*********\n";
		cout << "********************************\n";
		cout << " 1 - Customer Report Generation \n";
		cout << " 2 - Enter Transaction \n";
		cout << " 3 - Historical Sales Info \n";
		cout << " 4 - Item Data \n";
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


		switch (choice)
		{
		case 1:
			cout << endl;
			cout << "***Customer Report Generation***\n";
			cout << "********************************\n";
			// rest of code here
			sampleProgram();
			break;
		case 2:
			cout << endl;
			cout << "*******Enter Transaction********\n";
			cout << "********************************\n";
			// rest of code here
			sampleProgram();
			break;
		case 3:
			cout << endl;
			cout << "*****Historical Sales Info******\n";
			cout << "********************************\n";
			// rest of code here
			sampleProgram();
			break;
		case 4:
			cout << endl;
			cout << "***********Item Data************\n";
			cout << "********************************\n";
			// rest of code here
			sampleProgram();
			break;
		case 5:
			cout << endl;
			cout << "**Add, Delete, Edit Item Data***\n";
			cout << "********************************\n";
			// rest of code here
			sampleProgram();
			break;
		case 6:
			cout << endl;
			cout << "*********Employee Login*********\n";
			cout << "********************************\n";
			// rest of code here
			sampleProgram();
			break;
		case 7:
			cout << endl;
			cout << "*End Day (Process Batch Files)**\n";
			cout << "********************************\n";
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
*/

//Tester main
//Does NOT use namespace std, will need slight edits



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

