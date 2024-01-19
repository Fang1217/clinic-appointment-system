#pragma once
#ifndef Appointment_HPP
#define Appointment_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector> // Temporary sub for vector rather than linked based implementations
#include "AppointmentEntry.hpp"

using namespace std;

class Appointment
{
public:
	int numberOfAppointments = 0;
	//AppointmentEntry appointment;
	//AppointmentEntry* next;
	// pointer based 
	std::vector<AppointmentEntry> appointments;

	// Constructor. Creates an appointment system object that contains no data.
	Appointment();

	// Constructor. Creates an appointment system object with data that is loaded from infile file.
	Appointment(std::ifstream& infile);

	// Destructor. Deletes the appointment system object.
	~Appointment();

	// INPUT VARIABLES HERE

	// Display the first n entries of the currently active appointments, sorted by date. 
	// Where the default n is optional parameter head which is 10 by default.
	void display(int head = 10);

	// Display the calendar view of specific month, where entries of the currently active appointments will be displayed.
	//void display(int month, int year);

	// Add new appointment data into the system.
	void addEntry(string& response);

	// Delete data from the system.
	void deleteEntry(std::string searchTerm, int searchType);

	// Display data in the system, based on search string and type.
	void displayEntry(std::string searchTerm, int searchType);


private:
	// Returns an array of IDs of the result from searching using searchTerm, of type searchType, which then be processed by the public functions.
	int* search(std::string searchTerm, int searchType);

	// Returns an array of IDs of the result from after sorting by sortType, which then be processed by the public functions.
	int* sortEntry(const int data[], int sortType);

	// Returns true when there is no conflict when adding a new schedule.
	bool checkConflict();
};

#endif