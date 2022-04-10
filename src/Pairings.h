#pragma once
#include "CSV.h"
#include "Event.h"
enum {
	NAME,
	HOURS,
	CLASSTYPE,
	TEACHER
};

class Pairings : public CSV {
private:
	Event* eventList;
	int numEvents;

public:
	Pairings();
	Pairings(std::string fileExt) : CSV(fileExt) {
		importCSV();
		
	}
	~Pairings();

	void initEventList();
	void assignFromCSV();
	

};