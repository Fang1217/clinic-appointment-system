#include "Appointment.hpp"

using namespace std;

// Constructor. Attempt to load an existing save file. 
Appointment::Appointment() {
	load(headNodePointer);
};

// Constructor. Creates an appointment system object with data that is loaded from infile file.
//Appointment::Appointment(std::ifstream& infile) {};

// Destructor. Deletes the appointment system object.
Appointment::~Appointment() {};