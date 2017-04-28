//class that stores information vendororder.txt should input
class vendorOrderClass
{
private:
	int vendorCode;
	int itemCode;
	int quantityOrder;

public:
	vendorOrderClass()
	{
		vendorCode = 0;
		itemCode = 0;
		quantityOrder = 0;
	}

	void setVendorCode(int input)
	{
		vendorCode = input;
	}

	void setItemCode(int input)
	{
		itemCode = input;
	}

	void setQuantityOrder(int input)
	{
		quantityOrder = input;
	}

	int getVendorCode()
	{
		return vendorCode;
	}

	int getItemCode()
	{
		return itemCode;
	}

	int getQuantityOrder()
	{
		return quantityOrder;
	}
};

vector<vendorOrderClass> VendorOrderInput(vector<vendorOrderClass> vendorOrders, vector<char> file, string name, int loc, int line);

vector<vendorOrderClass> VendorOrder(vector<vendorOrderClass> vendorOrder, int&Seq)//main function of reports.txt
{
	int Date[3] = { 0, 0, 0 };

	vector<char> file;//vector of chars that will hold the text file
	string name = "vendororder.txt";//name of text file so fileCheck and checkHeader know the file name

	fstream fin(name);

	int line = 1;
	int loc = 0;

	if (fileCheck(fin, name) > 0)//if file exists and is not empty, 'else' loop is triggered
	{
		;
	}
	else
	{
		fin.close();

		file = FileConvert(name);

		if (checkHeader(file, name, Seq, Date) > 0)//if header of file matches conditions, 'else' loop is triggered
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

					vendorOrder = VendorOrderInput(vendorOrder, file, name, i, line);
				}

				if (i == file.size() - 1)
				{
					checkTrailer(file, name, line, loc);
				}
			}
		}
	}

	return vendorOrder;
}

vector<vendorOrderClass> VendorOrderInput(vector<vendorOrderClass> vendorOrders, vector<char> file, string name, int loc, int line)
{
	ofstream fout("ERRORS.TXT", ios::app);

	char vendorCode[4];
	char itemCode[9];
	char quantityOrder[10];

	vendorOrderClass vendorOrder;

	if (file[loc + 1] != 'T')
	{
		if (file[loc + 24] == '\n')
		{
			for (int i = 0; i < 4; i++)
			{
				if (!isdigit(file[loc + 1 + i]))
				{
					fout << name << ": error - non-digit found on line " << line << endl;

					return vendorOrders;
				}
				vendorCode[i] = file[loc + 1 + i];
			}
			vendorOrder.setVendorCode(atoi(vendorCode));


			for (int i = 4; i < 13; i++)
			{
				if (!isdigit(file[loc + 1 + i]))
				{
					fout << name << ": error - non-digit found on line " << line << endl;

					return vendorOrders;
				}
				itemCode[i - 4] = file[loc + 1 + i];
			}
			vendorOrder.setItemCode(atoi(itemCode));


			for (int i = 13; i < 23; i++)
			{
				if (!isdigit(file[loc + 1 + i]))
				{
					fout << name << ": error - non-digit found on line " << line << endl;

					return vendorOrders;
				}
				quantityOrder[i - 13] = file[loc + 1 + i];
			}
			vendorOrder.setQuantityOrder(atoi(quantityOrder));

			vendorOrders.push_back(vendorOrder);
		}
		else
		{
			fout << name << ": error found on line " << line << endl;

			return vendorOrders;
		}
	}
	else
	{
		if (file[loc + 1] == 'T' && file[loc + 2] == ' ')
		{
			if (loc + 8 != file.size())
			{
				fout << name << ": error found in trailer format" << endl;

				return vendorOrders;
			}
		}
		else
		{
			fout << name << ": error found on line " << line << endl;

			return vendorOrders;
		}
	}

	return vendorOrders;
}