#include "Appointment.hpp"

enum class SortType {
    StartTime,
    PatientID,
    PatientName,
    DoctorID,
    DoctorName
};

bool compare(AppointmentEntry a, AppointmentEntry b, SortType sortType) {
    switch (sortType) {
    case SortType::StartTime:
        return a.startTime.getTime() < b.startTime.getTime();
    case SortType::PatientID:
        return a.patientID == b.patientID ? a.startTime.getTime() < b.startTime.getTime() 
            : a.patientID < b.patientID;
    case SortType::PatientName:
        return a.patientID == b.patientID ? a.startTime.getTime() < b.startTime.getTime()
            : a.patientName < b.patientName;
    case SortType::DoctorID:
        return a.patientID == b.patientID ? a.startTime.getTime() < b.startTime.getTime()
            : a.doctorID < b.doctorID;
    case SortType::DoctorName:
        return a.patientID == b.patientID ? a.startTime.getTime() < b.startTime.getTime()
            : a.doctorName < b.doctorName;
    default:
        // Handle invalid sortType
        throw invalid_argument("Invalid sortType");
    }
};

Appointment::AppointmentNode* Appointment::sortEntry(AppointmentNode* head, int sortType) {
    if (head == nullptr || head->nextNode == nullptr) {
        return head; // Already sorted if the list is empty or has only one element
    }

    AppointmentNode* sorted = nullptr; // Head of the sorted list

    while (head != nullptr) {
        AppointmentNode* current = head; // Take the current node from the unsorted list
        head = head->nextNode;    // Move to the next unsorted node

        if (sorted == nullptr || compare(current->appointmentEntry, sorted->appointmentEntry, (SortType) sortType)) {
            // If the current node is smaller than the head of the sorted list
            current->nextNode = sorted;
            sorted = current; // Update the head of the sorted list
        }
        else {
            // Traverse the sorted list to find the appropriate position for the current node
            AppointmentNode* temp = sorted;
            while (temp->nextNode != nullptr && compare(temp->nextNode->appointmentEntry, current->appointmentEntry, (SortType) sortType)) {
                temp = temp->nextNode;
            }
            current->nextNode = temp->nextNode;
            temp->nextNode = current;
        }
    }

    return sorted;
};
