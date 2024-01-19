#include "Appointment.hpp"

void Appointment::remove() {
	
	if (numberOfAppointments <= 0) {
		cout << "cannot delete entry if no appointments.\n"
			 << "Press enter to continue.";
		cin.ignore();
		return;
	}
	// delete operations

	// search using searchTerm and searchType
	
	// ask which type to search using the search keyword
	// ask what input to search
	std::cout << "Input search string: ";
	string searchTerm;
	getline(cin, searchTerm);
	std::cout << "Search type [0 - Date, 1 - Patient, 2 - Doctor]: ";
	string input;
	getline(cin, input);

	int searchType = stoi(input);

	// call saerch(string searchTerm, int searchType), based on output: V
	vector<int> resultVector = searchEntry(searchTerm, searchType);


	// 
	// through the list find all matches, if multiple, ask again which to delete.
	// 
	// 
	//

};
