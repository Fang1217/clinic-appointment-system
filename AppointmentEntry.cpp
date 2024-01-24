#include "AppointmentEntry.hpp"

using namespace std;

AppointmentEntry::AppointmentEntry() {
};

AppointmentEntry::AppointmentEntry(const AppointmentEntry& ae) {
	this->startTime = ae.startTime;
	this->endTime = ae.endTime;
	this->patientID = ae.patientID;
	this->patientName = ae.patientName;
	this->doctorID = ae.doctorID;
	this->doctorName = ae.doctorName;
	this->description = ae.description;
};


// Constructor. Creates an appointment entry.
AppointmentEntry::AppointmentEntry
	(DateTime startTime, DateTime endTime, string patientID, string patientName, int doctorID, std::string doctorName, string description) {
	this->startTime = DateTime(startTime);
	this->endTime = DateTime(endTime);
	this->patientID = patientID;
	this->patientName = patientName;
	this->doctorID = doctorID;
	this->doctorName = doctorName;
	this->description = description;
};

