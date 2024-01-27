#include "Appointment.hpp"
using namespace std;

void Appointment::edit() {
	vector<int> resultIndexArray;
	search(resultIndexArray);

	if (numberOfAppointments == 0)
		return;

	string input;
	bool noTimeConflict;
	bool success;

	int numberOfResults = resultIndexArray.size();
	int indexToEdit;

	switch (numberOfResults) {
	case 0:
		cout << "Press Enter to continue.";
		cin.ignore();
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
			cout << "Input start time (YYYY/MM/DD HH:MM) [" << appointmentEntry.startTime.displayTime() << "]: ";
			getline(cin, startTimeInput);
			// Default input: remain no changes, else set the new time.
			success = startTimeInput.empty() ? startTime.setTime(appointmentEntry.startTime.displayTime()) : startTime.setTime(startTimeInput);
			if (success)
				continue;
			cout << "Error: Inputted date is an invalid format, please try again.\n";
		} while (!success);

		do {
			cout << "Input end time (YYYY/MM/DD HH:MM) [" << appointmentEntry.endTime.displayTime() << "]: ";
			getline(cin, endTimeInput);
			// Default input: remain no changes, else set the new time.
			success = endTimeInput.empty() ? endTime.setTime(appointmentEntry.endTime.displayTime()) : endTime.setTime(endTimeInput);
			if (success)
				continue;
			cout << "Error: Inputted date is an invalid format, please try again.\n";
		} while (!success);

		// Check time conflict before continuing
		noTimeConflict = checkConflict(startTime, endTime);
		if (noTimeConflict)
			break;
	} while (!noTimeConflict);

	int doctorID;
	string doctorName;
	string patientID;
	string patientName;
	string description;

	do {
		string input;
		cout << "Input new Doctor ID [" << appointmentEntry.doctorID << "]: ";
		getline(cin, input);
		success = input.empty() || regex_match(input, regex("^[0-9]+$"));
		if (success) {
			if (input.empty())
				doctorID = appointmentEntry.doctorID;
			else
				doctorID = stoi(input);
			continue;
		}
		cout << "Error: Invalid input, please try again.\n";
	} while (!success);

	do {
		cout << "Input new Doctor Name [" << appointmentEntry.doctorName << "]: ";
		getline(cin, doctorName);
		if (doctorName.empty())
			doctorName = appointmentEntry.doctorName;
	} while (false); //OCD hits

	do {
		cout << "Input new Patient NRIC (without symbols) [" << appointmentEntry.patientID << "]: ";
		getline(cin, patientID); 
		success = patientID.empty() || regex_match(patientID, regex("^[0-9]{12}$"));
		if (success) {
			if (patientID.empty())
				patientID = appointmentEntry.patientID;
			continue;
		}
		cout << "Error: Invalid input, please try again.\n";
	} while (!success);

	do {
		cout << "Input new Patient Name [" << appointmentEntry.patientName << "]: ";
		getline(cin, patientName);
		if (patientName.empty())
			patientName = appointmentEntry.patientName;
	} while (false);

	do {
		cout << "Input new Description [" << appointmentEntry.description << "]: ";
		getline(cin, description);
		if (description.empty())
			description = appointmentEntry.description;
	} while (false);

	appointmentNodeToEdit->appointmentEntry = AppointmentEntry(startTime, endTime, patientID, patientName, doctorID, doctorName, description);


	save();

	cout << "Entry edited successfully.";
	cin.ignore();
};