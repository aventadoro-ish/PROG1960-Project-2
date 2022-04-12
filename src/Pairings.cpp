#include "Pairings.h"
#define OFFSET 3

enum {
	NULL_ROOM,
	LECTURE_HALL,
	TECH_LAB,
	COMPUTER_LAB,
	SPORTS_HALL
};
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
	if (found != NPOS) {
		if (buffer[index + 1].find_first_not_of("0123456789") != NPOS) {
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
void Pairings::printEvent(int index){
	if (index == ALL) {
		for (int i = 0; i < numEvents; i++) {
			std::cout << i + 1 << ". ";
			std::cout << eventList[i].getName() << " | ";
			std::cout << eventList[i].getHours() << " | ";
			std::cout << roomTypeToString(eventList[i].getRoomReq());
			std::cout << eventList[i].getAttendantNamesStr() << " | ";
			std::cout << " | ";
			std::cout << std::endl;
			
		}
	}
	else {
		std::cout << "Name:                   ";
		std::cout << eventList[index].getName() << "\n";
		std::cout << "Hours per week:         ";
		std::cout << eventList[index].getHours() << "\n";
		std::cout << "Room Type Required:     ";
		std::cout << roomTypeToString(eventList[index].getRoomReq()) << "\n";
		std::cout << "Current Attendees:      ";
		std::cout << eventList[index].getAttendantNamesStr() << "\n";
		std::cout << std::endl;
	}
}



void Pairings::editor() {
	clearEx(OFFSET);
	printEvent(ALL);
	setCursX(0);
	setCursY(OFFSET);
	int i = selectEvent(OFFSET);
	int cmd;
	std::string buffer;
	clearEx(OFFSET);
	switch (getCursY() - OFFSET) {
	case 0:
		std::cout << "Current Name:\n";
		std::cout << eventList[i].getName() << "\n\n";
		std::cout << "Please enter a new name: ";
		std::cin >> buffer;
		eventList[i].setName(buffer);
		clearEx(OFFSET);
		break;
	case 1:
		std::cout << "Current hours per week:\n";
		std::cout << eventList[i].getHours() << "\n\n";
		std::cout << "Please enter a new value: ";
		int hours;
		std::cin >> hours;
		eventList[i].setHours(hours);
		clearEx(OFFSET);
		std::cout << eventList[i].getHours();
		break;
	case 2:
		std::cout << "Current room type required:\n";
		std::cout << roomTypeToString(eventList[i].getRoomReq());
		std::cout << "\n\nPlease select a new room type:\nLecture Hall\nTech Lab\nComputer Lab\nSports Hall";
		setCursX(0);
		setCursY(7);
		cmd = 0;
		while (cmd == 0) {
			cmd = menuKeyParser(_getch());
		}
		if (cmd == 1) {
			std::cout << getCursY();
			eventList[i].setRoomReq(intToRoomType(getCursY() - 7));
			std::cout << roomTypeToString(eventList[i].getRoomReq());
		}
		break;
	case 3:
		//for (int i = 0; i < eventList[i].getCurrentAttCount(); i++) {
		//	eventList[i].getAttendantNamesStr(i);
		//	std::cout << "\n";
		//}
		//cmd = 0;
		//while (cmd == 0) {
		//	cmd = menuKeyParser(_getch());
		//}
		//if (cmd == 1) {
		//	std::string name;
		//	std::cout << "Please enter a new Name: ";
		//	std::cin >> name;
		//	eventList[i].changeAttendantName(getCursY() - OFFSET, name);
		//}
		break;
	}
}


int Pairings::selectEvent(int offset) {

	int cmd = 0;
	int i = -1;
	while (cmd == 0) {
		cmd = menuKeyParser(_getch());
	}
	clearEx(offset);
	if (cmd == 1) {
		i = getCursY() - offset;
		printEvent(getCursY() - offset);
		setCursX(0);
		setCursY(offset);
		cmd = 0;
		while (cmd == 0) {
			cmd = menuKeyParser(_getch());
		}
		if (cmd == 1) {

			return i;

		}
	}
}