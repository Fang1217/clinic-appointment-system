#include "Appointment.hpp"

void Appointment::display() {

	if (numberOfAppointments <= 0) {
		cout << "nothing to display\n";
		cin.ignore();
		return;
	}

	cout << "Input how many entries to display (Default: 10): ";
	string input;
	int entries;
	getline(cin, input);
	try {
		entries = stoi(input);
	}
	catch (invalid_argument) { entries = 10; }

	cout << "Displaying " << min(numberOfAppointments, entries) << " entries: \n";
	// add table header

	// display specific number of entries.
	try {
		AppointmentNode* currentNodePointer = headNodePointer;
		for (int i = 0; i < min(numberOfAppointments, entries); i++) {
			AppointmentEntry appointmentEntry = currentNodePointer->appointmentEntry;
			cout << " " << i + 1 << "\t | "
				<< appointmentEntry.startTime.displayDate("%Y/%m/%d %H:%M") << " - "
				<< appointmentEntry.endTime.displayTime("%H:%M") << " | "
				<< appointmentEntry.patientID << ": "
				<< appointmentEntry.patientName << "\t | "
				<< appointmentEntry.doctorID << ": "
				<< appointmentEntry.doctorName << "\t | "
				<< appointmentEntry.description << "\t | "
				<< "\n";

			currentNodePointer = currentNodePointer->nextNode;
		}
	}
	catch (exception e) { cout << "Error display"; };
	//  update: change to select sort by, if needed, or exit.
	cout << "\nPress Enter to continue.\n\n";
	cin.ignore();
}