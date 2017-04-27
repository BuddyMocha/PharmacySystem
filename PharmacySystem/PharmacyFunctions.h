
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