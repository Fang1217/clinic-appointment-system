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
	AppointmentEntry appointmentEntryToEdit = AppointmentEntry(appointmentNodeToEdit->appointmentEntry);
	removeAppointmentNode(indexToEdit);

	// original times
	DateTime originalStartTime = DateTime(appointmentEntryToEdit.startTime);
	DateTime originalEndTime = DateTime(appointmentEntryToEdit.endTime);
	DateTime newStartTime = DateTime();
	DateTime newEndTime = DateTime();
	string startTimeInput;
	string endTimeInput;

	do {
		do {
			cout << "Input start time (YYYY/MM/DD HH:MM) [" << originalStartTime.displayTime() << "]: ";
			getline(cin, startTimeInput);
			// Default input: remain no changes, else set the new time.
			if (startTimeInput.empty())
				startTimeInput = originalStartTime.displayTime();
			success = newStartTime.setTime(startTimeInput);
			if (success)
				continue;
			cout << "Error: Inputted date is invalid, please try again.\n";
		} while (!success);

		do {
			cout << "Input end time (YYYY/MM/DD HH:MM) [" << originalEndTime.displayTime() << "]: ";
			getline(cin, endTimeInput);
			// Default input: remain no changes, else set the new time.
			if (endTimeInput.empty())
				endTimeInput = originalEndTime.displayTime();
			success = newEndTime.setTime(endTimeInput) && (newEndTime.getTime() > newStartTime.getTime());
			if (success)
				continue;
			cout << "Error: Inputted date is invalid, please try again.\n";
		} while (!success);

		// Check time conflict before continuing
		noTimeConflict = checkConflict(newStartTime, newEndTime);
		if (noTimeConflict) 
			break;
		appointmentEntryToEdit.startTime = originalStartTime;
		appointmentEntryToEdit.endTime = originalEndTime;
	} while (!noTimeConflict);

	int doctorID;
	string doctorName;
	string patientID;
	string patientName;
	string description;

	do {
		string input;
		cout << "Input new Doctor ID [" << appointmentEntryToEdit.doctorID << "]: ";
		getline(cin, input);
		success = input.empty() || regex_match(input, regex("^[0-9]+$"));
		if (success) {
			if (input.empty())
				doctorID = appointmentEntryToEdit.doctorID;
			else
				doctorID = stoi(input);
			continue;
		}
		cout << "Error: Invalid input, please try again.\n";
	} while (!success);

	do {
		cout << "Input new Doctor Name [" << appointmentEntryToEdit.doctorName << "]: ";
		getline(cin, doctorName);
		if (doctorName.empty())
			doctorName = appointmentEntryToEdit.doctorName;
	} while (false); //OCD hits

	do {
		cout << "Input new Patient NRIC (without symbols) [" << appointmentEntryToEdit.patientID << "]: ";
		getline(cin, patientID); 
		success = patientID.empty() || regex_match(patientID, regex("^[0-9]{12}$"));
		if (success) {
			if (patientID.empty())
				patientID = appointmentEntryToEdit.patientID;
			continue;
		}
		cout << "Error: Invalid input, please try again.\n";
	} while (!success);

	do {
		cout << "Input new Patient Name [" << appointmentEntryToEdit.patientName << "]: ";
		getline(cin, patientName);
		if (patientName.empty())
			patientName = appointmentEntryToEdit.patientName;
	} while (false);

	do {
		cout << "Input new Description [" << appointmentEntryToEdit.description << "]: ";
		getline(cin, description);
		if (description.empty())
			description = appointmentEntryToEdit.description;
	} while (false);

	appointmentEntryToEdit = AppointmentEntry(newStartTime, newEndTime, patientID, patientName, doctorID, doctorName, description);
	addAppointmentMode(appointmentEntryToEdit);

	save();

	cout << "Entry edited successfully.";
	cin.ignore();
};