int checkTrailer(vector<char> file, string name, int line, int loc)
{
	ofstream fout("ERRORS.TXT", ios::app);

	char trailChar[4];

	if (file[loc + 1] == 'T' && file[loc + 2] == ' ' && loc + 8 == file.size())
	{
		for (int i = 0; i < 4; i++)
		{
			if (!isdigit(file[loc + 3 + i]))
			{
				fout << name << ": TRAILER ERROR - non-digit found in trailer number" << endl;

				return 0;
			}

			trailChar[i] = file[loc + 3 + i];
		}

		if (atoi(trailChar) != line - 2)
		{
			fout << name << ": TRAILER ERROR - number of data records does not match actual file" << endl;

			return 0;
		}
	}
	else
	{
		fout << name << ": TRAILER ERROR - format incorrect or trailer doesn't exist" << endl;

		return 0;
	}

	return 0;
}