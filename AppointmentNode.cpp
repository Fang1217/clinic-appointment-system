#include "Appointment.hpp"

Appointment::AppointmentNode* Appointment::getAppointmentNode(int index) {
	AppointmentNode* currentNodePointer = headNodePointer;
	for (int j = 0; j < index; j++) {
		if (currentNodePointer->nextNode == NULL)
			return NULL;
		currentNodePointer = currentNodePointer->nextNode;
	}
	return currentNodePointer;
}

void Appointment::addAppointmentMode(AppointmentEntry appointmentEntry) {
	// Append new node into the linked-list.
	AppointmentNode* newAppointmentNode = new AppointmentNode;
	newAppointmentNode->appointmentEntry = appointmentEntry;
	newAppointmentNode->nextNode = NULL;

	if (headNodePointer == NULL) {
		headNodePointer = newAppointmentNode;
	}
	else {
		// Traverse to the last node
		AppointmentNode* currentNodePointer = headNodePointer;
		while (currentNodePointer->nextNode != NULL)
		{
			currentNodePointer = currentNodePointer->nextNode;
		}
		currentNodePointer->nextNode = newAppointmentNode;
	}
	numberOfAppointments++;
}

void Appointment::removeAppointmentNode(int index) {
	AppointmentNode* appointmentNode = getAppointmentNode(index);
	if (appointmentNode == NULL) {
		cout << "Error on remove node";
		return;
	}
	AppointmentNode* temp = appointmentNode;
	if (appointmentNode == headNodePointer) {
		headNodePointer = appointmentNode->nextNode;
	}
	else {
		// Update currentNodePointer only if not the head
		appointmentNode = headNodePointer;
	}
	delete temp;
	temp = NULL;
	
	numberOfAppointments--;
}