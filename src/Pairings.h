#pragma once
#include "CSV.h"
#include "Event.h"


class Pairings : public CSV {
private:
	Event* eventList;

public:
	Pairings(std::string fileExt) : CSV(fileExt) {
		importCsv();
		eventList = new Event[getRowCount()];
	}
	~Pairings();

	void assignEvents();


};