#include "Appointment.hpp"
using namespace std;


int main()
{
	std::cout << "Hello World!" << endl;

	//Load(); //Read file.
	Appointment as; // Initiate the appointment system.
	string input;
	char choice;

	string response;

	while (true)
	{
		system("cls||clear");

		//Main menu section
		cout << "\n\tWelcome to Clinic Appointment System.\n";


		// show todays appointment feature


		cout << "1. Add Appointment\n"
			 << "2. Search Appointment\n"
			 << "3. Display Appointment\n"
			 << "4. Delete Existing Appointment\n\n"
			//pending add edit 
			 << "5. Exit\n\n";
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
			//Checkout();
			break;
		case '6':
			system("cls||clear"); //Clears terminal, where 'cls' - Windows, 'clear' - Mac devices.
			cout << "Goodbye !";
			return 0;
			break;
		default:
			system("cls||clear");
			response = "Invalid option!";
			break;
		}
	}
	return 0;
}