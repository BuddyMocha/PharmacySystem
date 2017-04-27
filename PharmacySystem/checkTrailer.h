int checkTrailer(vector<char> file, string name, int line, int loc)
{
	char trailChar[4];

	if (file[loc + 1] == 'T' && file[loc + 2] == ' ' && loc + 8 == file.size())
	{
		for (int i = 0; i < 4; i++)
		{
			if (!isdigit(file[loc + 3 + i]))
			{
				cout << name << ": TRAILER ERROR - non-digit found in trailer number" << endl;

				return 0;
			}

			trailChar[i] = file[loc + 3 + i];
		}

		if (atoi(trailChar) != line - 2)
		{
			cout << name << ": TRAILER ERROR - number of data records does not match actual file" << endl;

			return 0;
		}
	}
	else
	{
		cout << name << ": TRAILER ERROR - format incorrect or trailer doesn't exist" << endl;

		return 0;
	}

	return 0;
}