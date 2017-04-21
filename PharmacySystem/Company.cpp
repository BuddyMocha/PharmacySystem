#include "Company_Warehouse.h"
#include <iomanip>


Company::Company(Warehouse warehouse, int day, int month, int year, std::vector<Store> stores, std::vector<Item> items, std::vector<Insurance> insurances)
	:warehouse(warehouse), day(day), month(month), year(year), storeChain(stores), stockableItems(items), insuranceProviders(insurances)
{

	customers = std::vector<Customer>();
}

void Company::addEmployee(Employee e)
{
	employeeList.push_back(e);
}

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
		std::cout << "This phone number already belongs to a customer's account." << std::endl;
		return;
	}
}

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

void Company::transaction()
{
	bool finished = false;
	Store* currentStore = nullptr;
	Customer* customer = nullptr;
	int inputNum = -1;
	std::string input = "";
	bool referred;
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
	std::cout << "Cart:" << std::endl;
	float price = 0;
	for (int x = 0; x < purchase.size(); x++)
	{
		std::cout << purchase[x].checkoutString() << std::endl;
		price += purchase[x].price * purchase[x].quantity;
	}
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
