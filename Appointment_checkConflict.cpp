#include "Appointment.hpp"

bool Appointment::checkConflict(DateTime newStartTime, DateTime newEndTime) {

	//Checks all in the appointment list for time conflicts.
	AppointmentNode* currentNodePointer = headNodePointer;
	for (int i = 0; i < numberOfAppointments; i++) {
		AppointmentEntry appointmentEntry = currentNodePointer->appointmentEntry;

		// Time conflicts when:
		// 1. Start time is in the duration, or
		// 2. End time is in the duration, or
		// 3. Duration of time is in between the duration.
		//

		bool timeConflict = ((newStartTime.getTime() >= appointmentEntry.startTime.getTime() &&
			newStartTime.getTime() < appointmentEntry.endTime.getTime()) ||

			(newEndTime.getTime() > appointmentEntry.startTime.getTime() &&
			newEndTime.getTime() < appointmentEntry.endTime.getTime()) ||

			(newStartTime.getTime() <= appointmentEntry.startTime.getTime() && 
				newEndTime.getTime() >= appointmentEntry.endTime.getTime())
			);

		if (timeConflict) {
			cout << "\nThe following is conflicting with the specified time below, please try again.\n\n";

			cout << "Appointment Date & Time: "
				<< appointmentEntry.startTime.displayDate("%Y/%m/%d %H:%M") << " - "
				<< appointmentEntry.endTime.displayTime("%H:%M") << "\n";
			cout << "Patient ID & Name: "
				<< appointmentEntry.patientID << " - "
				<< appointmentEntry.patientName << "\n";
			cout << "Doctor ID & Name: "s
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
	