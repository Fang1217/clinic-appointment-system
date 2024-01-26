#include "Appointment.hpp"
using namespace std;

void Appointment::remove() {
	vector<int> resultIndexArray;
	search(resultIndexArray);

	string input;
	bool validInt;
	bool validIndex;

	int numberOfResults = resultIndexArray.size();

	switch (numberOfResults)
	{
	case 0: 
		return;

	case 1:
		cout << "Remove this entry? [y/N]";
		getline(cin, input);
		if (toupper(input[0]) == 'Y') {
			int index = resultIndexArray[0];
			removeAppointmentNode(index);
		}
		else return;
		break;
	default:
		do {
			do {
				cout << "Select which entry to remove.\n";
				getline(cin, input);
				validInt = regex_match(input, regex("^[0-9]+$"));
				if (validInt)
					continue;
			} while (!validInt);

			int position = stoi(input) - 1;
			validIndex = (position >= 0 && position < numberOfResults);
			if (validIndex) {
				int indexToRemove = resultIndexArray[position];
				removeAppointmentNode(indexToRemove);
				continue;
			}
		} while (!validIndex);
		break;
	}

	save();

	cout << "Entry removed successfully.";
	cin.ignore();
};