#pragma once
#ifndef AppointmentEntry_HPP
#define AppointmentEntry_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

typedef std::string DateTime; //instead of ct,. for now.

using namespace std;


class AppointmentEntry
{

public:
	DateTime date;
	DateTime startTime;
	DateTime endTime;
	string patientID;
	string patientName;
	string doctorID;
	string doctorName;
	string description;

	AppointmentEntry();

	// Constructor. Creates an appointment entry.
	AppointmentEntry 
		(DateTime date, DateTime startTime, DateTime endTime, string patientID, string patientName, string doctorID, string doctorName, string description);

	vector<string> getEntry();
};

#endif