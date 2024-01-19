#include "Appointment.hpp"

void Appointment::display() {

	if (numberOfAppointments <= 0) {
		cout << "nothing to display\n";
		cin.ignore();
		return;
	}

	std::cout << "Input how many entries to display (Default: 10): ";
	string input;
	getline(cin, input);
	int head = stoi(input);

	// display 'head' number of entries.
	for (int i = 0; i < min(numberOfAppointments, head); i++) {
		cout << appointments[i].date << " | "
			 << appointments[i].startTime << " | "
			 << appointments[i].endTime << " | "
			 << appointments[i].patientID << " | "
			 << appointments[i].patientName << " | "
			 << appointments[i].doctorID << " | "
			 << appointments[i].doctorName << " | "
			 << appointments[i].description << " | "
			 << "\n";
	}
	cout << "\nPress Enter to continue.\n\n";
	cin.ignore();
};

// Display the calendar view of specific month, where entries of the currently active appointments will be displayed.
//void display(int month, int year) 