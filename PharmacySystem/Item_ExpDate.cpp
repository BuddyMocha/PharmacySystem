#include "Item_ExpDate.h"

ExpirationDate::ExpirationDate(int day, int month, int year, int quantity)
	:day(day), month(month), year(year), quantity(quantity)
{}

std::string ExpirationDate::toString()
{
	std::stringstream output;
	output << quantity << " of this item will expire on " << month << "/" << day << "/" << year << "\n";
	return output.str();
}

Item::Item(int idNum, int quantity, float price, int requiredStock, int restockQuantity, std::vector<ExpirationDate> expDates)
	:idNum(idNum), quantity(quantity), price(price), requiredRestock(requiredStock), restockQuantity(restockQuantity), expirationDates(expDates)
{
}

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

std::string Item::checkoutString()
{
	std::stringstream output;
	output << "Item ID: " << idNum << "     Quantity: " << quantity << "\n";
	output << "    Price: " << price * quantity << "\n";
	return output.str();
}

std::string Item::toString()
{
	std::stringstream output;
	output << "Item ID: " << idNum << "     Quantity Remaining: " << quantity << "\n";
	return output.str();
}

void Item::addQuantity(Item stock)
{
	quantity += stock.quantity;
	for (int x = 0; x < expirationDates.size(); x++)
	{

	}
}

Item Item::removeQuantity(int amount)
{
	int initialAmount = amount;
	std::vector<ExpirationDate> expDates;
	quantity -= amount;
	if (amount <= quantity)
	{
		for (int x = 0; x < expirationDates.size() && amount > 0; x++)
		{
			if (expirationDates[x].quantity > amount)
			{
				expDates.push_back(ExpirationDate(expirationDates[x].day, expirationDates[x].month, expirationDates[x].year, amount));
				expirationDates[x].quantity -= amount;
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
