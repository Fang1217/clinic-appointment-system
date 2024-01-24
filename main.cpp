#include "Appointment.hpp"
#include "DateTime.hpp"
#include <stdexcept>
using namespace std;


int main()
{
	Appointment as; // Initiate the appointment system.

	DateTime currentMonth; // By default, show current month.

	string input;
	int choice;

	string response;

	while (true)
	{
		// show this month calendar feature
		as.displayCalendar(currentMonth);
		//Main menu section
		cout << "\n\n\n\n\n\n"; // Add extra lines for vertical spacing
		cout << " ******************************************\n";
		cout << "*        Welcome to Clinic Appointment     *\n";
		cout << "*                  System                  *\n";
		cout << " ******************************************\n\n";


		cout << "1. Add Appointment\n"
			<< "2. Search Appointment\n"
			<< "3. Display Appointment\n"
			<< "4. Delete Existing Appointment\n"
			<< "5. Edit Existing Appointment\n"
			<< "6. Exit\n\n";
		cout << "Please select your option (1-6): ";
		getline(cin, input);
		try {
			choice = stoi(input); // Convert the entire input to an integer
		}
		catch (const std::invalid_argument&) {
			choice = -1; // If conversion fails, set an invalid choice
		}

		switch (choice)
		{
		case 1: //Insert product
			as.add();
			break;
		case 2: //Search product
			as.search();
			break;
		case 3: //Edit
			as.display();
			break;
		case 4: //Delete
			as.remove();
			break;
		case 5: //Checkout
			as.edit();
			break;
		case 6:
			system("cls||clear"); //Clears terminal, where 'cls' - Windows, 'clear' - Mac devices.
			cout << "Goodbye !";
			return 0;
			break;
		default:
			response = "Invalid option!";
			cout << "Invalid Option! Please enter a number between 1 and 6." << endl;
			system("pause");
			system("cls||clear");
			break;
		}

	}
	return 0;
}