#include "Appointment.hpp"

void Appointment::edit() {
	if (numberOfAppointments <= 0) {
		cout << "Unable to edit entry if there are no appointment entries.\n"
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
	bool timeConflict;

	DateTime startTime = DateTime();
	DateTime endTime = DateTime();
	string startTimeInput;
	string endTimeInput;

	do {
		do {
			cout << "Input start time (YYYY/MM/DD HH:MM) [" << appointmentEntryToEdit.startTime.displayTime() << "]: " << endl;
			getline(cin, startTimeInput);
			// Default input: remain no changes, else set the new time.
			success = startTimeInput.empty() ? startTime.setTime(appointmentEntryToEdit.startTime.displayTime()) : startTime.setTime(startTimeInput);
			if (success)
				continue;
			cout << "Error: Inputted date is an invalid format, please try again.\n";
		} while (!success);

		do {
			cout << "Input end time (YYYY/MM/DD HH:MM): " << appointmentEntryToEdit.endTime.displayTime() << "]: " << endl;
			getline(cin, endTimeInput);
			// Default input: remain no changes, else set the new time.
			success = endTimeInput.empty() ? endTime.setTime(appointmentEntryToEdit.endTime.displayTime()) : endTime.setTime(endTimeInput);
			if (success)
				continue;
			cout << "Error: Inputted date is an invalid format, please try again.\n";
		} while (!success);

		// Check time conflict before continuing
		timeConflict = checkConflict(startTime, endTime);

	} while (timeConflict);

	string doctorID;
	string doctorName;
	string patientID;
	string patientName;
	string description;

	do {
		cout << "Input new Doctor ID [" << appointmentEntryToEdit.doctorID << "]: " << endl;
		getline(cin, doctorID);
		success = regex_match(doctorID, regex("^[0-9]+$"));
		if (success)
			continue;
		cout << "Error: invalid input, please try again.\n";
	} while (!success);

	do {
		cout << "Input new Doctor Name [" << appointmentEntryToEdit.doctorName << "]: " << endl;
		getline(cin, doctorName);
		success = !(doctorName.empty());
		if (success)
			continue;
		cout << "Error: invalid input, please try again.\n";
	} while (!success);

	do {
		cout << "Input new Patient NRIC (without symbols) [" << appointmentEntryToEdit.patientID << "]: " << endl;
		getline(cin, patientID);
		success = regex_match(patientID, regex("^[0-9]{12}$"));
		if (success)
			continue;
		cout << "Error: invalid input, please try again.\n";
	} while (!success);

	do {
		cout << "Input new Patient Name [" << appointmentEntryToEdit.patientName << "]: " << endl;
		getline(cin, patientName);
		success = !(patientName.empty());
		if (success)
			continue;
		cout << "Error: invalid input, please try again.\n";
	} while (!success);

	do {
		cout << "Input new Description [" << appointmentEntryToEdit.description << "]: " << endl;
		getline(cin, description);
		success = !(description.empty());
		if (success)
			continue;
		cout << "Error: invalid input, please try again.\n";
	} while (!success);

	currentNodePointer->appointmentEntry = AppointmentEntry(startTime, endTime, patientID, patientName, stoi(doctorID), doctorName, description);

	save();

	cout << "Entry edited successfully.";
	cin.ignore();
};