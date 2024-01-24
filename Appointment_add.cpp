#include "Appointment.hpp"

void Appointment::add() {
	bool success;
	// To add: Verify inputs + activate time slot checker

	startTime:
		cout << "Input start time (YYYY/MM/DD HH:MM): ";
		string startTimeInput;
		getline(cin, startTimeInput);
		DateTime startTime = DateTime();
		success = startTime.setTime(startTimeInput);
		if (!success) {
			cout << "Error: invalid format, please try again.\n";
			goto startTime;
		}

	endTime:
		cout << "Input end time (YYYY/MM/DD HH:MM): ";
		string endTimeInput;
		getline(cin, endTimeInput);
		DateTime endTime = DateTime();
		success = endTime.setTime(endTimeInput);
		if (!success) {
			cout << "Error: invalid format, please try again.\n";
			goto endTime;
		}

	// Check time conflict before continuing
	if (!checkConflict(startTime, endTime))
		goto startTime;

	doctorID: 
		cout << "Input Doctor ID: ";
		string doctorID;
		getline(cin, doctorID);
		if (!regex_match(doctorID, regex("[0-9]+"))) {
			cout << "Error: invalid input, please try again.\n";
			goto doctorID;
		}

	doctorName: 
		cout << "Input Doctor Name: ";
		string doctorName;
		getline(cin, doctorName);
		if (doctorName.empty()) {
			cout << "Error: invalid input, please try again.\n";
			goto doctorName;
		}

	patientID:
		cout << "Input Patient ID: ";
		string patientID;
		getline(cin, patientID);
		if (!regex_match(doctorID, regex("[0-9]+"))) {
			cout << "Error: invalid input, please try again.\n";
			goto patientID;
		}

	patientName:
		cout << "Input Patient Name: ";
		string patientName;
		getline(cin, patientName);
		if (patientName == "") {
			cout << "Error: invalid input, please try again.\n";
			goto patientName;
		}
	
	description:
		std::cout << "Input Description: ";
		string description;
		getline(cin, description);
		if (description == "") {
			cout << "Error: invalid input, please try again.\n";
			goto description;
		}

	AppointmentNode* newAppointmentNode = new AppointmentNode;
	newAppointmentNode->appointmentEntry = AppointmentEntry(startTime, endTime, stoi(patientID), patientName, stoi(doctorID), doctorName, description);
	newAppointmentNode->nextNode = NULL;

	if (headNodePointer == NULL) {
		headNodePointer = newAppointmentNode;
	}
	else {
		AppointmentNode* currentNodePointer = headNodePointer;
		while (currentNodePointer->nextNode != NULL)
		{
			currentNodePointer = currentNodePointer->nextNode;
		}
		currentNodePointer->nextNode = newAppointmentNode;
	}
	numberOfAppointments++;

	sortEntry(headNodePointer);
	save();

	cout << "Appointment added successfully.\n" << 
			"Press any key to continue.";
	cin.ignore();

}
