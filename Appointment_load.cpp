#include "Appointment.hpp"

void Appointment::load(AppointmentNode*& head) {

    ifstream inputFile(SAVE_FILE_DIRECTORY);
    if (!inputFile.is_open()) {
        std::cerr << "Unable to open the file for reading." << std::endl;
    }

    string line;
    try {
        while (getline(inputFile, line)) {
            istringstream iss(line);
            string startTimeString, endTimeString, patientID, patientName, doctorID, doctorName, description;
            
            DateTime startTime, endTime;

            // Ensure all required fields are successfully read
            if (!(getline(iss, startTimeString, ',') &&
                getline(iss, endTimeString, ',') &&
                getline(iss, patientID, ',') &&
                getline(iss, patientName, ',') &&
                getline(iss, doctorID, ',') &&
                getline(iss, doctorName, ',') &&
                getline(iss, description, ','))) {
                throw runtime_error("Error parsing line: " + line);
            }
            if (!(startTime.setTime(startTimeString) && endTime.setTime(endTimeString)))
                throw runtime_error("Invalid time(s).");

            // Create an AppointmentEntry object and add it to the linked list
            AppointmentNode* newNode = new AppointmentNode;
            newNode->appointmentEntry = AppointmentEntry(startTime, endTime, patientID, patientName, stoi(doctorID), doctorName, description);
            newNode->nextNode = NULL;

            if (head == NULL) {
                // If the list is empty, set the newEntry as the head
                head = newNode;
            }
            else {
                AppointmentNode* currentNode = head;
                // Otherwise, traverse to the end of the list and append the newEntry
                while (currentNode->nextNode != NULL) {
                    currentNode = currentNode->nextNode;
                }
                currentNode->nextNode = newNode;
            }

            numberOfAppointments++;
        }
    }
    catch (const exception& e) {
        cout << "Error reading from the file: " << e.what() << std::endl;
    }

    inputFile.close();

    // Perform sorting after loading.
    head = sortEntry(head);
    save();
}