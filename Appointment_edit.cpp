#include "Appointment.hpp"

void Appointment::edit() {
	if (numberOfAppointments <= 0) {
		cout << "cannot edit entry if no appointments.\n"
			<< "Press enter to continue.";
		cin.ignore();
		return;
	}

	std::cout << "Input search string: ";
	string searchTerm;
	getline(cin, searchTerm);
	std::cout << "Search type [0 - Date, 1 - Patient, 2 - Doctor]: ";
	string input;
	getline(cin, input);

	int searchType = stoi(input);

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
		if (numberOfResults > 1)
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

	if (numberOfResults == 1) {
		cout << "Edit this entry? (Y/N)";
		getline(cin, input);
		if (!(toupper(input[0]) == 'Y')) {
			return;
		}
	}
	else { // numberOfResults > 1
	editID:
		cout << "Select which entry to edit: ";
		getline(cin, input);
		if (!regex_match(input, regex("[0-9]+"))) {
			cout << "Error: invalid input, please try again.\n";
			goto editID;
		}
		int indexToEdit = stoi(input) - 1;
		if (indexToEdit < 0 && indexToEdit >= numberOfResults) {
			cout << "Error: invalid index to remove, please try again.\n";
			goto editID;
		}
		currentNodePointer = headNodePointer;

		// Traverse to the node to edit
		for (int j = 0; j < indexArray[indexToEdit]; j++) {
			currentNodePointer = currentNodePointer->nextNode;
		}
	}

	AppointmentEntry appointmentEntryToEdit = currentNodePointer->appointmentEntry;

	bool success;
	// To add: Verify inputs + activate time slot checker

startTime:
	std::cout << "Input start time (YYYY/MM/DD HH:MM) [" << appointmentEntryToEdit.startTime.displayTime() << "]: " << endl;
	string startTimeInput;
	getline(cin, startTimeInput);
	DateTime startTime = DateTime();

	// Default input: remain no changes, else set the new time.
	success = startTimeInput.empty() ? startTime.setTime(appointmentEntryToEdit.startTime.displayTime()) : startTime.setTime(startTimeInput);
	if (!success) {
		cout << "Error: invalid format, please try again.\n";
		goto startTime;
	}

endTime:
	std::cout << "Input end time (YYYY/MM/DD HH:MM): " << appointmentEntryToEdit.endTime.displayTime() << "]: " << endl;
	string endTimeInput;
	getline(cin, endTimeInput);
	DateTime endTime = DateTime();

	// Default input: remain no changes, else set the new time.
	success = endTimeInput.empty() ? endTime.setTime(appointmentEntryToEdit.endTime.displayTime()) : endTime.setTime(endTimeInput);
	if (!success) {
		cout << "Error: invalid format, please try again.\n";
		goto endTime;
	}

	// Check time conflict before continuing
	if (!checkConflict(startTime, endTime))
		goto startTime;

doctorID:
	std::cout << "Input Doctor ID: " << appointmentEntryToEdit.doctorID << "]: " << endl;
	string doctorID;
	getline(cin, doctorID);
	if (!regex_match(doctorID, regex("[0-9]+"))) {
		cout << "Error: invalid input, please try again.\n";
		goto doctorID;
	}

doctorName:
	std::cout << "Input Doctor Name: " << appointmentEntryToEdit.doctorName << "]: " << endl;
	string doctorName;
	getline(cin, doctorName);
	if (doctorName == "") {
		cout << "Error: invalid input, please try again.\n";
		goto doctorName;
	}

patientID:
	std::cout << "Input Patient ID: " << appointmentEntryToEdit.patientID << "]: " << endl;
	string patientID;
	getline(cin, patientID);
	if (!regex_match(doctorID, regex("[0-9]+"))) {
		cout << "Error: invalid input, please try again.\n";
		goto patientID;
	}

patientName:
	std::cout << "Input new patient Name: " << appointmentEntryToEdit.patientName << "]: " << endl;
	string patientName;
	getline(cin, patientName);
	if (patientName == "") {
		cout << "Error: invalid input, please try again.\n";
		goto patientName;
	}

description:
	std::cout << "Input new description: [" << appointmentEntryToEdit.description << "]: " << endl;
	string description;
	getline(cin, description);
	if (description == "") {
		cout << "Error: invalid input, please try again.\n";
		goto description;
	}

	currentNodePointer->appointmentEntry = AppointmentEntry(startTime, endTime, stoi(patientID), patientName, stoi(doctorID), doctorName, description);

	save();

	cout << "Entry edited successfully.";
	cin.ignore();
};