#pragma once
#ifndef Appointment_HPP
#define Appointment_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <regex>
#include <vector> // Temporary sub for vector rather than linked
#include "AppointmentEntry.hpp"
#include "Queue.hpp"

using namespace std;

class Appointment
{
public:
	const string SAVE_FILE_DIRECTORY = "saveData.txt";

	// Constructor. Loads the appointment system object from the save file.
	Appointment();

	// Destructor. Deletes the appointment system object.
	~Appointment();

	// Display the first n entries of the currently active appointments, sorted by date. 
	// Where the default n is optional parameter head which is 10 by default.
	void display();

	// Display the calendar view of specific month, where entries of the currently active appointments will be displayed.
	void displayCalendar(DateTime& selectedMonth);

	// Add new appointment data into the system.
	void add();

	// Delete the specific entry with specific search term.
	void remove();

	// Display data in the system, based on search string and type.
	void search();

	// Edit data in the system, based on search string and type.
	void edit();

private:

	// Linked-list implementation to store appointment entries data.
	struct AppointmentNode {
		AppointmentEntry appointmentEntry;
		AppointmentNode* nextNode = NULL;
	};

	int numberOfAppointments = 0;
	AppointmentNode* headNodePointer = NULL;

	// Returns a queue containing all result index from searching using searchTerm, of type searchType, 
	// which then be processed by the public functions.
	Queue searchEntry(std::string searchTerm, int searchType);

	// Perform insertion sort and return a sorted list from the pointer, which then be processed by the public functions.
	AppointmentNode* sortEntry(AppointmentNode* head, int sortType = 0);

	// Check all appointment entries for time conflicts. Returns true when there is no conflict when adding a new schedule.
	bool checkConflict(DateTime startTime, DateTime endTime);
	
	// Save on every changes made in the system.
	void load(AppointmentNode*& head);

	// Save on every changes made in the system.
	void save();
};

#endif