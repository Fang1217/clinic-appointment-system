#include "Appointment.hpp"

vector<int> Appointment::searchEntry(const string searchTerm, const int searchType) {

	vector<int> positionArray;

	for (int i = 0; i < appointments.size(); i++) {
		switch (searchType) {
		case 0: // date
			if (appointments[i].date == searchTerm)
				positionArray.push_back(i);
			break;
		case 1: // patient ID/name
			if (appointments[i].patientID == searchTerm || appointments[i].patientName == searchTerm)
				positionArray.push_back(i);
			break;
		case 2: // doctor ID/name
			if (appointments[i].doctorID == searchTerm || appointments[i].doctorName == searchTerm)
				positionArray.push_back(i);
			break;
		}
	}

	return positionArray;

};