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

		}
	}
	inventory.push_back(item);
}

//Unfinished
Item Store::removeItemFromInv(int idNum, int quantity)
{
	for (int x = 0; x < inventory.size(); x++)
	{
		if (inventory[x].idNum = idNum)
		{
			inventory[x];
		}
	}
	return inventory[0];
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








