class itemReceivedClass
{
private:
	int vendorCode;
	int itemCode;
	int quantityReceived;
	int expirationDay;
	int expirationMonth;
	int expirationYear;

public:
	itemReceivedClass()
	{
		vendorCode = 0;
		itemCode = 0;
		quantityReceived = 0;

		expirationDay = 0;
		expirationMonth = 0;
		expirationYear = 0;
	}

	void setVendorCode(int input)
	{
		vendorCode = input;
	}

	void setItemCode(int input)
	{
		itemCode = input;
	}

	void setQuantityReceived(int input)
	{
		quantityReceived = input;
	}

	void setExpirationDate(int day, int month, int year)
	{
		expirationDay = day;
		expirationMonth = month;
		expirationYear = year;
	}

	int getVendorCode()
	{
		return vendorCode;
	}

	int getItemCode()
	{
		return itemCode;
	}

	int getQuantityReceived()
	{
		return quantityReceived;
	}

	int getExpirationDay()
	{
		return expirationDay;
	}

	int getExpirationMonth()
	{
		return expirationMonth;
	}

	int getExpirationYear()
	{
		return expirationYear;
	}
};

vector<itemReceivedClass> ItemReceivedInput(vector<itemReceivedClass> itemsReceived, vector<char> file, string name, int loc, int line);

vector<itemReceivedClass> ItemReceived(vector<itemReceivedClass> itemReceived, int&Seq, string name)
{
	int Date[3] = { 0, 0, 0 };

	vector<char> file;

	fstream fin(name);

	int line = 1;
	int loc = 0;

	if (fileCheck(fin, name) > 0)
	{
		;
	}
	else
	{
		fin.close();

		file = FileConvert(name);

		if (checkHeader(file, name, Seq, Date) > 0)
		{
			;
		}
		else
		{
			for (int i = 0; i < file.size(); i++)
			{
				if (file[i] == '\n')
				{
					line++;
					loc = i;

					itemReceived = ItemReceivedInput(itemReceived, file, name, i, line);
				}

				if (i == file.size() - 1)
				{
					checkTrailer(file, name, line, loc);
				}
			}
		}
	}

	return itemReceived;
}

vector<itemReceivedClass> ItemReceivedInput(vector<itemReceivedClass> itemsReceived, vector<char> file, string name, int loc, int line)
{
	char vendorCode[4];
	char itemCode[9];
	char quantityReceived[10];
	char expirationDay[2];
	char expirationMonth[2];
	char expirationYear[4];

	itemReceivedClass itemReceived;


	if (file[loc + 1] != 'T' && file[loc + 28] == '-' && file[loc + 31] == '-')
	{
		if (file[loc + 34] == '\n')
		{
			for (int i = 0; i < 4; i++)
			{
				if (!isdigit(file[loc + 1 + i]))
				{
					cout << name << ": error - non-digit found on line " << line << endl;

					return itemsReceived;
				}
				vendorCode[i] = file[loc + 1 + i];
			}
			itemReceived.setVendorCode(atoi(vendorCode));


			for (int i = 4; i < 13; i++)
			{
				if (!isdigit(file[loc + 1 + i]))
				{
					cout << name << ": error - non-digit found on line " << line << endl;

					return itemsReceived;
				}
				itemCode[i - 4] = file[loc + 1 + i];
			}
			itemReceived.setItemCode(atoi(itemCode));


			for (int i = 13; i < 23; i++)
			{
				if (!isdigit(file[loc + 1 + i]))
				{
					cout << name << ": error - non-digit found on line " << line << endl;

					return itemsReceived;
				}
				quantityReceived[i - 13] = file[loc + 1 + i];
			}
			itemReceived.setQuantityReceived(atoi(quantityReceived));


			for (int i = 23; i < 27; i++)
			{
				if (!isdigit(file[loc + 1 + i]))
				{
					cout << name << ": error - non-digit found on line " << line << endl;

					return itemsReceived;
				}
				expirationYear[i - 23] = file[loc + 1 + i];
			}


			for (int i = 28; i < 30; i++)
			{
				if (!isdigit(file[loc + 1 + i]))
				{
					cout << name << ": error - non-digit found on line " << line << endl;

					return itemsReceived;
				}
				expirationMonth[i - 28] = file[loc + 1 + i];
			}


			for (int i = 31; i < 33; i++)
			{
				if (!isdigit(file[loc + 1 + i]))
				{
					cout << name << ": error - non-digit found on line " << line << endl;

					return itemsReceived;
				}
				expirationDay[i - 31] = file[loc + 1 + i];
			}

			itemReceived.setExpirationDate(atoi(expirationYear), atoi(expirationMonth), atoi(expirationDay));

			itemsReceived.push_back(itemReceived);
		}
		else
		{
			cout << name << ": error found on line " << line << endl;

			return itemsReceived;
		}
	}
	else
	{
		if (file[loc + 1] == 'T' && file[loc + 2] == ' ')
		{
			if (loc + 8 != file.size())
			{
				cout << name << ": error found in trailer format" << endl;

				return itemsReceived;
			}
		}
		else
		{
			cout << name << ": error found on line " << line << endl;

			return itemsReceived;
		}
	}

	return itemsReceived;
}