#include "Appointment.hpp"
#include "DateTime.hpp"
using namespace std;


int main()
{
	Appointment as; // Initiate the appointment system.
	
	DateTime currentMonth; // By default, show current month.
	
	string input;
	char choice;

	string response;

	while (true)
	{
		// show this month calendar feature
		as.displayCalendar(currentMonth);
		//Main menu section
		cout << "\n\tWelcome to Clinic Appointment System.\n";

		cout << "1. Add Appointment\n"
			 << "2. Search Appointment\n"
			 << "3. Display Appointment\n"
			 << "4. Delete Existing Appointment\n"
			 << "5. Edit Existing Appointment\n"
			 << "6. Exit\n\n";
		cout << "Please select your option (1-6): ";
		getline(cin, input); //Using getline instead of cin to combat errors regarding spaces.
		choice = input[0]; // Only receive one letter to prevent error.
		switch (choice)
		{
		case '1': //Insert product
			as.add();
			break;
		case '2': //Search product
			as.search();
			break;
		case '3': //Edit
			as.display();
			break;
		case '4': //Delete
			as.remove();
			break;
		case '5': //Checkout
			as.edit();
			break;
		case '6':
			system("cls||clear"); //Clears terminal, where 'cls' - Windows, 'clear' - Mac devices.
			cout << "Goodbye !";
			return 0;
			break;
		default:;
			response = "Invalid option!";
			break;
		}

	}
	return 0;
}