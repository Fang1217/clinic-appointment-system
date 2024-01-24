#include "Appointment.hpp"

void Appointment::remove() {

	if (numberOfAppointments <= 0) {
		cout << "cannot delete entry if no appointments.\n"
			<< "Press enter to continue.";
		cin.ignore();
		return;
	}

	cout << "Search type [0 - Start Date, 1 - Patient, 2 - Doctor]: ";
	string input;
	getline(cin, input);
	int searchType = stoi(input);

	cout << ((searchType == 0) ? "Input start date (YYYY/MM/DD): " : "Input search term: ");
	string searchTerm;
	getline(cin, searchTerm);

	Queue resultQueue = searchEntry(searchTerm, searchType);
	int numberOfResults = resultQueue.count;

	if (numberOfResults == 0) {
		cout << "no results found\n";
		cin.ignore();
		return;
	}
	cout << "Found " << numberOfResults << " entries:\n";
	cout << "<Table header>\n";

	AppointmentNode* currentNodePointer = headNodePointer;
	int* indexArray = new int[numberOfResults];

	for (int i = 0; i < numberOfResults; i++) {
		int index = resultQueue.getFrontAndPop();
		indexArray[i] = index;

		for (int j = 0; j < index; j++) {
			currentNodePointer = currentNodePointer->nextNode;
		}
		AppointmentEntry appointmentEntry = currentNodePointer->appointmentEntry;
		if (numberOfResults > 1) {
			cout << i+1 << "\t";
			cout << appointmentEntry.startTime.displayTime("%Y/%m/%d %H:%M") << " - "
			<< appointmentEntry.endTime.displayTime("%H:%M") << " | "
			<< appointmentEntry.patientID << ":"
			<< appointmentEntry.patientName << " | "
			<< appointmentEntry.doctorID << ": "
			<< appointmentEntry.doctorName << " | "
			<< appointmentEntry.description << " | "
			<< "\n";
		}
	}

	if (numberOfResults == 1) {
		cout << "Remove this entry? (Y/N)";
		getline(cin, input);
		if (toupper(input[0]) == 'Y') {
			AppointmentNode* temp = currentNodePointer;
			if (currentNodePointer == headNodePointer) {
				headNodePointer = currentNodePointer->nextNode;
			}
			currentNodePointer = currentNodePointer->nextNode;
			delete temp;
			temp = NULL;
		}
	}
	else {
	removeID:
		cout << "Select which entry to remove.\n";
		getline(cin, input);
		if (!regex_match(input, regex("^[0-9]+$"))) {
			cout << "Error: invalid input, please try again.\n";
			goto removeID;
		}
		
		int indexToRemove = stoi(input) - 1;
		if (indexToRemove < 0 || indexToRemove >= numberOfResults) {
			cout << "Error: invalid index to remove, please try again.\n";
			goto removeID;
		}
		AppointmentNode* currentNodePointer = headNodePointer;

		// Traverse to the node to remove
		for (int j = 0; j < indexArray[indexToRemove]; j++) {
			currentNodePointer = currentNodePointer->nextNode;
		}

		// Remove the node
		AppointmentNode* temp = currentNodePointer;
		if (currentNodePointer == headNodePointer) {
			headNodePointer = currentNodePointer->nextNode;
		}
		currentNodePointer = currentNodePointer->nextNode;
		delete temp;
		temp = NULL;
	}
	
	numberOfAppointments--;
	save();

	cout << "Entry removed successfully.";
	cin.ignore();
};