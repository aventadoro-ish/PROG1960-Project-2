#pragma once
#include "CSV.h"
#include "Event.h"

class Pairings : private CSV {
private:
	Event* eventList;
	int numEvents;

public:
	Pairings(int);
	Pairings(std::string fileExt) : CSV(fileExt) {
		importCSV();
	}
	~Pairings();

	//Main Import Function
	void assignFromCSV();
	//Supporting Import Functions
	void initEventList();
	void initEventList(int x);
	void assignAttendants(std::string*);
	int isTeacher(std::string*, int);


	void printEvents();
};