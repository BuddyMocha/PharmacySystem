#include "Company_Warehouse.h"
#include <iomanip>
#include <fstream>

Company::Company()
{
}

Company::Company(Warehouse warehouse, int day, int month, int year, std::vector<Store> stores, std::vector<Item> items, std::vector<Insurance> insurances)
	:warehouse(warehouse), day(day), month(month), year(year), storeChain(stores), stockableItems(items), insuranceProviders(insurances)
{
	customers = std::vector<Customer>();
}

//Adds a new stockable item
void Company::addItemToStock(Item i)
{
	for (int x = 0; x < stockableItems.size(); x++)
	{
		if (stockableItems[x].idNum == i.idNum)
		{
			std::cout << "Item addition canceled, item already exists." << std::endl;
			return;
		}
	};
	stockableItems.push_back(i);
}



//Deletes an allowed stockable item
void Company::deleteItemFromStock(int id)
{
	for (int x = 0; x < stockableItems.size(); x++)
	{
		if (stockableItems[x].idNum == id)
		{
			stockableItems.erase(stockableItems.begin() + x);
		}
	};
}

//Returns whether an item exists
bool Company::isItemInStock(int id)
{
	for (int x = 0; x < stockableItems.size(); x++)
	{
		if (stockableItems[x].idNum == id)
		{
			return true;
		}
	};
	return false;
}

//Returns stockable items
std::vector<Item>* Company::getItemList()
{
	return &stockableItems;
}

Item* Company::getItem(int id)
{
	for (int x = 0; x < stockableItems.size(); x++)
	{
		if (stockableItems[x].idNum = id)
		{
			return &stockableItems[x];
		}
	}
	return nullptr;
}

//GEts item from warehouse with id
Item* Warehouse::getItem(int idNum)
{
	for (int x = 0; x < inventory.size(); x++)
	{
		if (inventory[x].idNum = idNum)
		{
			return &inventory[x];
		}
	}
	return nullptr;
}

//Takes an item and adds it to the warehouse
bool Company::addInventoryToWarehouse(Item item)
{
	if (isItemInStock(item.idNum))
	{
		for (int x = 0; x < warehouse.inventory.size(); x++)
		{
			if (warehouse.inventory[x].idNum == item.idNum)
			{
				warehouse.inventory[x].addQuantity(item);
				return true;
			}
		}
		warehouse.inventory.push_back(item);
		return true;
	}
	else
	{
		return false;
	}
}

//Sends items from the warehouse to a store, will be done overnight so need a log to save data
void Company::sendItems(std::vector<Item> order, Store destination)
{
	std::vector<Item> completedOrder;
	for (int x = 0; x < order.size(); x++)
	{
		Item* warehouseItem = warehouse.getItem(order[x].idNum);
		if (warehouseItem != nullptr)
		{
			if (warehouseItem->quantity >= order[x].quantity)
			{
				completedOrder.push_back(warehouseItem->removeQuantity(order[x].quantity));
			}
			else if (warehouseItem->quantity > 0)
			{
				completedOrder.push_back(warehouseItem->removeQuantity(warehouseItem->quantity));
				//Log not sufficient quantity, order from vendor
			}
			else
			{
				//Log no item quantity, order from vendor
			}
		}
		else
		{
			//Log that item was not found in warehouse
		}
	}
	for (int x = 0; x < completedOrder.size(); x++)
	{
		destination.addItemtoInv(completedOrder[x]);
	}
}

//Adds employee with specified argument
void Company::addEmployee(Employee e)
{
	employeeList.push_back(e);
}

//Adds store with specified argument if the ID doesn't exist
void Company::addStore(Store s)
{
	for (int x = 0; x < storeChain.size(); x++)
	{
		if (storeChain[x].getID() == s.getID())
		{
			std::cout << "Store addition canceled, store already exists." << std::endl;
			return;
		}
	}
	storeChain.push_back(s);
}

//Deletes Store with Given ID
void Company::deleteStore(int id)
{
	for (int x = 0; x < storeChain.size(); x++)
	{
		if (storeChain[x].getID() == id)
		{
			storeChain.erase(storeChain.begin() + x);
		}
	}
}

//Gets store with given ID
Store* Company::getStore(int id)
{
	for (int x = 0; x < storeChain.size(); x++)
	{
		if (storeChain[x].getID() == id)
		{
			return &storeChain[x];
		}
	}
	std::cout << "Store ID not found, please input a valid ID number." << std::endl;
	return nullptr;
}

//Adds new allowed insurance to the company's database
void Company::addInsurance(Insurance i)
{
	for (int x = 0; x < customers.size(); x++)
	{
		if (insuranceProviders[x].idNum == i.idNum)
		{
			std::cout << "Insurance addition canceled, insurance already exists." << std::endl;
			return;
		}
	}
	insuranceProviders.push_back(i);
}

//Gets insurance based off the ID number, and checks if it is supported from the database
Insurance* Company::getInsurance(int idNum)
{
	for (int x = 0; x < insuranceProviders.size(); x++)
	{
		if (insuranceProviders[x].idNum == idNum)
		{
			return &insuranceProviders[x];
		}
	}
	std::cout << "Insurance not found, please input valid ID number." << std::endl;
	return nullptr;
}

//Adds customer from argument unless phoneNum is already registered
void Company::addCustomer(Customer newCustomer) {
	for (int x = 0; x < customers.size(); x++)
	{
		if (customers[x].phoneNum == newCustomer.phoneNum)
		{
			std::cout << "Customer addition canceled, customer already exists." << std::endl;
			return;
		}
	}
	customers.push_back(newCustomer);
}

//Called from the transaction method, this adds a customer to the company's database
void Company::createCustomer()
{
	std::string phoneNum = "";
	std::string name = "";
	std::string address = "";
	std::string input = "";
	Insurance* insurance = nullptr;
	int idNum = -1;
	std::cout << "Please input the new customer's 10-digit phone number." << std::endl;
	while (phoneNum.length() != 10)
	{
		std::getline(std::cin, phoneNum);
		if (phoneNum.length() != 10)
		{
			std::cout << "The inputted phone # was not 10 digits. Please try again." << std::endl;
		}
	}
	if (getCustomer(phoneNum) == nullptr)
	{
		std::cout << "Please input the new customer's name." << std::endl;
		std::getline(std::cin, name);
		std::cout << "Please input the new customer's address." << std::endl;
		std::getline(std::cin, address);
		while (insurance == nullptr)
		{
			std::cout << "Please input the ID number for the new customer's insurance" << std::endl;
			std::cout << "ID:1, Blue Cross Blue Shield " << std::endl;
			std::cout << "ID:2, Humana" << std::endl;
			std::cout << "ID:3, UnitedHealthcare" << std::endl;
			std::cout << "ID:4, Aetna" << std::endl;
			std::getline(std::cin, input);
			std::stringstream stream(input);
			if (stream >> idNum)
			{
				insurance = getInsurance(idNum);
			}

		}
		addCustomer(Customer(name, address, phoneNum, insurance));
		return;
	}
	else
	{
		std::cout << "This phone number already belongs to a customer's account, creation canceled." << std::endl;
		return;
	}
}
//Returns customer object from given phone number
Customer* Company::getCustomer(std::string phoneNum) {
	for (int x = 0; x < customers.size(); x++)
	{
		if (customers[x].phoneNum == phoneNum)
		{
			return &customers[x];
		}
	}
	//std::cout << "Customer not found, please input valid phone # without dashes." << std::endl;
	return nullptr;
}
//Full transaction method, does not currently allow backing out of transaction
void Company::transaction()
{
	bool finished = false;
	Store* currentStore = nullptr;
	Customer* customer = nullptr;
	int inputNum = -1;
	std::string input = "";
	//Find store
	std::cout << "Please input the ID number of the store you are purchasing from." << std::endl;
	while (currentStore == nullptr)
	{
		
		std::getline(std::cin, input);
		std::stringstream stream(input);
		if (stream >> inputNum)
		{
			currentStore = getStore(inputNum);
		}
		else
		{
			std::cout << "Invalid store ID, please input a valid ID number." << std::endl;
		}
	}
	//Get customer
	std::cout << "Please input the 10 digit phone number of the customer, or enter \"n\" to enter a new customer." << std::endl;
	inputNum = -1;
	input = "";
	while (customer == nullptr)
	{
		std::getline(std::cin, input);
		if (input.length() == 10)
		{
			customer = getCustomer(input);
		}
		else if(input.length() == 1 && input == "n")
		{
			std::cout << "Creating new customer." << std::endl;
			createCustomer();
			std::cout << "Please input the phone number of the newly created account." << std::endl;
		}
		else
		{
			std::cout << "Please enter a valid input." << std::endl;
		}
	}
	//Get referral if available
	input = "";
	std::cout << "Was this customer referred? If so, input the referrer's phone #. Else input \"n\" to continue." << std::endl;
	while (input != "n")
	{
		input = "";
		std::getline(std::cin, input);
		Customer* referrer = getCustomer(input);
		if (input.length() == 10 && referrer != nullptr)
		{
			referrer->numReferrals++;
			input = "n";
		}
		else if(input.length() == 10 && referrer == nullptr)
		{
			std::cout << "This number does not have an account." << std::endl;
		}
		else if(input != "n")
		{
			std::cout << "Please enter \"n\" or a valid 10-digit phone number." << std::endl;
		}
	}
	//Find Items and Remove from stock
	input = "";
	std::cout << "Please enter the ID number of the product being purchased, and \"n\" to finalize the transaction." << std::endl;
	std::cout << "The customer may only purchase 5 items per transaction." << std::endl;
	int quantityPurchased = 0;
	std::vector<Item> purchase;
	while (input != "n")
	{
		int quantityRequested = 0;
		input = "";
		std::getline(std::cin, input);
		std::stringstream stream(input);
		if (stream >> inputNum)
		{
			if (currentStore->getItem(inputNum) != nullptr && quantityPurchased < 5)
			{
				std::cout << currentStore->getItem(inputNum)->toString() << std::endl;
				std::cout << "\nWhat quantity of this item do you wish to purchase?" << std::endl;
				std::getline(std::cin, input);
				stream.clear();
				stream.str(input);
				if (stream >> quantityRequested)
				{
					if (quantityRequested + quantityPurchased <= 5)
					{
						quantityPurchased += quantityRequested;
						purchase.push_back(currentStore->getItem(inputNum)->removeQuantity(quantityRequested));

						std::cout << purchase[0].allDataToString() << std::endl;
						if (quantityRequested + quantityPurchased < 5)
						{
							std::cout << "Please enter the ID number of the product being purchased, and \"n\" to finalize the transaction." << std::endl;
						}
						else
						{
							std::cout << "Five items have been added to the cart, proceeding to checkout." << std::endl;
							input = "n";
						}
					}
					else
					{
						std::cout << "Only 5 items can be purchased in total. You have currently added "<< quantityPurchased << "items to the cart." << std::endl;
					}
				}
				else
				{
					std::cout << "Please enter a value between 1 and 5." << std::endl;
				}

			}
			else
			{
				std::cout << "Five items have been added to the cart, proceeding to checkout." << std::endl;
				input = "n";
			}
		}
		
	}

	//2nd employee confirms transaction
	while(!verifyEmployee())
	
	//Show cart, cost, and deduct referral & insurance amount

	std::cout << "Cart:" << std::endl;
	float price = 0;
	for (int x = 0; x < purchase.size(); x++)
	{
		std::cout << purchase[x].checkoutString() << std::endl;
		price += purchase[x].price * purchase[x].quantity;
	}
	std::cout << "Insurance reduction: " << customer->insurance->copay << std::endl;
	//Getting copay:
	price = price * (1 - customer->insurance->copay);
	std::cout << std::fixed << std::setprecision(2);
	std::cout << "The total for your order is: " << price << std::endl;
	bool referral = false;
	if (customer->numReferrals > 0)
	{
		referral = true;
		std::cout << "You currently have " << customer->numReferrals << " referrals. One will be used, and you will get 5% off your order." << std::endl;
		std::cout << "Your new total is: ";
		//std::cout << std::fixed << std::setprecision(2);
		std::cout << price << std::endl;
	}
	std::cout << "Input the amount given to determine change, or input \"n\" to conclude checkout." << std::endl;
	float money = 0;
	input = "";
	while (input != "n")
	{
		input = "";
		std::getline(std::cin, input);
		std::stringstream stream(input);
		if (stream >> money)
		{
			if (money >= price)
			{
				money -= price;
				std::cout << "Your change is " << money << std::endl;
				input = "n";
			}
			else
			{
				std::cout << "Money given must be more than the purchace's price." << std::endl;
			}
		}
		else if (input != "n")
		{
			std::cout << "Please input a numerical value for change, or \"n\" to exit." << std::endl;
		}
	}
	currentStore->addPurchase(Purchase(referral, day, month, year, customer, price, purchase));
	return;
	//send purchase to list
}

void Company::readEmployeeFile()
{
	std::ifstream file("EmployeeInfo.txt");
	std::vector<std::string> lines;
	std::string line;

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

			std::istringstream ss(line);
			std::string token;

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
	else std::cout << "Unable to open file";
}

//login to pharmacy system using employee info read from file
void Company::employeeLogin()
{
	std::string userName;
	std::string password;
	bool found = false;

	readEmployeeFile();

	for (unsigned int i = 5; i > 0; i--)
	{
		std::cout << std::endl;
		std::cout << i << " tries remaining. \n";
		std::cout << "Enter your username and password.\n";
		std::cin >> userName >> password;


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
			std::cout << "Access Granted. \n";
			loggedIn = true;
			break;
		}
		else
		{
			std::cout << "Access Denied. \n";
		}
	}
}

//Verifies second employees credentials to allow transaction to be processed
bool Company::verifyEmployee()
{
	std::string userName;
	std::string password;
	bool found = false;

	for (unsigned int i = 5; i > 0; i--)
	{
		std::cout << std::endl;
		std::cout << i << " tries remaining. \n";
		std::cout << "You need to have another employee verify this. \n";
		std::cout << "Enter their username and password.\n";
		std::cin >> userName >> password;

		for (unsigned int i = 0; i < employeeList.size(); i++)
		{
			if ((userName == employeeList[i].username) && (password == employeeList[i].password) && (employeeList[i].name != currentUser))
			{
				found = true;
				//cout << found << endl;
				break;
			}
		}

		if (found == true)
		{
			std::cout << "Valid Credentials. \n";
			return true;
			break;
		}
		else
		{
			std::cout << "Invalid Credentials. \n";
		}
	}

	return false;
}

//Get todays date
void Company::getTodaysDate()
{
	time_t today = time(0);
	struct tm *now = localtime(&today);

	year = now->tm_year + 1900;
	month = now->tm_mon + 1;
	day = now->tm_mday;
}

//Setup date structure
void Company::setupDate()
{
	date = { 0, 0, 0, 12 };

	//Set up the date structure
	date.tm_year = year - 1900;
	date.tm_mon = month - 1;		//note: zero indexed
	date.tm_mday = day;				//note: not zero indexed
}

//Add to a date
void Company::datePlusDays(int days)
{
	const time_t ONE_DAY = 24 * 60 * 60;

	//Seconds since start of epoch
	time_t date_seconds = mktime(&date) + (days * ONE_DAY);

	//Update caller's date
	//Use localtime because mktime converts to UTC so may change date
	date = *localtime(&date_seconds);
}

//Update date
void Company::updateDate()
{
	year = date.tm_year + 1900;
	month = date.tm_mon + 1;
	day = date.tm_mday;
}

bool Company::getLoggedIn()
{
	return loggedIn;
}
std::string Company::getCurrentUser()
{
	return currentUser;
}
int Company::getDay()
{
	return day;
}
int Company::getMonth()
{
	return month;
}
int Company::getYear()
{
	return year;
}