#include "Pairings.h"
#define NPOS -1
enum {
	NON_ATTENDANT = 0,
	INSTRUCTOR = 1,
	CLASS_STREAM = 2,
};

Pairings::Pairings() {
	numEvents = 0;
	std::cout << "EVENT LIST UNINITIALIZED" << std::endl;
}
Pairings::Pairings(CSV& file) {
	assignFromCSV(file);
}
Pairings::~Pairings() {
	delete[] eventList;
}

void Pairings::assignFromCSV(CSV& file) {
	initEventList(file.getRowCount());
	
	for (int i = 0; i < file.getRowCount(); i++) {
		std::string* buffer = file.getRowData(i);
		eventList[i].setName(buffer[0]);
		eventList[i].setHours(std::stoi(buffer[1]));
		eventList[i].setRoomReq(RoomType::LECTURE_HALL);
		for (int k = 3; k < file.getColCount(); k++)
		{
			switch (isTeacher(buffer, k)) {
			case 0:
				break;
			case 1:
				eventList[i].appendAttendant(buffer[k], 0);
				break;
			case 2:
				eventList[i].appendAttendant(buffer[k], stoi(buffer[k + 1]));
				k++;
			}
		}
	}


}

int Pairings::isTeacher(std::string buffer[], int index) {
	size_t found = buffer[index].find_first_not_of("0123456789");
	if (found != std::string::npos) {
		if (buffer[index + 1].find_first_not_of("0123456789") != std::string::npos) {
			return 1;
		}
		else return 2;
	}
	else return 0;
}


void Pairings::initEventList(int x) {
	numEvents = x;
	eventList = new Event[numEvents];
}
void Pairings::printEvents(){
	for (int i = 0; i < numEvents; i++) {
		std::cout << i + 1 << ". ";
		std::cout << eventList[i].getName() << " | ";
		std::cout << eventList[i].getHours() << " | ";
		std::cout << eventList[i].getCurrentAttCount() << " | ";
		std::cout << eventList[i].getAttendantNamesStr() << " | ";
		std::cout << roomTypeToString(eventList[i].getRoomReq());
		std::cout << " | ";
		std::cout << std::endl;
	}
}


void Pairings::editor() {
	clearEx(3);
	int originX = 0;
	int originY = 3;
	printEvents();
	
	setCursX(originX);
	setCursY(originY);
	

}