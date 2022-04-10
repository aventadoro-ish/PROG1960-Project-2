#pragma once
#include "CSV.h"
#include "Event.h"

class Pairings : private CSV {
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
	void initEventList(int x);
	void assignFromCSV();
	int isTeacher(std::string*, int);

};