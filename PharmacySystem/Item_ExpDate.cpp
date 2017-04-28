#include "Item_ExpDate.h"
//Constructor for ExpDate
ExpirationDate::ExpirationDate(int day, int month, int year, int quantity)
	:day(day), month(month), year(year), quantity(quantity)
{
}

//Used in outputting item data
std::string ExpirationDate::toString()
{
	std::stringstream output;
	output << quantity << " of this item will expire on " << month << "/" << day << "/" << year << "\n";
	return output.str();
}

//Operator overloads to make date sorting easier
//Read: "If expDate 1 is earlier than expDate 2"
bool ExpirationDate::operator <(ExpirationDate expDate)
{
	if (year < expDate.year)
	{
		return true;
	}
	else if (year == expDate.year)
	{
		if (month < expDate.month)
		{
			return true;
		}
		else if (month == expDate.month && day < expDate.day)
		{
			return true;
		}
	}
	return false;
}
//If the dates are equal...
bool ExpirationDate::operator ==(const ExpirationDate expDate)
{
	if (year == expDate.year)
	{
		if (month == expDate.month)
		{
			if (day == expDate.day)
			{
				return true;
			}
		}
	}
	return false;
}

//Item constructor
Item::Item(int idNum, int defaultItemQuantity, int requiredStock, int restockQuantity)
	:idNum(idNum), defaultStoreQuantity(defaultStoreQuantity), requiredRestock(requiredStock), restockQuantity(restockQuantity)
{
	price = rand() % 20 + 1;
	name = "";
	dosage = -1;
	quantity = -1;
}

Item::Item(int idNum, int quantity ,float price, int requiredRestock, int restockQuantity, std::vector<ExpirationDate> expDate)
	:idNum(idNum), quantity(quantity), price(price), requiredRestock(requiredRestock), restockQuantity(restockQuantity), expirationDates(expDate)
{
	name = "";
	dosage = -1;
}

Item::Item(int vendorCode, int idNum, int quantity, std::vector<ExpirationDate> expDate)
	:vendorCode(vendorCode), idNum(idNum), quantity(quantity), expirationDates(expDate)
{
	name = "";
	dosage = -1;
	requiredRestock = -1;
	restockQuantity = -1;
	price = rand() % 20 + 1;
}

//Outputs all item data, including expDates
std::string Item::allDataToString()
{
	std::stringstream output;
	output << "Item ID: " << idNum << "     Quantity Remaining: " << quantity << "\n";
	output << "    Restock at " << requiredRestock << " units. Refill to " << restockQuantity << " units.\n";
	for (int x = 0; x < expirationDates.size(); x++)
	{
		output << expirationDates[x].toString();
	}

	return output.str();
}
//A sepecific string used during checkout, showing price charged
std::string Item::checkoutString()
{
	std::stringstream output;
	output << "Item ID: " << idNum << "     Quantity: " << quantity << "\n";
	output << "    Price: " << price * quantity << "\n";
	return output.str();
}
//Simple string output, only showing ID and quantity
std::string Item::toString()
{
	std::stringstream output;
	output << "Item ID: " << idNum << "     Quantity Remaining: " << quantity << "\n";
	return output.str();
}

//Adds the quantity of 2 items together, and merges their experation date lists
void Item::addQuantity(Item stock)
{
	if (idNum == stock.idNum)
	{
		quantity += stock.quantity;
		for (int x = 0; x < stock.expirationDates.size(); x++)
		{
			expirationDates.push_back(stock.expirationDates[x]);
		}
		std::sort(expirationDates.begin(), expirationDates.end());
		for (int x = 0; x < expirationDates.size() - 1; x++)
		{
			if (expirationDates[x] == expirationDates[x + 1])
			{
				expirationDates[x].quantity += expirationDates[x + 1].quantity;
				expirationDates.erase(expirationDates.begin() + x + 1);
				x--;
			}
		}
	}
	else
	{
		std::cout << "ID numbers not the same, cannot merge items" << std::endl;
	}
}

//Removes a quantity of the item from stock, removing the most recent expiration dates, and returning an Item object with the removed data
Item Item::removeQuantity(int amount)
{
	int initialAmount = amount;
	std::vector<ExpirationDate> expDates;
	quantity -= amount;
	//Sorts the expDate list before removing items. If process is too slow, remove this line
	std::sort(expirationDates.begin(), expirationDates.end());
	if (amount <= quantity)
	{
		for (int x = 0; x < expirationDates.size() && amount > 0; x++)
		{
			if (expirationDates[x].quantity > amount)
			{
				expDates.push_back(ExpirationDate(expirationDates[x].day, expirationDates[x].month, expirationDates[x].year, amount));
				expirationDates[x].quantity -= amount;
				if (expirationDates[x].quantity == 0)
				{
					expirationDates.erase(expirationDates.begin() + x);
				}
				amount = 0;
			}
			else
			{
				expDates.push_back(ExpirationDate(expirationDates[x].day, expirationDates[x].month, expirationDates[x].year, expirationDates[x].quantity));

				amount -= expirationDates[x].quantity;
				expirationDates.erase(expirationDates.begin() + x);
				x--;
			}
		}
	}
	else
	{
		std::cout << "Error: Item quantity is " << quantity << ". Amount requested was " << amount << ". Please request an available amount." << std::endl;
	}
	return Item(idNum, initialAmount, price, requiredRestock, restockQuantity, expDates);
}
