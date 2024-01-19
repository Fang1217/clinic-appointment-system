#pragma once
#ifndef AppointmentEntry_HPP
#define AppointmentEntry_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

// To do in the future: Safe coding management
class AppointmentEntry
{

public:
	// static int numberOfAppointments;
	//std::tm date;
	string date;
	string startTime;
	string endTime;
	string patientID;
	string patientName;
	string doctorID;
	string doctorName;
	string description;

	AppointmentEntry();

	// Constructor. Creates an appointment entry.
	AppointmentEntry 
		(string date, string startTime, string endTime, string patientID, string patientName, string doctorID, string doctorName, string description);
};

#endif