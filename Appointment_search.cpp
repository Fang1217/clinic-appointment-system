#include "Appointment.hpp"
using namespace std;

string toupper(string input) {
	for (auto& c : input) c = toupper(c);
	return input;
}

void Appointment::search() {
	vector<int> resultIndexArray;
	search(resultIndexArray);

	cout << "Press Enter to continue.";
	cin.ignore();
}

void Appointment::search(vector<int>& resultIndexArray) {

	// Check if there are no appointment entries.
	if (numberOfAppointments <= 0) {
		cout << "There are no entries in the appointment system.\n"
			<< "Press Enter to continue.";
		cin.ignore();
		return;
	}

	// Get search string and type from user.
	string input;
	int searchType = 0;
	string searchTerm;
	bool success;
	bool validInt;
	do {
		do {
			cout << "Search type (0 - Start Date, 1 - Patient, 2 - Doctor) [0]: ";
			getline(cin, input);
			success = input.empty() || regex_match(input, regex("^[0-9]+$"));
			if (success) {
				searchType = (input.empty() ? 0 : stoi(input));
				continue;
			}
			cout << "Error: Invalid input, please try again.\n\n";
		} while (!success);
		validInt = (searchType >= 0 && searchType <= 2);
		if (validInt)
			continue;
		cout << "Error: Input out of range, please try again.\n\n";
	} while (!validInt);

	DateTime date = DateTime();
	string today = date.displayDate();
	do {
		cout << ((searchType == 0) ? "Input start date (YYYY/MM/DD) [" + today + "]: " : "Input search term: ");
		getline(cin, input);
		success = ((searchType == 0) ? (input.empty() || DateTime().setTime(input, true)) : !input.empty());
		if (success) {
			searchTerm = ((searchType == 0 && input.empty()) ? today : input);
			continue;
		}
		cout << "Error: Invalid search string, please try again.\n\n";
	} while (!success);

	// Search 
	Queue resultQueue = Queue();

	AppointmentNode* currentNodePointer = headNodePointer;

	// Queue every matching results
	for (int i = 0; i < numberOfAppointments; i++) {
		AppointmentEntry appointmentEntry = currentNodePointer->appointmentEntry;
		switch (searchType) {
		case 0: // date
			if (appointmentEntry.startTime.displayDate() == searchTerm)
				resultQueue.enqueue(i);
			break;
		case 1: // patient ID/name
			if (appointmentEntry.patientID == searchTerm || (toupper(appointmentEntry.patientName) == toupper(searchTerm))) {
				resultQueue.enqueue(i);
			}
			break;
		case 2: // doctor ID/name
			if (to_string(appointmentEntry.doctorID) == searchTerm || (toupper(appointmentEntry.doctorName) == toupper(searchTerm))) {
				resultQueue.enqueue(i);
			}
			break;
		}
		currentNodePointer = currentNodePointer->nextNode;
	}
	
	//Display each matching entries.
	if (resultQueue.isEmpty()) {
		cout << "No results found\n";
		return;
	}
	else {
		while (!resultQueue.isEmpty()) {
				resultIndexArray.push_back(resultQueue.getFrontAndPop());
		}
	}

	int numberOfResults = resultIndexArray.size();
	// else, found >= 1

	//// Display the table, the length of each column is based on the longest content.
	cout << "Found " << numberOfResults << " " << (numberOfResults > 1 ? "entries" : "entry") << ": \n\n";

		// Find the maximum width of each column
		size_t maxColumnWidths[] = { 3, 14, 10, 10, 12 }; // Initial column widths"
		currentNodePointer = headNodePointer;
		for (int i = 0; i < numberOfResults; i++) {
			AppointmentNode* an = getAppointmentNode(resultIndexArray[i]);
			AppointmentEntry ae = an->appointmentEntry;

			maxColumnWidths[0] = max(maxColumnWidths[0], to_string(resultIndexArray[i] + 1).size());
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
		for (int i = 0; i < numberOfResults; i++) {
		AppointmentNode* an = getAppointmentNode(resultIndexArray[i]);
		AppointmentEntry ae = an->appointmentEntry;
		cout << setw(maxColumnWidths[0]) << right << (i + 1) << " | "
				<< setw(maxColumnWidths[1]) << left << ae.startTime.displayTime("%Y/%m/%d %H:%M") + " - " + ae.endTime.displayTime("%H:%M") << " | "
				<< setw(maxColumnWidths[2]) << ae.patientID + ": " + ae.patientName << " | "
				<< setw(maxColumnWidths[3]) << to_string(ae.doctorID) + ": " + ae.doctorName << " | "
				<< setw(maxColumnWidths[4]) << ae.description << " | "
				<< endl;
				}

};


