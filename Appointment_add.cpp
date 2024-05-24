#include "Appointment.hpp"

void Appointment::add() {
	bool success;
	string input;

	DateTime startTime = DateTime();
	DateTime endTime = DateTime();
	do {
		do {
			cout << "Input start time (YYYY/MM/DD HH:MM): ";
			getline(cin, input);
			success = startTime.setTime(input);
			if (success)
				continue;
			cout << "Error: Inputted date is invalid, please try again.\n";
		} while (!success);

		do {
			cout << "Input end time (YYYY/MM/DD HH:MM): ";
			getline(cin, input);
			success = endTime.setTime(input) && endTime.getTime() > startTime.getTime();
			if (success)
				continue;
			cout << "Error: Inputted date is invalid, please try again.\n";
		} while (!success);
	} while (!checkConflict(startTime, endTime));
	// Check time conflict before continuing

	int doctorID;
	string doctorName;
	string patientID;
	string patientName;
	string description;

	do {
		cout << "Input Doctor ID: ";
		getline(std::cin, input);
		success = regex_match(input, regex("^[0-9]+$"));
		if (success) {
			doctorID = stoi(input);
			continue;
		}
		cout << "Error: Invalid input, please try again.\n\n";
	} while (!success);

	do {
		cout << "Input Doctor Name: ";
		getline(std::cin, doctorName);
		success = !(doctorName.empty());
		if (success)
			continue;
		cout << "Error: Invalid input, please try again.\n\n";
	} while (!success);

	do {
		cout << "Input Patient NRIC (without symbols): ";
		getline(std::cin, patientID);
		success = regex_match(patientID, regex("^[0-9]{12}$"));
		if (success)
			continue;
		cout << "Error: Invalid input, please try again.\n\n";
	} while (!success);

	do {
		cout << "Input Patient Name: ";
		getline(std::cin, patientName);
		success = !(patientName.empty());
		if (success)
			continue;
		cout << "Error: Invalid input, please try again.\n\n";
	} while (!success);

	do {
		cout << "Input Description: ";
		getline(std::cin, description);
		success = !(description.empty());
		if (success)
			continue;
		cout << "Error: Invalid input, please try again.\n\n";
	} while (!success);

	AppointmentEntry newAppointment = AppointmentEntry(startTime, endTime, patientID, patientName, doctorID, doctorName, description);
	addAppointmentMode(newAppointment);

	save();

	cout << "Appointment added successfully.\n"
		<< "Press any key to continue.";
	cin.ignore();
}