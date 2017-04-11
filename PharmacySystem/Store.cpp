#include "Store_Customer_Employee_Purchase.h"

Store::Store(std::string name, int idNum, int priority)
	: name(name), idNum(idNum), priority(priority)) 
{ 
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
	inventory.push_back(item);
}

Item removeItemFromInv()





