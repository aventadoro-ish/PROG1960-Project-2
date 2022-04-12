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
	for (int i = 0; i < MAX_EVENTS; i++) {
		eventList[i] = NULL;
	}
	//std::cout << "EVENT LIST UNINITIALIZED" << std::endl;
}
Pairings::Pairings(CSV& file) {
	assignFromCSV(file);
}

Pairings::~Pairings() {
	for (int i = 0; i < getNEvents()-1; i++) {
		std::cout << "pair destorys !event " << eventList[i]->getName() <<std::endl;
		delete eventList[i];
	}
}

void Pairings::assignFromCSV(CSV& file) {
	initEventList(file.getRowCount());
	
	for (int i = 0; i < file.getRowCount(); i++) {
		std::string* buffer = file.getRowData(i);
		std::cout << buffer[0] << "; " << buffer[1] << "; " << buffer[2] << "; " << buffer[3] << "\n";

		eventList[i]->setName(buffer[0]);
		eventList[i]->setHours(std::stoi(buffer[1]));
		eventList[i]->setRoomReq(RoomType::LECTURE_HALL); // TODO: lecture_hall


		for (int k = 3; k < file.getColCount()-1; k++) {
			if (k == file.getColCount()) { // quick and dirty fix
				//std::cout << "Hopefully is a teacher: " << buffer[k] << std::endl;
				eventList[i]->appendAttendant(buffer[k], 0);
				continue;
			}
			switch (isTeacher(buffer, k)) {
			case 0:
				break;
			case 1:
				eventList[i]->appendAttendant(buffer[k], 0);
				break;
			case 2:
				eventList[i]->appendAttendant(buffer[k], stoi(buffer[k + 1]));
				k++;
			}
		}
	}
}

int Pairings::isTeacher(std::string buffer[], int index) {
	size_t found = buffer[index].find_first_not_of("0123456789");
	if (found != NPOS) {
		//std::cout << "*" << buffer[index] << "\n";
		if (buffer[index + 1].find_first_not_of("0123456789") != NPOS) {
			return 1;
		}
		else return 2;
	}
	else return 0;
}


void Pairings::initEventList(int x) {
	numEvents = x;
	for (int i = 0; i < numEvents; i++) {
		eventList[i] = new Event();
	}
	//eventList = new Event*[numEvents];
}
void Pairings::printEvent(int index){
	if (index == ALL) {
		for (int i = 0; i < numEvents; i++) {
			std::cout << i + 1 << ". ";
			std::cout << eventList[i]->getName() << " | ";
			std::cout << eventList[i]->getHours() << " | ";
			std::cout << roomTypeToString(eventList[i]->getRoomReq());


			///DELETE CURRENT ATT COUNT -- IT WILL BE ASSOCIATED WITH ATTENDANTS
			std::cout << eventList[i]->getCurrentAttCount() << " | ";
			//ONLY TO BE USED FOR TESTING


			std::cout << eventList[i]->getAttendantNamesStr() << " | ";
			std::cout << " | ";
			std::cout << std::endl;
			
		}
	}
	else {
		std::cout << "1. Name:                   ";
		std::cout << eventList[index]->getName() << "\n";
		std::cout << "2. Hours per week:         ";
		std::cout << eventList[index]->getHours() << "\n";
		std::cout << "3. Room Type Required:     ";
		std::cout << roomTypeToString(eventList[index]->getRoomReq()) << "\n";
		std::cout << "4. Current Attendees:      ";
		std::cout << eventList[index]->getAttendantNamesStr() << "\n";
		std::cout << std::endl;
	}
}



bool Pairings::editor() {
	clearEx(3);
	printEvent(ALL);
	std::cout << "\n5. Return to Main Menu";
	int i;
	std::cout << "\n\nPlease select an event to edit:\n";
	std::cin >> i;
	i--;
	std::string buffer;
	clearEx(OFFSET);
	std::cout << "Please select a field to edit:\n";
	printEvent(i);
	int menuSel;
	std::cin >> menuSel;
	switch (i) {
	case 1:
		std::cout << "Current Name:\n";
		std::cout << eventList[i]->getName() << "\n\n";
		std::cout << "Please enter a new name: ";
		std::cin >> buffer;
		eventList[i]->setName(buffer);
		clearEx(OFFSET);
		return true;
	case 2:
		std::cout << "Current hours per week:\n";
		std::cout << eventList[i]->getHours() << "\n\n";
		std::cout << "Please enter a new value: ";
		int hours;
		std::cin >> hours;
		eventList[i]->setHours(hours);
		clearEx(OFFSET);
		std::cout << eventList[i]->getHours();
		return true;
	case 3:
		clearEx(3);
		std::cout << "Current room type required:\n";
		std::cout << roomTypeToString(eventList[i]->getRoomReq());
		std::cout << "\n\nPlease select a new room type:\n1. Lecture Hall\n2. Tech Lab\n3. Computer Lab\n4. Sports Hall";
		std::cin >> menuSel;
		eventList[i]->setRoomReq(intToRoomType(menuSel));
		//std::cout << roomTypeToString(eventList[i]->getRoomReq());
		return true;
	case 4:
		std::cout << "IMPLEMENTAION FAILED";
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
	case 5:
		return false;
	default:
		return true;
	}
}
