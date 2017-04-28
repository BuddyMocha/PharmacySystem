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

void writeStoreUpdateCREATESTORE(vector<addDeleteStoreClass>&addDeleteStore, int seq)
{
	int line = 0;

	ofstream fout("storeupdateCREATESTORE.txt");

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
			line++;

			fout << "A";

			if (addDeleteStore[i].getStoreID() > 9999)
			{
				fout << addDeleteStore[i].getStoreID();
			}
			else
			{
				if (addDeleteStore[i].getStoreID() > 999)
				{
					fout << "0" << addDeleteStore[i].getStoreID();
				}
				else
				{
					if (addDeleteStore[i].getStoreID() > 99)
					{
						fout << "00" << addDeleteStore[i].getStoreID();
					}
					else
					{
						if (addDeleteStore[i].getStoreID() > 9)
						{
							fout << "000" << addDeleteStore[i].getStoreID();
						}
						else
						{
							fout << "0000" << addDeleteStore[i].getStoreID();
						}
					}
				}
			}

			if (addDeleteStore[i].getStorePriority() > 9)
			{
				fout << addDeleteStore[i].getStorePriority();
			}
			else
			{
				fout << "0" << addDeleteStore[i].getStorePriority() << endl;
			}

			if (addDeleteStore[i].getItem(j).getItemCode() > 99999999)
			{
				fout << addDeleteStore[i].getItem(j).getItemCode();
			}
			else
			{
				if (addDeleteStore[i].getItem(j).getItemCode() > 9999999)
				{
					fout << "0" << addDeleteStore[i].getItem(j).getItemCode();
				}
				else
				{
					if (addDeleteStore[i].getItem(j).getItemCode() > 999999)
					{
						fout << "00" << addDeleteStore[i].getItem(j).getItemCode();
					}
					else
					{
						if (addDeleteStore[i].getItem(j).getItemCode() > 99999)
						{
							fout << "000" << addDeleteStore[i].getItem(j).getItemCode();
						}
						else
						{
							if (addDeleteStore[i].getItem(j).getItemCode() > 9999)
							{
								fout << "0000" << addDeleteStore[i].getItem(j).getItemCode();
							}
							else
							{
								if (addDeleteStore[i].getItem(j).getItemCode() > 999)
								{
									fout << "00000" << addDeleteStore[i].getItem(j).getItemCode();
								}
								else
								{
									if (addDeleteStore[i].getItem(j).getItemCode() > 99)
									{
										fout << "000000" << addDeleteStore[i].getItem(j).getItemCode();
									}
									else
									{
										if (addDeleteStore[i].getItem(j).getItemCode() > 9)
										{
											fout << "0000000" << addDeleteStore[i].getItem(j).getItemCode();
										}
										else
										{
											fout << "00000000" << addDeleteStore[i].getItem(j).getItemCode();
										}
									}
								}
							}
						}
					}
				}
			}

			if (addDeleteStore[i].getItem(j).getDefaultQuantity() > 99999999)
			{
				fout << addDeleteStore[i].getItem(j).getDefaultQuantity();
			}
			else
			{
				if (addDeleteStore[i].getItem(j).getDefaultQuantity()  > 99999999)
				{
					fout << "0" << addDeleteStore[i].getItem(j).getDefaultQuantity();
				}
				else
				{
					if (addDeleteStore[i].getItem(j).getDefaultQuantity()  > 9999999)
					{
						fout << "00" << addDeleteStore[i].getItem(j).getDefaultQuantity();
					}
					else
					{
						if (addDeleteStore[i].getItem(j).getDefaultQuantity()  > 999999)
						{
							fout << "000" << addDeleteStore[i].getItem(j).getDefaultQuantity();
						}
						else
						{
							if (addDeleteStore[i].getItem(j).getDefaultQuantity()  > 99999)
							{
								fout << "0000" << addDeleteStore[i].getItem(j).getDefaultQuantity();
							}
							else
							{
								if (addDeleteStore[i].getItem(j).getDefaultQuantity()  > 9999)
								{
									fout << "00000" << addDeleteStore[i].getItem(j).getDefaultQuantity();
								}
								else
								{
									if (addDeleteStore[i].getItem(j).getDefaultQuantity()  > 999)
									{
										fout << "000000" << addDeleteStore[i].getItem(j).getDefaultQuantity();
									}
									else
									{
										if (addDeleteStore[i].getItem(j).getDefaultQuantity() > 99)
										{
											fout << "0000000" << addDeleteStore[i].getItem(j).getDefaultQuantity();
										}
										else
										{
											if (addDeleteStore[i].getItem(j).getDefaultQuantity() > 9)
											{
												fout << "00000000" << addDeleteStore[i].getItem(j).getDefaultQuantity();
											}
											else
											{
												fout << "000000000" << addDeleteStore[i].getItem(j).getDefaultQuantity();
											}
										}
									}
								}
							}
						}
					}
				}
			}
			fout << endl;
		}
	}

	fout << "T ";

	if (line > 999)
	{
		fout << line;
	}
	else
	{
		if (line > 99)
		{
			fout << "0" << line;
		}
		else
		{
			if (line > 9)
			{
				fout << "00" << line;
			}
			else
			{
				fout << "000" << line;
			}
		}
	}

	addDeleteStore.clear();
}

void warehouse2store(vector<storeUpdateClass> storeUpdate, Company&company)
{
	int storeID;
	int priorityLevel;
	int itemCode;
	int quantity;

	Store *store;

	for (int i = 0; i < storeUpdate.size(); i++)
	{
		store = company.getStore(storeUpdate[i].getStoreID());

	}
}