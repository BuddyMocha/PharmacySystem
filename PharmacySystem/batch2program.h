#pragma once
#include "Company_Warehouse.h"

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
		vendorCode = itemReceived[i].getVendorCode();
		itemCode = itemReceived[i].getItemCode();
		quantity = itemReceived[i].getQuantityReceived();
		expirationDay = itemReceived[i].getExpirationDay();
		expirationMonth = itemReceived[i].getExpirationMonth();
		expirationYear = itemReceived[i].getExpirationYear();

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
}

void warehouse2store(vector<storeUpdateClass> storeUpdate, Company&company)
{
	Store *store;

	for (int i = 0; i < storeUpdate.size(); i++)
	{
		store = company.getStore(storeUpdate[i].getStoreID());

		company.sendItems(storeUpdate[i].getItemCode(), storeUpdate[i].getRequestedQuantity(), store);
	}
}

void deleteStore(vector<addDeleteStoreClass> addDeleteStore, Company&company, int seq)
{
	int line = 0;

	ofstream fout("itemreceivedDELSTORE.txt");

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

	vector<Item> items;
	vector<ExpirationDate> expDates;

	for (int i = 0; i < addDeleteStore.size(); i++)
	{
		if (addDeleteStore[i].getActionCode() == 'D')
		{
			for (int j = 0; j < company.getStoreChain().size(); j++)
			{
				if (company.getStore(addDeleteStore[i].getStoreID()) != nullptr)
				{
					items = company.getStore(addDeleteStore[i].getStoreID())->getItemList();

					for (int h = 0; h < items.size(); h++)
					{
						items[h].vendorCode;
						items[h].idNum;
						expDates = items[h].expirationDates;
						for (int g = 0; g < expDates.size(); g++)
						{
							expDates[g].month;
							expDates[g].day;
							expDates[g].year;
							expDates[g].quantity;

							line++;

							if (items[h].vendorCode > 999)
							{
								fout << items[h].vendorCode;
							}
							else
							{
								if (items[h].vendorCode > 99)
								{
									fout << "0" << items[h].vendorCode;
								}
								else
								{
									if (items[h].vendorCode > 9)
									{
										fout << "00" << items[h].vendorCode;
									}
									else
									{
										fout << "000" << items[h].vendorCode;
									}
								}
							}

							if (items[h].idNum > 99999999)
							{
								fout << items[h].idNum;
							}
							else
							{
								if (items[h].idNum > 9999999)
								{
									fout << "0" << items[h].idNum;
								}
								else
								{
									if (items[h].idNum > 999999)
									{
										fout << "00" << items[h].idNum;
									}
									else
									{
										if (items[h].idNum > 99999)
										{
											fout << "000" << items[h].idNum;
										}
										else
										{
											if (items[h].idNum > 9999)
											{
												fout << "0000" << items[h].idNum;
											}
											else
											{
												if (items[h].idNum > 999)
												{
													fout << "00000" << items[h].idNum;
												}
												else
												{
													if (items[h].idNum > 99)
													{
														fout << "000000" << items[h].idNum;
													}
													else
													{
														if (items[h].idNum > 9)
														{
															fout << "0000000" << items[h].idNum;
														}
														else
														{
															fout << "00000000" << items[h].idNum;
														}
													}
												}
											}
										}
									}
								}
							}

							if (expDates[g].quantity > 99999999)
							{
								fout << expDates[g].quantity;
							}
							else
							{
								if (expDates[g].quantity  > 99999999)
								{
									fout << "0" << expDates[g].quantity;
								}
								else
								{
									if (expDates[g].quantity  > 9999999)
									{
										fout << "00" << expDates[g].quantity;
									}
									else
									{
										if (expDates[g].quantity  > 999999)
										{
											fout << "000" << expDates[g].quantity;
										}
										else
										{
											if (expDates[g].quantity  > 99999)
											{
												fout << "0000" << expDates[g].quantity;
											}
											else
											{
												if (expDates[g].quantity  > 9999)
												{
													fout << "00000" << expDates[g].quantity;
												}
												else
												{
													if (expDates[g].quantity  > 999)
													{
														fout << "000000" << expDates[g].quantity;
													}
													else
													{
														if (expDates[g].quantity > 99)
														{
															fout << "0000000" << expDates[g].quantity;
														}
														else
														{
															if (expDates[g].quantity > 9)
															{
																fout << "00000000" << expDates[g].quantity;
															}
															else
															{
																fout << "000000000" << expDates[g].quantity;
															}
														}
													}
												}
											}
										}
									}
								}
							}

							fout << expDates[g].year << "-";
							
							if (expDates[g].month > 9)
							{
								fout << expDates[g].month << "-";
							}
							else
							{
								fout << "0" << expDates[g].month << "-";
							}

							if (expDates[g].day > 9)
							{
								fout << expDates[g].day << endl;
							}
							else
							{
								fout << "0" << expDates[g].day << endl;
							}
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

					company.deleteStore(company.getJustAStore(j).getID());
				}
			}
		}
	}
}
