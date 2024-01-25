#include "Appointment.hpp"

bool Appointment::checkConflict(DateTime newStartTime, DateTime newEndTime) {

	//Checks all in the appointment list for time conflicts.
	AppointmentNode* currentNodePointer = headNodePointer;
	for (int i = 0; i < numberOfAppointments; i++) {
		AppointmentEntry appointmentEntry = currentNodePointer->appointmentEntry;

		bool timeConflict = (newStartTime.getTime() > appointmentEntry.startTime.getTime() &&
			newStartTime.getTime() < appointmentEntry.endTime.getTime());

		if (timeConflict) {
			cout << "The following is conflicting with the specified time below, please try again.\n\n";

			cout << "Appointment Date & Time: "
				<< appointmentEntry.startTime.displayDate("%Y/%m/%d %H:%M") << " - "
				<< appointmentEntry.endTime.displayTime("%H:%M") << "\n";
			cout << "Patient ID & Name: "
				<< appointmentEntry.patientID << " - "
				<< appointmentEntry.patientName << "\n";
			cout << "Doctor ID & Name: "
				<< appointmentEntry.doctorID << " - "
				<< appointmentEntry.doctorName << "\n";
			cout << "Description: "
				<< appointmentEntry.description << "\n\n";

			return false;
		}
		currentNodePointer = currentNodePointer->nextNode;
	}
	return true;
};
	