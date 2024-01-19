#include "Appointment.hpp"
using namespace std;


int main()
{
	std::cout << "Hello World!" << endl;

	//Load(); //Read file.
	Appointment as;
	string input;
	char choice;

	string response;

	while (true)
	{
		cout << response << endl;
		//Main menu section
		cout << "\n\tWelcome to Clinic Appointment System.\n";

		//if (productCount > 0) {
		//    //If at least 1 product is added, display the cart.
		//    cout << "\nCurrent inventory:\n";   
		//    Display(0, productCount);
		//
		// show todays appointment feature


		cout << "1. Add Appointment\n"
			 << "2. Search Appointment\n"
			 << "3. Delete Existing Appointment\n"
			//pending add edit 
			 << "4. Exit\n\n";
		cout << "Please select your option (1-6): ";
		getline(cin, input); //Using getline instead of cin to combat errors regarding spaces.
		choice = input[0]; // Only receive one letter to prevent error.
		switch (choice)
		{
		case '1': //Insert product
			as.addEntry(response);
			break;
		case '2': //Search product
			//as.();
			break;
		case '3': //Edit
			//Edit();
			break;
		case '4': //Delete
			//Delete();
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