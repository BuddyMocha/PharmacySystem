class storeUpdateClass
{
private:
	char sourceCode;
	int storeID;
	int storePriority;
	int itemCode;
	int requestedQuantity;

public:
	storeUpdateClass()
	{
		sourceCode = '\0';
		storeID = 0;
		storePriority = 0;
		itemCode = 0;
		requestedQuantity = 0;
	}

	void setSourceCode(char input)
	{
		sourceCode = input;
	}

	void setStoreID(int input)
	{
		storeID = input;
	}

	void setStorePriority(int input)
	{
		storePriority = input;
	}

	void setItemCode(int input)
	{
		itemCode = input;
	}

	void setRequestedQuantity(int input)
	{
		requestedQuantity = input;
	}

	char getSourceCode()
	{
		return sourceCode;
	}

	int getStoreID()
	{
		return storeID;
	}

	int getStorePriority()
	{
		return storePriority;
	}

	int getItemCode()
	{
		return itemCode;
	}

	int getRequestedQuantity()
	{
		return requestedQuantity;
	}
};

vector<storeUpdateClass> StoreUpdateInput(vector<storeUpdateClass> storeUpdates, vector<char> file, string name, int loc, int line);

vector<storeUpdateClass> StoreUpdate(vector<storeUpdateClass> storeUpdate, int&Seq, string name)
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

					storeUpdate = StoreUpdateInput(storeUpdate, file, name, i, line);
				}

				if (i == file.size() - 1)
				{
					checkTrailer(file, name, line, loc);
				}
			}
		}
	}

	return storeUpdate;
}

vector<storeUpdateClass> StoreUpdateInput(vector<storeUpdateClass> storeUpdates, vector<char> file, string name, int loc, int line)
{
	char storeID[5];
	char storePriority[2];
	char itemCode[9];
	char requestedQuantity[10];

	storeUpdateClass storeUpdate;

	if (file[loc + 1] == 'A' || file[loc + 1] == 'O' || file[loc + 1] == 'B')
	{
		storeUpdate.setSourceCode(file[loc + 1]);

		if (file[loc + 28] == '\n')
		{
			for (int i = 1; i < 6; i++)
			{
				if (!isdigit(file[loc + 1 + i]))
				{
					cout << name << ": error - non-digit found on line " << line << endl;

					return storeUpdates;
				}
				storeID[i - 1] = file[loc + 1 + i];
			}
			storeUpdate.setStoreID(atoi(storeID));


			for (int i = 6; i < 8; i++)
			{
				if (!isdigit(file[loc + 1 + i]))
				{
					cout << name << ": error - non-digit found on line " << line << endl;

					return storeUpdates;
				}
				storePriority[i - 6] = file[loc + 1 + i];
			}
			storeUpdate.setStorePriority(atoi(storePriority));


			for (int i = 8; i < 17; i++)
			{
				if (!isdigit(file[loc + 1 + i]))
				{
					cout << name << ": error - non-digit found on line " << line << endl;

					return storeUpdates;
				}
				itemCode[i - 8] = file[loc + 1 + i];
			}
			storeUpdate.setItemCode(atoi(itemCode));


			for (int i = 17; i < 27; i++)
			{
				if (!isdigit(file[loc + 1 + i]))
				{
					cout << name << ": error - non-digit found on line " << line << endl;

					return storeUpdates;
				}
				requestedQuantity[i - 17] = file[loc + 1 + i];
			}
			storeUpdate.setRequestedQuantity(atoi(requestedQuantity));


			storeUpdates.push_back(storeUpdate);
		}
		else
		{
			cout << name << ": error found on line " << line << endl;

			return storeUpdates;
		}
	}
	else
	{
		if (file[loc + 1] == 'T' && file[loc + 2] == ' ')
		{
			if (loc + 8 != file.size())
			{
				cout << name << ": error found in trailer format" << endl;

				return storeUpdates;
			}
		}
		else
		{
			cout << name << ": error found on line " << line << endl;

			return storeUpdates;
		}
	}

	return storeUpdates;
}