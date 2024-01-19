#include "Appointment.hpp"

void Appointment::add() {

	// To add: Verify inputs + activate time slot checker

	std::cout << "Input date: ";
	string date;
	getline(cin, date);
	std::cout << "Input start time: ";
	string startTime;
	getline(cin, startTime);
	std::cout << "Input end time: ";
	string endTime;
	getline(cin, endTime);

	// checkConflict(date, startTime, endTime);
	// check time conflict here before continuing

	std::cout << "Input Doctor ID: ";
	string doctorID;
	getline(cin, doctorID);
	std::cout << "Input Doctor Name: ";
	string doctorName;
	getline(cin, doctorName);
	std::cout << "Input Patient ID: ";
	string patientID;
	getline(cin, patientID);
	std::cout << "Input Patient Name: ";
	string patientName;
	getline(cin, patientName);
	std::cout << "Input Description: ";
	string description;
	getline(cin, description);

	AppointmentEntry* newAppointment = new AppointmentEntry(date, startTime, endTime, patientID, patientName, doctorID, doctorName, description);
	numberOfAppointments++;

	appointments.push_back(*newAppointment);
	
	cout << "Appointment added successfully.\n" << 
			"Press any key to continue.";
	cin.ignore();

}
