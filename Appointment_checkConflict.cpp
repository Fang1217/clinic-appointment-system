#include "Appointment.hpp"

bool Appointment::checkConflict(DateTime newStartTime, DateTime newEndTime) {

	//Checks all in the appointment list for time conflicts.
	AppointmentNode* currentNodePointer = headNodePointer;
	for (int i = 0; i < numberOfAppointments; i++) {
		AppointmentEntry appointmentEntry = currentNodePointer->appointmentEntry;

		bool timeConflict = (newStartTime.getTime() > appointmentEntry.startTime.getTime() &&
			newStartTime.getTime() < appointmentEntry.endTime.getTime());

		if (timeConflict) {
			cout << "The following is conflicting with the specified time below, please try again.\n";
			cout << appointmentEntry.startTime.displayDate("%Y/%m/%d %H:%M") << " | "
				<< appointmentEntry.endTime.displayTime("%H:%M") << " | "
				<< appointmentEntry.patientID << "\t | "
				<< appointmentEntry.patientName << "\t | "
				<< appointmentEntry.doctorID << "\t | "
				<< appointmentEntry.doctorName << "\t | "
				<< appointmentEntry.description << "\t | "
				<< "\n";

			return false;
		}

		currentNodePointer = currentNodePointer->nextNode;
	}
	return true;
};
	