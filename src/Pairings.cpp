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
	for (int i = 0; i < getNEvents(); i++) {
		std::cout << "*";
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
		std::cout << "Name:                   ";
		std::cout << eventList[index]->getName() << "\n";
		std::cout << "Hours per week:         ";
		std::cout << eventList[index]->getHours() << "\n";
		std::cout << "Room Type Required:     ";
		std::cout << roomTypeToString(eventList[index]->getRoomReq()) << "\n";
		std::cout << "Current Attendees:      ";
		std::cout << eventList[index]->getAttendantNamesStr() << "\n";
		std::cout << std::endl;
	}
}



void Pairings::editor(int x) {
	clearEx(OFFSET);
	printEvent(ALL);
	setCursX(0);
	setCursY(OFFSET);
	int i = selectEvent(OFFSET);
	int cmd;
	clearEx(OFFSET);
	switch (getCursY() - OFFSET) {
	case 0:
		std::cout << eventList[i]->getName();
		break;
	case 1:
		std::cout << eventList[i]->getHours();
		break;
	case 2:
		std::cout << roomTypeToString(eventList[i]->getRoomReq());
		cmd = 0;
		while (cmd == 0) {
			cmd = menuKeyParser(_getch());
		}
		if (cmd == 1) {
			eventList[i]->setRoomReq(intToRoomType(getCursY() - OFFSET));
		}
		break;
	case 3:
		std::cout << eventList[i]->getAttendantNamesStr();
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
			//Should this be i?




		}
	}
}