//class that stores information reports.txt should input
class reportsClass
{
private:
	int itemCode;

public:
	reportsClass()
	{
		itemCode = 0;
	}

	void setItemCode(int input)
	{
		itemCode = input;
	}

	int getItemCode()
	{
		return itemCode;
	}
};

vector<reportsClass> getReportsInput(vector<reportsClass> reports, vector<char> file, string name, int loc, int line);//function that gets input from file and places it in Reports vector

vector<reportsClass> Reports(vector<reportsClass> reports, int&Seq)//main function of reports.txt
{
	int Date[3] = { 0, 0, 0 };

	vector<char> file;//vector of chars that will hold the text file
	string name = "reports.txt";//name of text file so fileCheck and checkHeader know the file name

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

					reports = getReportsInput(reports, file, name, i, line);
				}

				if (i == file.size() - 1)
				{
					checkTrailer(file, name, line, loc);
				}
			}
		}
	}

	return reports;
}

vector<reportsClass> getReportsInput(vector<reportsClass> reports, vector<char> file, string name, int loc, int line)
{
	ofstream fout("ERRORS.TXT", ios::app);

	char inChar[9];
	reportsClass report;

	if (file[loc + 1] == 'I')
	{
		if (file[loc + 11] == '\n')
		{
			for (int i = 0; i < 9; i++)
			{
				if (!isdigit(file[loc + 2 + i]))
				{
					fout << name << ": error - non-digit found on line " << line << endl;

					return reports;
				}

				inChar[i] = file[loc + 2 + i];
			}
			report.setItemCode(atoi(inChar));

			reports.push_back(report);
		}
		else
		{
			fout << name << ": error found on line " << line << endl;

			return reports;
		}
	}
	else
	{
		if (file[loc + 1] == 'T' && file[loc + 2] == ' ')
		{
			if (loc + 8 != file.size())
			{
				fout << name << ": error found in trailer format" << endl;

				return reports;
			}
		}
		else
		{
			fout << name << ": error found on line " << line << endl;

			return reports;
		}
	}

	return reports;
}