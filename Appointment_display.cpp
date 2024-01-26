#include "Appointment.hpp"
#include <iomanip> // for setw()

void Appointment::display() {

	string input;

	const int DEFAULT_ENTRIES = 10;
	int entries;
	bool success;
	bool validInt;

	if (numberOfAppointments <= 0) {
		cout << "Nothing to display.\n Please enter to continue.";
		cin.ignore();
		return;
	}

	do {
		cout << "Input how many entries to display [10]: ";
		getline(cin, input);
		success = input.empty() || regex_match(input, regex("^[0-9]+$"));
		if (success) {
			entries = min(input.empty() ? DEFAULT_ENTRIES : stoi(input), numberOfAppointments);
			continue;
		}
		cout << "Error: invalid input, please try again.\n";
	} while (!success);
	
	while (true) 
	{
		//// Display the table, the length of each column is based on the longest content.
		cout << "Displaying " << entries << " entries: \n\n";

		// Find the maximum width of each column
		size_t maxColumnWidths[] = { 3, 14, 10, 10, 12 }; // Initial column widths
		AppointmentNode* currentNodePointer = headNodePointer;
		for (int i = 0; i < entries; i++) {
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
		for (int i = 0; i < entries; i++) {
			AppointmentEntry ae = currentNodePointer->appointmentEntry;
			cout << setw(maxColumnWidths[0]) << right << i + 1 << " | "
				<< setw(maxColumnWidths[1]) << left << ae.startTime.displayTime("%Y/%m/%d %H:%M") + " - " + ae.endTime.displayTime("%H:%M") << " | "
				<< setw(maxColumnWidths[2]) << ae.patientID + ": " + ae.patientName << " | "
				<< setw(maxColumnWidths[3]) << to_string(ae.doctorID) + ": " + ae.doctorName << " | "
				<< setw(maxColumnWidths[4]) << ae.description << " | "
				<< endl;

			currentNodePointer = currentNodePointer->nextNode;
		}
		int sortType = 0;
		do {
			do {
				cout << "\nSort Options >> 0: Start Date, 1: Patient NRIC, 2: Patient Name, 3: Doctor ID, 4: Doctor Name, 9: Return\n";
				cout << "Select sort option [9]:";
				getline(cin, input);
				success = input.empty() || regex_match(input, regex("^[0-9]+$"));
				if (success) {
					sortType = (input.empty() ? 9 : stoi(input));
					continue;
					cout << "Error: Invalid input, please try again.\n\n";
				}
			} while (!success);
			validInt = ((sortType >= 0 && sortType <= 4 ) || sortType == 9);
			
			if (validInt)
				continue;
			cout << "Error: Input out of range, please try again.\n\n";
		} while (!validInt);

		if (sortType == 9) break; 
 
		headNodePointer = sortEntry(headNodePointer, sortType);
	}
	// Return to default sort.
	headNodePointer = sortEntry(headNodePointer, 0);
}