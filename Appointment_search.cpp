#include "Appointment.hpp"

void Appointment::search() {

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

	if (resultVector.size() == 0) {
		cout << "no results found\n";
		cin.ignore();
		return;
	}
	else {
		// respond found (>=1)
		cout << "<Table header>\n";
		for (int i = 0; i < resultVector.size(); i++) {
			cout 
				<< appointments[i].startTime << " | "
				<< appointments[i].endTime << " | "
				<< appointments[i].patientID << " | "
				<< appointments[i].patientName << " | "
				<< appointments[i].doctorID << " | "
				<< appointments[i].doctorName << " | "
				<< appointments[i].description << " | "
				<< "\n";
		}
		
	}
};
