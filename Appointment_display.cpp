#include "Appointment.hpp"
#include <iomanip> // for setw()

void Appointment::display() {
	const int DEFAULT_ENTRIES = 10;
	int entries;
	bool success;

	if (numberOfAppointments <= 0) {
		cout << "nothing to display\n";
		cin.ignore();
		return;
	}

	do {
		string input;
		cout << "Input how many entries to display [10]: ";
		getline(cin, input);
		success = input.empty() || regex_match(input, regex("^[0-9]+$"));
		if (success) {
			entries = input.empty() ? DEFAULT_ENTRIES : stoi(input);
			continue;
		}
		cout << "Error: invalid input, please try again.\n";
	} while (!success);
	
	//// Display the table, the length of each column is based on the longest content.
	cout << "Displaying " << min(numberOfAppointments, entries) << " entries: \n\n";
	
	// Find the maximum width of each column
	size_t maxColumnWidths[] = { 3, 14, 10, 10, 12 }; // Initial column widths"
	AppointmentNode* currentNodePointer = headNodePointer;
	for (int i = 0; i < min(numberOfAppointments, entries); i++) {
		AppointmentEntry ae = currentNodePointer->appointmentEntry;
		maxColumnWidths[0] = max(maxColumnWidths[0], to_string(i + 1).size());
		maxColumnWidths[1] = max(maxColumnWidths[1], ae.startTime.displayTime("%Y/%m/%d %H:%M").size() + ae.endTime.displayTime(" - %H:%M").size());
		maxColumnWidths[2] = max(maxColumnWidths[2], ae.patientID.size() + ae.patientName.size() + 2); // +2 for ": "
		maxColumnWidths[3] = max(maxColumnWidths[3], to_string(ae.doctorID).size() + ae.doctorName.size() + 2); // +2 for ": "
		maxColumnWidths[4] = max(maxColumnWidths[4], ae.description.size());

		currentNodePointer = currentNodePointer->nextNode;
	}

	// Display the table headers
	cout << setw(maxColumnWidths[0]) << right << "No." << " | "
		<< setw(maxColumnWidths[1]) << left << "Date & Time" << " | "
		<< setw(maxColumnWidths[2]) << left << "Patient" << " | "
		<< setw(maxColumnWidths[3]) << left << "Doctor" << " | "
		<< setw(maxColumnWidths[4]) << left << "Description" << " | "
		<< endl;

	// Display the table separator
	for (int i = 0; i < sizeof(maxColumnWidths) / sizeof(maxColumnWidths[0]); ++i) {
		cout << string(maxColumnWidths[i], '-') << " | ";
	}
	cout << endl;

	// Display the appointments
	currentNodePointer = headNodePointer;
	for (int i = 0; i < min(numberOfAppointments, entries); i++) {
		AppointmentEntry ae = currentNodePointer->appointmentEntry;
		cout << setw(maxColumnWidths[0]) << right << i + 1 << " | "
			<< setw(maxColumnWidths[1]) << left << ae.startTime.displayTime("%Y/%m/%d %H:%M") + " - " + ae.endTime.displayTime("%H:%M") << " | "
			<< setw(maxColumnWidths[2]) << ae.patientID + ": " + ae.patientName << " | "
			<< setw(maxColumnWidths[3]) << ae.doctorID + ": " + ae.doctorName << " | "
			<< setw(maxColumnWidths[4]) << ae.description << " | "
			<< endl;

		currentNodePointer = currentNodePointer->nextNode;
	}

	//  update: change to select sort by, if needed, or exit.
	cout << "\nPress Enter to continue.\n\n";
	cin.ignore();
}