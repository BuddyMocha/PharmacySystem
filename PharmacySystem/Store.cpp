#include "Store_Customer_Insurance_Purchase.h"

Insurance::Insurance(int id, float copay)
	:idNum(id), copay(copay)
{

}

Store::Store(int idNum, int priority)
	:idNum(idNum), priority(priority) 
{ 
}

Customer::Customer(std::string name, std::string address, std::string phoneNum, Insurance* insurance)
	:name(name), address(address), phoneNum(phoneNum), insurance(insurance)
{

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

void Store::setPriority(int p){
	priority = p;
}

void Store::addItemtoInv(Item item){
	for (int x = 0; x < inventory.size(); x++)
	{
		if (inventory[x].idNum = item.idNum)
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
		if (inventory[x].idNum = idNum)
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
		if (inventory[x].idNum = idNum)
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
std::string Store::removeExpiredItems(int month, int day, int year)
{
	std::stringstream output;
	ExpirationDate date(day, month, year, 0);
	for (int x = 0; x < inventory.size(); x++)
	{
		//Sorts all expiration dates daily during overnight cycle, and removes the expired ones
		std::sort(inventory[x].expirationDates.begin(), inventory[x].expirationDates.end());
		for (int y = 0; y < inventory[x].expirationDates.size(); x++)
		{
			if (inventory[x].expirationDates[y] < date)
			{
				inventory[x].quantity -= inventory[x].expirationDates[y].quantity;
				output << "Removed " << inventory[x].expirationDates[y].quantity << " expired items of ID " << inventory[x].idNum << "\n";
				inventory[x].expirationDates.erase(inventory[x].expirationDates.begin() + y);
			}
			else
			{
				break;
			}
		}
	}
	return output.str();
}








