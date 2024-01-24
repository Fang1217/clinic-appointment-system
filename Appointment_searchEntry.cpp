#include "Appointment.hpp"
#include "Queue.hpp"


Queue Appointment::searchEntry(const string searchTerm, const int searchType) {

	Queue searchQueue = Queue();

	AppointmentNode* currentNodePointer = headNodePointer;

	for (int i = 0; i < numberOfAppointments; i++) {
		AppointmentEntry appointmentEntry = currentNodePointer->appointmentEntry;

		switch (searchType) {
		case 0: // date
			if (appointmentEntry.startTime.displayDate() == searchTerm)
				searchQueue.enqueue(i);
			break;
		case 1: // patient ID/name
			if (appointmentEntry.patientID == searchTerm || appointmentEntry.patientName == searchTerm)
				searchQueue.enqueue(i);
			break;
		case 2: // doctor ID/name
			if (to_string(appointmentEntry.doctorID) == searchTerm || appointmentEntry.doctorName == searchTerm)
				searchQueue.enqueue(i);
			break;
		}

		currentNodePointer = currentNodePointer->nextNode;
	}

	return searchQueue;

};