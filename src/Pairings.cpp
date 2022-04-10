#include "Pairings.h"
#define NPOS -1


Pairings::~Pairings() {
	delete[] eventList;
}




void Pairings::assignFromCSV() {

	for (int i = 0; i < numEvents; i++) {
		std::string* buffer = getRowData(i);
		eventList[i].setName(buffer[0]);
		eventList[i].setHours(std::stoi(buffer[1]));
		if (isTeacher(buffer, 2)) {
			
		}
	}
}

void Pairings::initEventList() {
	eventList = new Event[getRowCount()];
}
void Pairings::initEventList(int x) {
	eventList = new Event[x];
}
int Pairings::isTeacher(std::string* cell, int index) {
	if (cell[index].find_first_not_of("0123456789") == NPOS) {


		if (cell[index + 1].find_first_not_of("0123456789") == NPOS) {
			return 1;
		}
		else return 2;
	}
	else return 0;
}
