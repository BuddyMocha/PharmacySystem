void addStore2program(vector<addDeleteStoreClass>&addDeleteStore, Company&company)
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

			for (int i = 0; i < addDeleteStore[i].getItems().size(); i++)
			{
				;
			}
		}
	}
}