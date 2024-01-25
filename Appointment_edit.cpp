#include "Appointment.hpp"
using namespace std;

void Appointment::edit() {
	vector<int> resultIndexArray;
	search(resultIndexArray);

	string input;
	bool timeConflict;
	bool success;

	int numberOfResults = sizeof(resultIndexArray);
	int indexToEdit;

	switch (numberOfResults) {
	case 0:
		cout << "No results found.\nPress Enter to continue.";
		cin.ignore();
		return;

	case 1:
		cout << "Edit this entry? [y/N]";
		getline(cin, input);
		if (toupper(input[0]) == 'Y') {
			int index = resultIndexArray[0];
			removeAppointmentNode(index);
		}
		else return;
		break;

	default: // numberOfResults > 1
		bool validInt;
		bool validPosition;
		do {
			do {
				cout << "Select which entry to edit: ";
				getline(cin, input);
				validInt = regex_match(input, regex("[0-9]+"));
				if (validInt)
					continue;
				cout << "Error: invalid input, please try again.\n";
			} while (!validInt);

			int position = stoi(input) - 1;
			validPosition = position < 0 && position >= numberOfResults;
			if (validPosition) {
				indexToEdit = resultIndexArray[position];
				continue;
			}
			cout << "Error: invalid index to remove, please try again.\n";
		} while (!validPosition);
	};
		
	AppointmentEntry appointmentEntryToEdit = getAppointmentNode(indexToEdit)->appointmentEntry;


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

	appointmentEntryToEdit = AppointmentEntry(startTime, endTime, patientID, patientName, stoi(doctorID), doctorName, description);

	save();

	cout << "Entry edited successfully.";
	cin.ignore();
};