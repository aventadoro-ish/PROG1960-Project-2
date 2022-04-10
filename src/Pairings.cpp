#include "Pairings.h"



Pairings::~Pairings() {
	delete[] eventList;
}


void Pairings::assignEvents() {

	for (int i = 0; i < numEvents; i++) {
		std::string* buffer = getRowData(i);
		eventList[i].setName(buffer[0]);
		eventList[i].setHours(std::stoi(buffer[1]));
	}

	
}