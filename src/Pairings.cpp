#include "Pairings.h"



Pairings::~Pairings() {
	delete[] eventList;
}




void Pairings::assignFromCSV() {

	for (int i = 0; i < numEvents; i++) {
		std::string* buffer = getRowData(i);
		eventList[i].setName(buffer[NAME]);
		eventList[i].setHours(std::stoi(buffer[HOURS]));
	}

	
}