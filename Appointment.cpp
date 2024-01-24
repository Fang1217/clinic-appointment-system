#include "Appointment.hpp"

using namespace std;

// Constructor. Attempt to load an existing save file. 
Appointment::Appointment() {
	load(headNodePointer);
};

// Destructor. Deletes the appointment system object.
Appointment::~Appointment() {};