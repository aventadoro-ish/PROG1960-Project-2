#include "Pairings.h"
#define NPOS -1
enum {
	NON_ATTENDANT = 0,
	INSTRUCTOR = 1,
	CLASS_STREAM = 2,
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
		eventList[i].setRoomReq(RoomType::LECTURE_HALL);
		assignAttendants(buffer);
	}
}
void Pairings::assignAttendants(std::string buffer[]) {
	for (int i = 3; i < getColCount(); i++)
	{
		switch (isTeacher(buffer, i)) {
		case 0:
			break;
		case 1:
			eventList[i].appendAttendant(buffer[i], 0);
			break;
		case 2:
			eventList[i].appendAttendant(buffer[i], stoi(buffer[i + 1]));
		}
	}
}

int Pairings::isTeacher(std::string buffer[], int index) {
	size_t found = buffer[index].find_first_not_of("0123456789");
	if (found != std::string::npos) {
		if (buffer[index + 1].find_first_not_of("0123456789") == std::string::npos) {
			return 1;
		}
		else return 2;
	}
	else return 0;
}


void Pairings::printEvents(){
	for (int i = 0; i < numEvents; i++) {
		std::cout << eventList[i].getName() << "\n";
		std::cout << eventList[i].getHours() << "\n";
		std::cout << eventList[i].getCurrentAttCount() << "\n";
		std::cout << eventList[i].getAttendantNamesStr() << "\n";
	}
}