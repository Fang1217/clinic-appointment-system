#include "Appointment.hpp"
using namespace std;

void Appointment::edit() {
	vector<int> resultIndexArray;
	search(resultIndexArray);

	string input;
	bool timeConflict;
	bool success;

	int numberOfResults = resultIndexArray.size();
	int indexToEdit;

	switch (numberOfResults) {
	case 0:
		return;

	case 1:
		cout << "Edit this entry? [y/N]";
		getline(cin, input);
		if (toupper(input[0]) == 'Y') {
			indexToEdit = resultIndexArray[0];
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
				cout << "Error: Invalid input, please try again.\n";
			} while (!validInt);

			int position = stoi(input) - 1; 
			validPosition = position >= 0 && position < numberOfResults; // valid position is from 0 to numberOfResults
			if (validPosition) {
				indexToEdit = resultIndexArray[position];
				continue;
			}
			cout << "Error: Invalid index to remove, please try again.\n";
		} while (!validPosition);
	};
	AppointmentNode* appointmentNodeToEdit = getAppointmentNode(indexToEdit);
	AppointmentEntry appointmentEntry = appointmentNodeToEdit->appointmentEntry;

	DateTime startTime = DateTime();
	DateTime endTime = DateTime();
	string startTimeInput;
	string endTimeInput;

	do {
		do {
			cout << "Input start time (YYYY/MM/DD HH:MM) [" << appointmentEntry.startTime.displayTime() << "]: " << endl;
			getline(cin, startTimeInput);
			// Default input: remain no changes, else set the new time.
			success = startTimeInput.empty() ? startTime.setTime(appointmentEntry.startTime.displayTime()) : startTime.setTime(startTimeInput);
			if (success)
				continue;
			cout << "Error: Inputted date is an invalid format, please try again.\n";
		} while (!success);

		do {
			cout << "Input end time (YYYY/MM/DD HH:MM): " << appointmentEntry.endTime.displayTime() << "]: " << endl;
			getline(cin, endTimeInput);
			// Default input: remain no changes, else set the new time.
			success = endTimeInput.empty() ? endTime.setTime(appointmentEntry.endTime.displayTime()) : endTime.setTime(endTimeInput);
			if (success)
				continue;
			cout << "Error: Inputted date is an invalid format, please try again.\n";
		} while (!success);

		// Check time conflict before continuing
		timeConflict = checkConflict(startTime, endTime);
		if (!timeConflict)
			break;

	} while (timeConflict);

	string doctorID;
	string doctorName;
	string patientID;
	string patientName;
	string description;

	do {
		cout << "Input new Doctor ID [" << appointmentEntry.doctorID << "]: " << endl;
		getline(cin, doctorID);
		success = regex_match(doctorID, regex("^[0-9]+$"));
		if (success)
			continue;
		cout << "Error: Invalid input, please try again.\n";
	} while (!success);

	do {
		cout << "Input new Doctor Name [" << appointmentEntry.doctorName << "]: " << endl;
		getline(cin, doctorName);
		success = !(doctorName.empty());
		if (success)
			continue;
		cout << "Error: Invalid input, please try again.\n";
	} while (!success);

	do {
		cout << "Input new Patient NRIC (without symbols) [" << appointmentEntry.patientID << "]: " << endl;
		getline(cin, patientID);
		success = regex_match(patientID, regex("^[0-9]{12}$"));
		if (success)
			continue;
		cout << "Error: Invalid input, please try again.\n";
	} while (!success);

	do {
		cout << "Input new Patient Name [" << appointmentEntry.patientName << "]: " << endl;
		getline(cin, patientName);
		success = !(patientName.empty());
		if (success)
			continue;
		cout << "Error: Invalid input, please try again.\n";
	} while (!success);

	do {
		cout << "Input new Description [" << appointmentEntry.description << "]: " << endl;
		getline(cin, description);
		success = !(description.empty());
		if (success)
			continue;
		cout << "Error: Invalid input, please try again.\n";
	} while (!success);

	appointmentNodeToEdit->appointmentEntry = AppointmentEntry(startTime, endTime, patientID, patientName, stoi(doctorID), doctorName, description);


	save();

	cout << "Entry edited successfully.";
	cin.ignore();
};