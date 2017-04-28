void addStoreAndItems2company(vector<addDeleteStoreClass> addDeleteStore, Company&company)
{
	int storeID;
	string streetAddress;
	string city;
	string state;
	int zipCode;
	int priority;

	int itemCode;
	int defaultQuantity;
	int reorderLevel;
	int reorderQuantity;

	for (int i = 0; i < addDeleteStore.size(); i++)
	{
		if (addDeleteStore[i].getActionCode() == 'A')
		{
			storeID = addDeleteStore[i].getStoreID();
			streetAddress = addDeleteStore[i].getStreetAddress();
			city = addDeleteStore[i].getCity();
			state = addDeleteStore[i].getState();
			zipCode = addDeleteStore[i].getZipCode();
			priority = addDeleteStore[i].getStorePriority();

			Store store(storeID, streetAddress, city, state, zipCode, priority);

			company.addStore(store);

			for (int j = 0; j < addDeleteStore[i].getItems().size(); j++)
			{
				itemCode = addDeleteStore[i].getItem(j).getItemCode();
				defaultQuantity = addDeleteStore[i].getItem(j).getDefaultQuantity();
				reorderLevel = addDeleteStore[i].getItem(j).getReorderLevel();
				reorderQuantity = addDeleteStore[i].getItem(j).getReorderQuantity();

				Item item(itemCode, defaultQuantity, reorderLevel, reorderQuantity);

				company.addItemToStock(item);
			}
		}
	}

	//addDeleteStore.clear();
}

void items2warehouse(vector<itemReceivedClass>&itemReceived, Company&company)
{
	int vendorCode;
	int itemCode;
	int quantity;
	int expirationDay;
	int expirationMonth;
	int expirationYear;

	vector<ExpirationDate> ExpDate;

	for (int i = 0; i < itemReceived.size(); i++)
	{
		cout << "HELLO" << itemReceived[i].getItemCode() << endl;

		vendorCode = itemReceived[i].getVendorCode();
		itemCode = itemReceived[i].getItemCode();
		quantity = itemReceived[i].getQuantityReceived();
		expirationDay = itemReceived[i].getExpirationDay();
		expirationMonth = itemReceived[i].getExpirationMonth();
		expirationYear = itemReceived[i].getExpirationYear();

		cout << "THE YEAR ON ITS OWN: " << expirationYear << endl;

		ExpirationDate expdate(expirationDay, expirationMonth, expirationYear, quantity);

		ExpDate.push_back(expdate);

		Item item(vendorCode, itemCode, quantity, ExpDate);
		
		company.addInventoryToWarehouse(item);

		ExpDate.clear();
	}
}

void writeStoreUpdateCREATESTORE(vector<addDeleteStoreClass> addDeleteStore, int seq)
{
	int line = 0;

	fstream fout("storeupdateCREATESTORE.txt");

	fout << "HD ";

	if (seq > 999)
	{
		fout << seq;
	}
	else
	{
		if (seq > 99)
		{
			fout << "0" << seq;
		}
		else
		{
			if (seq > 9)
			{
				fout << "00" << seq;
			}
			else
			{
				fout << "000" << seq;
			}
		}
	}
	
	fout << "      2017-03-27" << endl;

	for (int i = 0; i < addDeleteStore.size(); i++)
	{
		for (int j = 0; j < addDeleteStore[i].getItems().size(); j++)
		{
			fout << "A";

			//if 
		}
	}
}