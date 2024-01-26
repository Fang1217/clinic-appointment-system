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
		//Main menu section
		cout << "\n\n"; // Add extra lines for vertical spacing
		cout << "********************************************************\n";
		cout << "*            Welcome to Clinic Appointment             *\n";
		cout << "*                        System                        *\n";
		cout << "********************************************************\n\n";

	
		// show this month calendar feature
		int month = currentMonth.getMonth();
		int year = currentMonth.getYear();
		currentMonth.setTime(year, month); // set the date to 1st for calendar.
		as.displayCalendar(currentMonth);

		cout << "1. Display Appointment(s)\n"
			<< "2. Search Appointment(s)\n"
			<< "3. Add Appointment\n"
			<< "4. Delete Existing Appointment\n"
			<< "5. Edit Existing Appointment\n\n"
			
			<< "8. Calendar: Show previous month\n"
			<< "9. Calendar: Show next month\n\n"

			<< "0. Exit\n\n";
		cout << "Please select your option: ";
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
			as.display();
			break;
		case 2: //Search product
			as.search();
			break;
		case 3: //Display
			as.add();
			break;
		case 4: //Delete
			as.remove();
			break;
		case 5: //Edit
			as.edit();
			break;
		case 8: //Previous Month
			currentMonth.setTime(month == 1 ? year - 1 : year, month == 1 ? 12 : month - 1);
			system("cls||clear");
			break;
		case 9: //Next Month
			currentMonth.setTime(month == 12 ? year + 1 : year, month == 12 ? 1 : month + 1);
			system("cls||clear");
			break;
		case 0:
			cout << "\nGoodbye !";
			return 0;
			break;
		default:
			response = "Invalid option!";
			cout << "Invalid Option! Please Enter a number between 1 and 6." << endl;
			system("pause");
			system("cls||clear");
			break;
		}

	}
	return 0;
}