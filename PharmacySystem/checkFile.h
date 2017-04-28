int fileExists(fstream&fin, string name);//check if file exists
int fileEmpty(fstream&fin, string name);//check if file is empty

int fileCheck(fstream&fin, string name)//main function of fileCheck
{
	return fileExists(fin, name) + fileEmpty(fin, name);
}

int fileExists(fstream&fin, string name)
{
	ofstream fout("ERRORS.TXT", ios::app);

	if (fin.fail())
	{
		fout << name + " does not exist" << endl;
		return 1;
	}

	return 0;
}

int fileEmpty(fstream&fin, string name)
{
	ofstream fout("ERRORS.TXT", ios::app);

	fin.ignore(1);

	if (fin.eof())
	{
		fout << name + " is empty" << endl;
		return 1;
	}

	return 0;
}

vector<char> FileConvert(string name)
{
	fstream in(name);

	vector<char> file;

	while (!in.eof())
	{
		file.push_back(in.get());
	}

	in.close();

	return file;
}