#include "AppointmentEntry.hpp"

using namespace std;

// To do in the future: Safe coding management
AppointmentEntry::AppointmentEntry() {};

// Constructor. Creates an appointment entry.
AppointmentEntry::AppointmentEntry
	(string date, string startTime, string endTime, string patientID, std::string patientName, string doctorID, std::string doctorName, std::string description) {
	this->date = date;
	this->startTime = startTime;
	this->endTime = endTime;
	this->patientID = patientID;
	this->patientName = patientName;
	this->doctorID = doctorID;
	this->doctorName = doctorName;
	this->description = description;
};