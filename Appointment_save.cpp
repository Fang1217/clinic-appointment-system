#include "Appointment.hpp"

void Appointment::save() {
    std::ofstream outputFile(SAVE_FILE_DIRECTORY);

    if (!outputFile.is_open() || numberOfAppointments == 0) {
        std::cerr << "Unable to save appointments. File not open or no appointments to save." << std::endl;
        return;
    }

	Appointment::AppointmentNode* currentNodePointer = headNodePointer;
    while (currentNodePointer != nullptr) {
		AppointmentEntry appointmentEntry = currentNodePointer->appointmentEntry;

		outputFile << appointmentEntry.startTime.displayTime() << ","
			<< appointmentEntry.endTime.displayTime() << ","
			<< appointmentEntry.patientID << ","
			<< appointmentEntry.patientName << ","
			<< appointmentEntry.doctorID << ","
			<< appointmentEntry.doctorName << ","
			<< appointmentEntry.description << "\n";

		currentNodePointer = currentNodePointer->nextNode;
    }

    outputFile.close();
};