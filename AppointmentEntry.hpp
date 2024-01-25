#pragma once
#ifndef AppointmentEntry_HPP
#define AppointmentEntry_HPP

#include <iostream>
#include <fstream>
#include <string>
#include "DateTime.hpp"

using namespace std;

class AppointmentEntry
{
public:
	DateTime startTime;
	DateTime endTime;
	string patientID;
	string patientName;
	int doctorID;
	string doctorName;
	string description;

	// Default constructor.
	AppointmentEntry();

	// Copy constructor. 
	AppointmentEntry(const AppointmentEntry& ae);

	// Constructor. Creates an appointment entry.
	AppointmentEntry 
		(DateTime startTime, DateTime endTime, string patientID, string patientName, int doctorID, string doctorName, string description);
};

#endif