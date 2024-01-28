#include "Appointment.hpp"

Appointment::AppointmentNode* Appointment::getAppointmentNode(int index) {
	if (index >= numberOfAppointments)
		return NULL;
	AppointmentNode* currentNodePointer = headNodePointer;
	for (int j = 0; j < index; j++) {
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
	sortEntry(headNodePointer);
	numberOfAppointments++;
}

void Appointment::removeAppointmentNode(int index) {
	AppointmentNode* previousNode = getAppointmentNode(index - 1);
	AppointmentNode* currentNode = getAppointmentNode(index);

	if (currentNode == NULL) {
		cout << "Error on remove node";
		return;
	}
	if (currentNode == headNodePointer) {
		headNodePointer = currentNode->nextNode;
	}
	else {
		AppointmentNode* temp = currentNode;
		previousNode->nextNode = currentNode->nextNode;
		temp->nextNode = NULL;
		delete temp;
		temp = NULL;
	}
	
	numberOfAppointments--;
}