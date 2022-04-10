#pragma once
#include "CSV.h"
#include "Event.h"


class Pairings : public CSV {
private:
	Event* eventList;
	int numEvents;

public:
	Pairings(std::string fileExt) : CSV(fileExt) {
		importCsv();
		eventList = new Event[getRowCount()];
		numEvents = (getRowCount());
	}
	~Pairings();

	void assignEvents();
	

};