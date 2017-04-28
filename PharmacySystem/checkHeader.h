int*date2intArray(char dateChar[], string name);//converts date from file into an array for error checking
void updateRefs(int&seq, int date[], int dateInt[]);//updates sequence number and date passed in from main function
int checkDate(int&seq, string name, int date[], int dateInt[]);//checks if date is already processed

int checkHeader(vector<char> file, string name, int&seq, int date[])//checkHeader main function
{
	ofstream fout("ERRORS.TXT", ios::app);

	char seqChar[4];
	int seqInt;

	char dateChar[10];
	int *dateInt = new int;

	if (file[0] == 'H'&&file[1] == 'D'&&file[2] == ' '&&file[7] == ' '&& file[8] == ' '&&
		file[9] == ' '&&file[10] == ' '&&file[11] == ' '&&file[12] == ' ' &&file[23] == '\n')
	{
		for (int i = 0; i < 4; i++)
		{
			if (!isdigit(file[3 + i]))
			{
				fout << name << " rejected: HEADER ERROR - non-digit found in sequence number" << endl;

				return 1;
			}

			seqChar[i] = file[3 + i];
		}

		seqInt = atoi(seqChar);

		if (seqInt == seq)
		{
			/*
			for (int i = 0; i < 10; i++)
			{
			dateChar[i] = file[13 + i];
			}

			dateInt = date2intArray(dateChar, name);

			if (dateInt[0] != -1 || dateInt[1] != -1 || dateInt[2] != -1)
			{
			//return checkDate(seq, name, date, dateInt);
			}
			else
			{
			fout << name << " rejected: HEADER ERROR - date has incorrect format" << endl;

			return 1;
			}
			*/
			updateRefs(seq, date, dateInt);
		}
		else
		{
			fout << name << " rejected: HEADER ERROR - incorrect sequence number" << endl;

			return 1;
		}
	}
	else
	{
		fout << name << " rejected: HEADER ERROR - format incorrect or header doesn't exist" << endl;

		return 1;
	}

	return 0;
}

int*date2intArray(char dateChar[], string name)
{
	int *dateInt = new int[3];

	char year[4];
	char month[2];
	char day[2];

	if (dateChar[4] == '-' && dateChar[7] == '-')
	{
		for (int i = 0; i < 4; i++)
		{
			if (!isdigit(dateChar[i]))
			{
				//fout << name << " rejected: non-digit found in date" << endl;

				dateInt[0] = -1;
				dateInt[1] = -1;
				dateInt[2] = -1;

				return dateInt;
			}

			year[i] = dateChar[i];
		}

		for (int i = 0; i < 2; i++)
		{
			if (!isdigit(dateChar[5 + i]))
			{
				//fout << name << " rejected: non-digit found in date" << endl;

				dateInt[0] = -1;
				dateInt[1] = -1;
				dateInt[2] = -1;

				return dateInt;
			}

			month[i] = dateChar[5 + i];
		}

		for (int i = 0; i < 2; i++)
		{
			if (!isdigit(dateChar[8 + i]))
			{
				//fout << name << " rejected: non-digit found in date" << endl;

				dateInt[0] = -1;
				dateInt[1] = -1;
				dateInt[2] = -1;

				return dateInt;
			}

			day[i] = dateChar[8 + i];
		}

		dateInt[0] = atoi(year);
		dateInt[1] = atoi(month);
		dateInt[2] = atoi(day);
	}
	else
	{
		dateInt[0] = -1;
		dateInt[1] = -1;
		dateInt[2] = -1;
	}
	/*
	if (dateInt[1] > 12)
	{
	fout << name << " rejected: month is greater than 12" << endl;

	dateInt[0] = -1;
	dateInt[1] = -1;
	dateInt[2] = -1;
	}

	if (dateInt[2] > 31)
	{
	fout << name << " rejected: day is greater than 31" << endl;

	dateInt[0] = -1;
	dateInt[1] = -1;
	dateInt[2] = -1;
	}
	*/
	return dateInt;
}

void updateRefs(int&seq, int date[], int dateInt[])
{
	seq++;

	if (seq > 9999)
	{
		seq = 0;
	}

	for (int i = 0; i < 3; i++)
	{
		date[i] = dateInt[i];
	}
}

int checkDate(int&seq, string name, int date[], int dateInt[])
{
	ofstream fout("ERRORS.TXT", ios::app);

	if (dateInt[0]>date[0])
	{
		updateRefs(seq, date, dateInt);
	}
	else
	{
		if (dateInt[0] == date[0])
		{
			if (dateInt[1]>date[1])
			{
				updateRefs(seq, date, dateInt);
			}
			else
			{
				if (dateInt[1] == date[1])
				{
					if (dateInt[2]>date[2])
					{
						updateRefs(seq, date, dateInt);
					}
					else
					{
						if (dateInt[2] == date[2])
						{
							updateRefs(seq, date, dateInt);
						}
						else
						{
							fout << name << " rejected: date already processed" << endl;

							return 1;
						}
					}
				}
				else
				{
					fout << name << " rejected: date already processed" << endl;

					return 1;
				}
			}
		}
		else
		{
			fout << name << " rejected: date already processed" << endl;

			return 1;
		}
	}

	return 0;
}