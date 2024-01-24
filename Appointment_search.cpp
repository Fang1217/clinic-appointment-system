#include "Appointment.hpp"

void Appointment::search() {

	std::cout << "Search type [0 - Start Date, 1 - Patient, 2 - Doctor]: ";
	string searchTerm;
	getline(cin, searchTerm);
	int searchType = stoi(searchTerm);

	std::cout << "Input search term: ";
	string input;
	getline(cin, input);


	// Search 
	Queue searchQueue = searchEntry(searchTerm, searchType);

	if (searchQueue.isEmpty()) {
		cout << "no results found\n";
		cin.ignore();
		return;
	}
	else {
		// respond found (>=1)
		cout << "<Table header>\n";
		while (!searchQueue.isEmpty()) {
			// Find specific entry to display
			int index = searchQueue.getFrontAndPop();
			AppointmentNode* currentNodePointer = headNodePointer;
			for (int j = 0; j < index; j++) {
				currentNodePointer = currentNodePointer->nextNode;
			}
			AppointmentEntry appointmentEntry = currentNodePointer->appointmentEntry;
			cout << index << " | "
				<< appointmentEntry.startTime.displayTime() << " - "
				<< appointmentEntry.endTime.displayTime() << " | "
				<< appointmentEntry.patientID << " | "
				<< appointmentEntry.patientName << " | "
				<< appointmentEntry.doctorID << " | "
				<< appointmentEntry.doctorName << " | "
				<< appointmentEntry.description << " | "
				<< "\n";
		}
		cin.ignore();
	}
};
