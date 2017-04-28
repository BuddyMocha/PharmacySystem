class itemsClass
{
private:
	string actionCode;
	int itemCode;
	string itemName;
	string itemDescription;
	string itemDosage;
	int warehouseReorderLevel;
	int vendorCode;
	int warehouseReorderQuantity;
	string expectedDeliveryTime;

public:
	itemsClass()
	{
		actionCode = '\0';
		itemCode = 0;
		itemName = "";
		itemDescription = "";
		itemDosage = "";
		warehouseReorderLevel = 0;
		vendorCode = 0;
		warehouseReorderQuantity = 0;
		expectedDeliveryTime = "";
	}

	void setActionCode(string input)
	{
		actionCode = input;
	}

	void setItemCode(int input)
	{
		itemCode = input;
	}

	void setItemName(string input)
	{
		itemName = input;
	}

	void setItemDescription(string input)
	{
		itemDescription = input;
	}

	void setItemDosage(string input)
	{
		itemDosage = input;
	}

	void setWarehouseReorderLevel(int input)
	{
		warehouseReorderLevel = input;
	}

	void setVendorCode(int input)
	{
		vendorCode = input;
	}

	void setWarehouseReorderQuantity(int input)
	{
		warehouseReorderQuantity = input;
	}

	void setExpectedDeliveryTime(string input)
	{
		expectedDeliveryTime = input;
	}

	string getActionCode()
	{
		return actionCode;
	}

	int getItemCode()
	{
		return itemCode;
	}

	string getItemName()
	{
		return itemName;
	}

	string getItemDescription()
	{
		return itemDescription;
	}

	string getItemDosage()
	{
		return itemDosage;
	}

	int getWarehouseReorderLevel()
	{
		return warehouseReorderLevel;
	}

	int getVendorCode()
	{
		return vendorCode;
	}

	int getWarehouseReorderQuantity()
	{
		return warehouseReorderQuantity;
	}

	string getExpectedDeliveryTime()
	{
		return expectedDeliveryTime;
	}
};

vector<itemsClass>  ItemsInput(vector<itemsClass> items, vector<char> file, string name, int loc, int&line, int&lineD, int&lineA, int&lineC);
int checkNumber(vector<char> file, string name, int line, int loc, string);

vector<itemsClass> Items(vector<itemsClass> items, int&Seq)
{
	int Date[3] = { 0, 0, 0 };

	vector<char> file;
	string name = "items.txt";

	fstream fin(name);

	int line = 1;
	int loc = 0;
	int lineD = 0;
	int lineA = 0;
	int lineC = 0;

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

					items = ItemsInput(items, file, name, i, line, lineD, lineA, lineC);
				}

				if (i == file.size() - 1)
				{
					checkTrailer(file, name, line, loc);
				}
			}
		}
	}

	return items;
}

vector<itemsClass>  ItemsInput(vector<itemsClass> items, vector<char> file, string name, int loc, int&line, int&lineD, int&lineA, int&lineC)
{
	ofstream fout("ERRORS.TXT", ios::app);

	char itemCode[9];
	vector<char> itemName;
	vector<char> itemDescription;
	vector<char> itemDosage;
	char warehouseReorderLevel[20];
	char vendorCode[4];
	char warehouseReorderQuantity[10];
	vector<char> expectedDeliveryTime;

	itemsClass item;

	if (file[loc + 1] == 'D')
	{
		if (items.size() == 0 || items.back().getActionCode() == "D")
		{
			if (file[loc + 11] == '\n')
			{
				lineD++;

				item.setActionCode(string(1, file[loc + 1]));

				for (int i = 1; i < 10; i++)
				{
					if (!isdigit(file[loc + 1 + i]))
					{
						fout << name << ": error - non-digit found on line " << line << endl;

						return items;
					}
					itemCode[i - 1] = file[loc + 1 + i];
				}
				item.setItemCode(atoi(itemCode));

				items.push_back(item);

				return items;
			}
		}
		else
		{
			fout << name << ": ERROR - delete found in wrong sequence " << endl;
		}
	}

	if (file[loc + 1] == 'N' && file[loc + 2] == 'D' && file[loc + 3] == ' ')
	{
		if (items.back().getActionCode() == "D")
		{
			checkNumber(file, name, lineD, loc, "ND");

			line--;

			item.setActionCode("ND");
			items.push_back(item);

			return items;
		}
		else
		{
			fout << name << ": ERROR - D action code not found before ND" << endl;

			line--;

			return items;
		}
	}

	if (file[loc + 1] == 'A' && items.size() != 0)
	{
		if (items.back().getActionCode() == "A" || items.back().getActionCode() == "ND")
		{
			lineA++;

			item.setActionCode(string(1, file[loc + 1]));

			for (int i = 1; i < 10; i++)
			{
				if (!isdigit(file[loc + 1 + i]))
				{
					fout << name << ": error - non-digit found on line " << line << endl;

					return items;
				}
				itemCode[i - 1] = file[loc + 1 + i];
			}
			item.setItemCode(atoi(itemCode));

			for (int i = 10; i < 30; i++)
			{
				itemName.push_back(file[loc + 1 + i]);
			}
			itemName = eraseSpace(itemName);
			item.setItemName(string(itemName.data(), itemName.size()));


			for (int i = 30; i < 130; i++)
			{
				itemDescription.push_back(file[loc + 1 + i]);
			}
			itemDescription = eraseSpace(itemDescription);
			item.setItemDescription(string(itemDescription.data(), itemDescription.size()));


			for (int i = 130; i < 150; i++)
			{
				itemDosage.push_back(file[loc + 1 + i]);
			}
			itemDosage = eraseSpace(itemDosage);
			item.setItemDosage(string(itemDosage.data(), itemDosage.size()));

			for (int i = 150; i < 160; i++)
			{
				if (!isdigit(file[loc + 1 + i]))
				{
					fout << name << ": error - non-digit found on line " << line << endl;

					return items;
				}
				warehouseReorderLevel[i - 150] = file[loc + 1 + i];
			}
			item.setWarehouseReorderLevel(atoi(warehouseReorderLevel));

			for (int i = 160; i < 164; i++)
			{
				if (!isdigit(file[loc + 1 + i]))
				{
					fout << name << ": error - non-digit found on line " << line << endl;

					return items;
				}
				vendorCode[i - 160] = file[loc + 1 + i];
			}
			item.setVendorCode(atoi(vendorCode));


			for (int i = 164; i < 174; i++)
			{
				if (!isdigit(file[loc + 1 + i]))
				{
					fout << name << ": error - non-digit found on line " << line << endl;

					return items;
				}
				warehouseReorderQuantity[i - 164] = file[loc + 1 + i];
			}
			item.setWarehouseReorderQuantity(atoi(warehouseReorderQuantity));


			for (int i = 174; i < 194; i++)
			{
				expectedDeliveryTime.push_back(file[loc + 1 + i]);
			}
			expectedDeliveryTime = eraseSpace(expectedDeliveryTime);
			item.setExpectedDeliveryTime(string(expectedDeliveryTime.data(), expectedDeliveryTime.size()));


			items.push_back(item);

			return items;
		}
		else
		{
			fout << name << ": ERROR - A action code found in wrong sequence " << endl;
		}
	}

	if (file[loc + 1] == 'N' && file[loc + 2] == 'A' && file[loc + 3] == ' ')
	{
		if (items.back().getActionCode() == "A")
		{
			checkNumber(file, name, lineA, loc, "NA");

			line--;

			item.setActionCode("NA");
			items.push_back(item);

			return items;
		}
		else
		{
			fout << name << ": ERROR - A action code not found before NA" << endl;

			line--;

			return items;
		}
	}

	if (file[loc + 1] == 'C' && items.size() != 0)
	{
		if (items.back().getActionCode() == "C" || items.back().getActionCode() == "NA")
		{
			lineC++;

			item.setActionCode(string(1, file[loc + 1]));

			for (int i = 1; i < 10; i++)
			{
				if (!isdigit(file[loc + 1 + i]))
				{
					fout << name << ": error - non-digit found on line " << line << endl;

					return items;
				}
				itemCode[i - 1] = file[loc + 1 + i];
			}
			item.setItemCode(atoi(itemCode));

			for (int i = 10; i < 30; i++)
			{
				itemName.push_back(file[loc + 1 + i]);
			}
			itemName = eraseSpace(itemName);
			item.setItemName(string(itemName.data(), itemName.size()));


			for (int i = 30; i < 130; i++)
			{
				itemDescription.push_back(file[loc + 1 + i]);
			}
			itemDescription = eraseSpace(itemDescription);
			item.setItemDescription(string(itemDescription.data(), itemDescription.size()));


			for (int i = 130; i < 150; i++)
			{
				itemDosage.push_back(file[loc + 1 + i]);
			}
			itemDosage = eraseSpace(itemDosage);
			item.setItemDosage(string(itemDosage.data(), itemDosage.size()));

			for (int i = 150; i < 160; i++)
			{
				if (!isdigit(file[loc + 1 + i]))
				{
					fout << name << ": error - non-digit found on line " << line << endl;

					return items;
				}
				warehouseReorderLevel[i - 150] = file[loc + 1 + i];
			}
			item.setWarehouseReorderLevel(atoi(warehouseReorderLevel));

			for (int i = 160; i < 164; i++)
			{
				if (!isdigit(file[loc + 1 + i]))
				{
					fout << name << ": error - non-digit found on line " << line << endl;

					return items;
				}
				vendorCode[i - 160] = file[loc + 1 + i];
			}
			item.setVendorCode(atoi(vendorCode));


			for (int i = 164; i < 174; i++)
			{
				if (!isdigit(file[loc + 1 + i]))
				{
					fout << name << ": error - non-digit found on line " << line << endl;

					return items;
				}
				warehouseReorderQuantity[i - 164] = file[loc + 1 + i];
			}
			item.setWarehouseReorderQuantity(atoi(warehouseReorderQuantity));


			for (int i = 174; i < 194; i++)
			{
				expectedDeliveryTime.push_back(file[loc + 1 + i]);
			}
			expectedDeliveryTime = eraseSpace(expectedDeliveryTime);
			item.setExpectedDeliveryTime(string(expectedDeliveryTime.data(), expectedDeliveryTime.size()));


			items.push_back(item);

			return items;
		}
		else
		{
			fout << name << ": ERROR - C code found in wrong sequence " << endl;
		}
	}

	if (file[loc + 1] == 'N' && file[loc + 2] == 'C' && file[loc + 3] == ' ')
	{
		if (items.back().getActionCode() == "C")
		{
			checkNumber(file, name, lineC, loc, "NC");

			line--;

			item.setActionCode("NC");
			items.push_back(item);

			return items;
		}
		else
		{
			fout << name << ": ERROR - C action code not found before ND" << endl;

			line--;

			return items;
		}
	}

	return items;
}

int checkNumber(vector<char> file, string name, int line, int loc, string rec)
{
	ofstream fout("ERRORS.TXT", ios::app);

	char numbChar[4];

	if (file[loc + 1] == rec.at(0) && file[loc + 2] == rec.at(1) && file[loc + 3] == ' ')
	{
		for (int i = 0; i < 4; i++)
		{
			if (!isdigit(file[loc + 4 + i]))
			{
				fout << name << ": #ROWS ERROR - non-digit found in #ROWS" << endl;

				return 0;
			}

			numbChar[i] = file[loc + 4 + i];
		}

		if (atoi(numbChar) != line)
		{
			fout << name << ": #ROWS ERROR - number of item records does not match #ROWS number" << endl;

			return 0;
		}
	}
	else
	{
		fout << name << ": #ROWS ERROR - format incorrect or #ROWS doesn't exist" << endl;

		return 0;
	}

	return 0;
}