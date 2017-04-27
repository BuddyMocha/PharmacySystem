vector<Employee> employeeList;
string currentUser;
bool LoggedIn = false;

struct tm date;
int year;
int month;
int day;

//read in and store employee login info
void readEmployeeFile()
{
	ifstream file("EmployeeInfo.txt");
	vector<string> lines;
	string line;

	if (file.is_open())
	{
		while (getline(file, line))
		{
			//cout << line << '\n';
			lines.push_back(line);
		}
		file.close();

		for (unsigned int i = 0; i < lines.size(); i++)
		{
			line = lines[i];

			istringstream ss(line);
			string token;

			employeeList.push_back(Employee());

			getline(ss, token, ',');
			employeeList[i].name = token;

			getline(ss, token, ',');
			employeeList[i].username = token;

			getline(ss, token, ',');
			employeeList[i].password = token;

			//cout << Employees[i].name << endl;
			//cout << Employees[i].username << endl;
			//cout << Employees[i].password << endl;
		}
	}
	else cout << "Unable to open file";
}

//login to pharmacy system using employee info read from file
void employeeLogin()
{
	string userName;
	string password;
	bool found = false;

	readEmployeeFile();

	for (unsigned int i = 5; i > 0; i--)
	{
		cout << endl;
		cout << i << " tries remaining. \n";
		cout << "Enter your username and password.\n";
		cin >> userName >> password;


		for (unsigned int i = 0; i < employeeList.size(); i++)
		{
			if ((userName == employeeList[i].username) && (password == employeeList[i].password))
			{
				found = true;
				currentUser = employeeList[i].name;
				//cout << found << endl;
				break;
			}
		}

		if (found == true)
		{
			cout << "Access Granted. \n";
			LoggedIn = true;
			break;
		}
		else
		{
			cout << "Access Denied. \n";
		}
	}
}

//Verifies second employees credentials to allow transaction to be processed
bool verifyEmployee()
{
	string userName;
	string password;
	bool found = false;

	for (unsigned int i = 5; i > 0; i--)
	{
		cout << endl;
		cout << i << " tries remaining. \n";
		cout << "You need to have another employee verify this. \n";
		cout << "Enter their username and password.\n";
		cin >> userName >> password;

		for (unsigned int i = 0; i < employeeList.size(); i++)
		{
			if ((userName == employeeList[i].username) && (password == employeeList[i].password) && (employeeList[i].name != currentUser))
			{
				found = true;
				//cout << found << endl;
				break;
			}
		}

		if (found == true)
		{
			cout << "Valid Credentials. \n";
			return true;
			break;
		}
		else
		{
			cout << "Invalid Credentials. \n";
		}
	}

	return false;
}

//Get todays date
void getTodaysDate()
{
	time_t today = time(0);
	struct tm *now = localtime(&today);

	year = now->tm_year + 1900;
	month = now->tm_mon + 1;
	day = now->tm_mday;
}

//Setup date structure
void setupDate()
{
	date = { 0, 0, 0, 12 };

	//Set up the date structure
	date.tm_year = year - 1900;
	date.tm_mon = month - 1;		//note: zero indexed
	date.tm_mday = day;				//note: not zero indexed
}

//Add to a date
void datePlusDays(struct tm* date, int days)
{
	const time_t ONE_DAY = 24 * 60 * 60;

	//Seconds since start of epoch
	time_t date_seconds = mktime(date) + (days * ONE_DAY);

	//Update caller's date
	//Use localtime because mktime converts to UTC so may change date
	*date = *localtime(&date_seconds);;
}

//Update date
void updateDate()
{
	year = date.tm_year + 1900;
	month = date.tm_mon + 1;
	day = date.tm_mday;
}

//sample function to show how a program could run 
//note: there is a bug that I havent figured out yet
void sampleProgram()
{
	int choice;

	cout << "Enter '0' to go back to the main menu. ";

	while (!(cin >> choice) || (choice != 0))
	{
		cout << endl;
		cout << "Please enter '0' to go back to the main menu. ";
		cin >> choice;
		cin.clear();
		cin.ignore(100, '\n');

		if (choice == 0)
		{
			break;
		}
	}
}