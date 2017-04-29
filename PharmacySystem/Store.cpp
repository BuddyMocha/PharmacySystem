#include "Store_Customer_Insurance_Purchase.h"

Insurance::Insurance(int id, std::string name, float copay)
	:idNum(id), name(name), copay(copay)
{

}

Store::Store(int idNum, std::string streetAddress, std::string city, std::string state, int zipCode, int priority)
	:idNum(idNum), streetAddress(streetAddress), city(city), state(state), zipCode(zipCode), priority(priority)
{ 

}



Customer::Customer(std::string name, std::string address, std::string phoneNum, Insurance* insurance)
	:name(name), address(address), phoneNum(phoneNum), insurance(insurance)
{
	numReferrals = 0;
}

Purchase::Purchase(bool referred, int day, int month, int year, Customer* customer, float cost, std::vector<Item> transaction)
	:referred(referred), day(day), month(month), year(year), customer(customer), cost(cost), transaction(transaction)
{

}

std::string Insurance::toString()
{
	std::stringstream output;
	output << "Insurance ID: " << idNum << "   Copay: " << copay << "\n";
	return output.str();
}

std::string Customer::toString()
{
	std::stringstream output;
	output << "Name: " << name << "     Phone #: " << phoneNum << "\n";
	output << "    Address: " << address << "\n";
	output << "    " << insurance->toString() << "\n";

	return output.str();
}

int Store::getID(){
	return idNum;
}

int Store::getPriority(){
	return priority;
}

std::vector<Purchase>& Store::getPurchaseList()
{
	return transactions;
}

void Store::setPriority(int p){
	priority = p;
}

void Store::addItemtoInv(Item item){
	for (int x = 0; x < inventory.size(); x++)
	{
		if (inventory[x].idNum == item.idNum)
		{
			inventory[x].addQuantity(item);
			return;
		}
	}
	inventory.push_back(item);
}

//Removes only a specific quantity of an item
Item Store::removeItemFromInv(int idNum, int quantity)
{
	Item* item = getItem(idNum);
	Item realItem = item->removeQuantity(quantity);
	return realItem;
}

//Removes an item from the inventory completely and returns the item
Item Store::removeItemFromInv(int idNum)
{
	for (int x = 0; x < inventory.size(); x++)
	{
		if (inventory[x].idNum == idNum)
		{
			Item item = inventory[x].removeQuantity(inventory[x].quantity);
			inventory.erase(inventory.begin() + x);
			return item;
		}
	}
	return Item(-1, -1, (float) -1, -1, -1, std::vector<ExpirationDate>());
}


Item* Store::getItem(int id)
{
	for (int x = 0; x < inventory.size(); x++)
	{
		if (inventory[x].idNum == id)
		{
			return &inventory[x];
		}
	}
	return nullptr;
}

void Store::addPurchase(Purchase p)
{
	transactions.push_back(p);
}

//Used at end of day routine to remove expired items and sort expiration dates. Can use removeItemFromInventory() to return & save the expired item somewhere
std::string Store::removeExpiredItems(int day, int month, int year)
{
	std::stringstream output;
	ExpirationDate date(day, month, year, 0);
	for (int x = 0; x < inventory.size(); x++)
	{
		//Sorts all expiration dates daily during overnight cycle, and removes the expired ones
		std::sort(inventory[x].expirationDates.begin(), inventory[x].expirationDates.end());
		//for (int y = 0; y < inventory[x].expirationDates.size(); x++)
		//{
			if (inventory[x].expirationDates[0] < date || inventory[x].expirationDates[0] == date)
			{
				inventory[x].quantity -= inventory[x].expirationDates[0].quantity;
				output << "Removed " << inventory[x].expirationDates[0].quantity << " expired items of ID " << inventory[x].idNum << "\n";
				inventory[x].expirationDates.erase(inventory[x].expirationDates.begin()); // + y
			}
			else
			{

			}
		//}
	}
	return output.str();
}

//MUST be tested
void Store::editItemData()
{
	std::stringstream stream;
	int idNum = -1;
	int changeData = -1;
	float price = (float) -1;
	std::string input = "";
	Item* item;
	while (input != "x")
	{
		std::cout << "Please input the ID number for the item you wich to change, or \"x\" to exit" << std::endl;
		std::cin >> input;
		stream.clear();
		stream.str(input);
		if (stream >> idNum && getItem(idNum) != nullptr)
		{
			item = getItem(idNum);
			
			while (input != "x" && input != "0")
			{
				std::cout << item->allDataToString() << std::endl;
				std::cout << "Please input corresponding number for the data you wish to edit, or \"x\" to exit" << std::endl;
				std::cout << "1. Price" << std::endl;
				std::cout << "2. Restock at X quantity" << std::endl;
				std::cout << "3. Restock to X quantity" << std::endl;
				std::cout << "0. Choose another item" << std::endl;
				std::cin >> input;
				stream.clear();
				stream.str(input);
				if (stream >> idNum && idNum >= 1 && idNum <= 3)
				{
					while (input != "x")
					{
						if (idNum == 1)
						{
							std::cout << "Please input value you wish to change the price to." << std::endl;
							std::cin >> input;
							stream.clear();
							stream.str(input);
							if (stream >> price && price > 0)
							{
								item->price = price;
								break;
							}
							else
							{
								std::cout << "Please input a valid price, or \"x\" to exit" << std::endl;
							}
						}
						else if (idNum == 2)
						{
							std::cout << "Please input value you wish to change the restock at X quantity to." << std::endl;
							std::cin >> input;
							stream.clear();
							stream.str(input);
							if (stream >> changeData && changeData >= 0)
							{
								item->requiredRestock = changeData;
								break;
							}
							else
							{
								std::cout << "Please input a valid restock quantity, or \"x\" to exit" << std::endl;
							}
						}
						else if (idNum == 3)
						{
							std::cout << "Please input value you wish to change the restock to X quantity to." << std::endl;
							std::cin >> input;
							stream.clear();
							stream.str(input);
							if (stream >> changeData && changeData > 0)
							{
								item->restockQuantity = changeData;
								break;
							}
							else
							{
								std::cout << "Please input a valid restock quantity > 0, or \"x\" to exit" << std::endl;
							}
						}

					}
				}
				else if(input != "0")
				{
					std::cout << "Please input a valid value, or \"x\" to exit" << std::endl;
				}
			}

		}
		else
		{
			std::cout << "Please input a valid value, or \"x\" to exit" << std::endl;
		}
	}
	return;
}

std::string Store::getPurchaseHistory()
{
	std::string input;
	for (int x = 0; x < transactions.size(); x++)
	{
		input += transactions[x].toString() + "\n";
	}
	return input;
}

std::string Store::toString()
{
	std::string output;
	output = "Address: " + streetAddress + ", City: " + city + ", State: " + state + "\n";
	for (int x = 0; x < inventory.size(); x++)
	{
		output += inventory[x].toString();
	}

	return output;
}
void Store::deleteItem(int idNum)
{
	for (int x = 0; x < inventory.size(); x++)
	{
		if (inventory[x].idNum == idNum && inventory[x].quantity == 0)
		{
			inventory.erase(inventory.begin() + x);
		}
	}

}

std::vector<Item> Store::getItemList()
{
	return inventory;
}

Order::Order(int itemID, int quantity, int storeID, int priority)
	:itemID(itemID), quantity(quantity), storeID(storeID), priority(priority)
{

}

void Store::restockStore()
{
	for (int x = 0; x < inventory.size(); x++)
	{
		if (inventory[x].requiredRestock > inventory[x].quantity)
		{
			currentOrder.push_back(Order(inventory[x].idNum, inventory[x].restockQuantity - inventory[x].quantity, idNum, priority));
		}
	}
}




