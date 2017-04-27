class addItemsClass
{
private:
	int itemCode;
	int defaultQuantity;
	int reorderLevel;
	int reorderQuantity;

public:
	addItemsClass()
	{
		itemCode = 0;
		defaultQuantity = 0;
		reorderLevel = 0;
		reorderQuantity = 0;
	}

	void setItemCode(int input)
	{
		itemCode = input;
	}

	void setDefaultQuantity(int input)
	{
		defaultQuantity = input;
	}

	void setReorderLevel(int input)
	{
		reorderLevel = input;
	}

	void setReorderQuantity(int input)
	{
		reorderQuantity = input;
	}

	int getItemCode()
	{
		return itemCode;
	}

	int getDefaultQuantity()
	{
		return defaultQuantity;
	}

	int getReorderLevel()
	{
		return reorderLevel;
	}

	int getReorderQuantity()
	{
		return reorderQuantity;
	}
};

class addDeleteStoreClass
{
private:
	char actionCode;
	int storeID;
	string streetAddress;
	string city;
	string state;
	int zipCode;
	int storePriority;
	vector<addItemsClass> items;

public:
	addDeleteStoreClass()
	{
		actionCode = '\0';
		storeID = 0;
		streetAddress = "";
		city = "";
		state = "";
		zipCode = 0;
		storePriority = 0;
	}

	void setActionCode(char input)
	{
		actionCode = input;
	}

	void setStoreID(int input)
	{
		storeID = input;
	}

	void setStreetAddress(string input)
	{
		streetAddress = input;
	}

	void setCity(string input)
	{
		city = input;
	}

	void setState(string input)
	{
		state = input;
	}

	void setZipCode(int input)
	{
		zipCode = input;
	}

	void setStorePriority(int input)
	{
		storePriority = input;
	}

	void pushItems(addItemsClass input)
	{
		items.push_back(input);
	}

	char getActionCode()
	{
		return actionCode;
	}

	int getStoreID()
	{
		return storeID;
	}

	string getStreetAddress()
	{
		return streetAddress;
	}

	string getCity()
	{
		return city;
	}

	string getState()
	{
		return state;
	}

	int getZipCode()
	{
		return zipCode;
	}

	int getStorePriority()
	{
		return storePriority;
	}

	vector<addItemsClass> getItems()
	{
		return items;
	}

	addItemsClass getItem(int i)
	{
		return items[i];
	}
};

vector<char> eraseSpace(vector<char> Vector);
vector<addDeleteStoreClass> AddDeleteStoreInput(vector<addDeleteStoreClass> addDeleteStores, vector<char> file, string name, int loc, int&line, int&lineItem);
vector<addDeleteStoreClass> AddItems(vector<addDeleteStoreClass> addDeleteStores, vector<char> file, string name, int loc, int line);
int checkControl(vector<char> file, string name, int lineItem, int loc);

vector<addDeleteStoreClass> AddDeleteStore(vector<addDeleteStoreClass> addDeleteStore, int&Seq)
{
	int Date[3] = { 0, 0, 0 };

	vector<char> file;
	string name = "adddeletestore.txt";

	fstream fin(name);

	int line = 1;
	int lineItem = 0;
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

					addDeleteStore = AddDeleteStoreInput(addDeleteStore, file, name, i, line, lineItem);
				}

				if (i == file.size() - 1)
				{
					checkTrailer(file, name, line, loc);
				}
			}
		}
	}

	return addDeleteStore;
}

vector<char> eraseSpace(vector<char> Vector)
{
	for (int i = Vector.size() - 1; i > -1; i--)
	{
		if (Vector[i] == ' ')
		{
			Vector.pop_back();
		}
		else
		{
			return Vector;
		}
	}
	return Vector;
}

vector<addDeleteStoreClass> AddDeleteStoreInput(vector<addDeleteStoreClass> addDeleteStores, vector<char> file, string name, int loc, int&line, int&lineItem)
{
	char actionCode;
	char storeID[5];
	vector<char> streetAddress;
	vector<char> city;
	char state[3];
	char zipCode[9];
	char storePriority[2];

	addDeleteStoreClass addDeleteStore;

	if (file[loc + 1] == 'A' || file[loc + 1] == 'D')
	{
		lineItem = 0;

		addDeleteStore.setActionCode(file[loc + 1]);

		for (int i = 1; i < 6; i++)
		{
			if (!isdigit(file[loc + 1 + i]))
			{
				cout << name << ": error - non-digit found on line " << line << endl;

				return addDeleteStores;
			}
			storeID[i - 1] = file[loc + 1 + i];
		}
		addDeleteStore.setStoreID(atoi(storeID));

		for (int i = 6; i < 26; i++)
		{
			if (!isalnum(file[loc + 1 + i]))
			{
				if (file[loc + 1 + i] != ' ')
				{
					cout << name << ": error - non-alphabetic letter or non-digit found on line " << line << endl;

					return addDeleteStores;
				}
			}

			streetAddress.push_back(file[loc + 1 + i]);
		}
		streetAddress = eraseSpace(streetAddress);
		addDeleteStore.setStreetAddress(string(streetAddress.data(), streetAddress.size()));

		for (int i = 26; i < 46; i++)
		{
			if (!isalpha(file[loc + 1 + i]))
			{
				if (file[loc + 1 + i] != ' ')
				{
					cout << name << ": error - non-alphabetic letter found on line " << line << endl;

					return addDeleteStores;
				}
			}
			city.push_back(file[loc + 1 + i]);
		}
		city = eraseSpace(city);
		addDeleteStore.setCity(string(city.data(), city.size()));

		for (int i = 46; i < 48; i++)
		{
			if (!isalpha(file[loc + 1 + i]))
			{
				if (file[loc + 1 + i] != ' ')
				{
					cout << name << ": error - non-alphabetic letter found on line " << line << endl;

					return addDeleteStores;
				}
			}
			state[i - 46] = file[loc + 1 + i];
		}
		state[2] = '\0';
		addDeleteStore.setState(state);

		for (int i = 48; i < 57; i++)
		{
			if (!isdigit(file[loc + 1 + i]))
			{
				cout << name << ": error - non-digit found on line " << line << endl;

				return addDeleteStores;
			}
			zipCode[i - 48] = file[loc + 1 + i];
		}
		addDeleteStore.setZipCode(atoi(zipCode));

		for (int i = 57; i < 59; i++)
		{
			if (!isdigit(file[loc + 1 + i]))
			{
				cout << name << ": error - non-digit found on line " << line << endl;

				return addDeleteStores;
			}
			storePriority[i - 57] = file[loc + 1 + i];
		}
		addDeleteStore.setStorePriority(atoi(storePriority));

		addDeleteStores.push_back(addDeleteStore);

		if (file[loc + 1] == 'A')
		{
			if (file[loc + 61] != 'I')
			{
				cout << name << ": ERROR - I record not found after an A record" << endl;
			}
		}
	}
	else
	{
		if (file[loc + 1] == 'T' && file[loc + 2] == ' ')
		{
			if (loc + 8 != file.size())
			{
				cout << name << ": error found in trailer format" << endl;

				return addDeleteStores;
			}

			if (loc + 8 == file.size())
			{
				return addDeleteStores;
			}
		}

		if (file[loc + 1] == 'I')
		{
			if (addDeleteStores.back().getActionCode() == 'A')
			{
				lineItem++;

				addDeleteStores = AddItems(addDeleteStores, file, name, loc, lineItem);

				return addDeleteStores;
			}
			else
			{
				cout << name << ": ERROR - I action code found not after A" << endl;

				return addDeleteStores;
			}
		}

		if (file[loc + 1] == 'C')
		{
			if (addDeleteStores.back().getActionCode() == 'A')
			{
				checkControl(file, name, lineItem, loc);

				line--;

				return addDeleteStores;
			}
			else
			{
				cout << name << ": ERROR - C action code found not after I" << endl;

				line--;

				return addDeleteStores;
			}
		}

		cout << name << ": error found on line " << line << endl;

		return addDeleteStores;
	}

	return addDeleteStores;
}

vector<addDeleteStoreClass> AddItems(vector<addDeleteStoreClass> addDeleteStores, vector<char> file, string name, int loc, int line)
{
	char itemCode[9];
	char defaultQuantity[10];
	char reorderLevel[10];
	char reorderQuantity[10];

	addItemsClass items;

	for (int i = 1; i < 10; i++)
	{
		if (!isdigit(file[loc + 1 + i]))
		{
			cout << name << ": error - non-digit found on line " << line << endl;

			return addDeleteStores;
		}
		itemCode[i - 1] = file[loc + 1 + i];
	}
	items.setItemCode(atoi(itemCode));

	for (int i = 10; i < 20; i++)
	{
		if (!isdigit(file[loc + 1 + i]))
		{
			cout << name << ": error - non-digit found on line " << line << endl;

			return addDeleteStores;
		}
		defaultQuantity[i - 10] = file[loc + 1 + i];
	}
	items.setDefaultQuantity(atoi(defaultQuantity));

	for (int i = 20; i < 30; i++)
	{
		if (!isdigit(file[loc + 1 + i]))
		{
			cout << name << ": error - non-digit found on line " << line << endl;

			return addDeleteStores;
		}
		reorderLevel[i - 20] = file[loc + 1 + i];
	}
	items.setReorderLevel(atoi(reorderLevel));

	for (int i = 30; i < 40; i++)
	{
		if (!isdigit(file[loc + 1 + i]))
		{
			cout << name << ": error - non-digit found on line " << line << endl;

			return addDeleteStores;
		}
		reorderQuantity[i - 30] = file[loc + 1 + i];
	}
	items.setReorderQuantity(atoi(reorderQuantity));

	addDeleteStores.back().pushItems(items);

	return addDeleteStores;
}

int checkControl(vector<char> file, string name, int lineItem, int loc)
{
	char contChar[4];

	if (file[loc + 1] == 'C' && file[loc + 2] == ' ')
	{
		for (int i = 0; i < 4; i++)
		{
			if (!isdigit(file[loc + 3 + i]))
			{
				cout << name << ": CONTROL ERROR - non-digit found in control number" << endl;

				return 0;
			}

			contChar[i] = file[loc + 3 + i];
		}

		if (atoi(contChar) != lineItem)
		{
			cout << name << ": CONTROL ERROR - number of item records does not match control number" << endl;

			return 0;
		}
	}
	else
	{
		cout << name << ": CONTROL ERROR - format incorrect or control doesn't exist" << endl;

		return 0;
	}

	return 0;
}