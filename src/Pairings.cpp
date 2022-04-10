#include "Pairings.h"
#define NPOS -1
enum {
	NON_ATTENDANT,
	INSTRUCTOR,
	CLASS_STREAM
};

Pairings::Pairings(int xNumEvents) {
	numEvents = xNumEvents;
	eventList = new Event[numEvents];
}
Pairings::~Pairings() {
	delete[] eventList;
}

void Pairings::assignFromCSV() {
	initEventList(getRowCount());

	for (int i = 0; i < numEvents; i++) {
		std::string* buffer = getRowData(i);
		eventList[i].setName(buffer[0]);
		eventList[i].setHours(std::stoi(buffer[1]));
		
	}
}
void Pairings::assignAttendants(string* buffer) {
	for (int i = 2; i < getColCount(); i++)
	{
		switch (isTeacher(buffer, i)) {
		case NON_ATTENDANT:
			break;
		case INSTRUCTOR:
			eventList[i].appendAttendant(buffer[i], 0);
			break;
		case CLASS_STREAM:
			eventList[i].appendAttendant(buffer[i], stoi(buffer[i + 1]);
		}
	}
}

void Pairings::initEventList() {
	eventList = new Event[getRowCount()];
}
void Pairings::initEventList(const int x) {
	int numEvents = x;
	eventList = new Event[numEvents];
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
