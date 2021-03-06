#pragma once
#include "CSV.h"
#include "Event.h"
#include "KeyNav.h"
#define ALL 255
#define NPOS std::string::npos

//Joshua Rice


class Pairings : public KeyNav{
private:
	Event* eventList[MAX_EVENTS];
	int numEvents;
	int numAttendants = 0;

public:
	Pairings();
	Pairings(CSV&);
	~Pairings();

	//Main Import Function
	void assignFromCSV(CSV&);
	//Supporting Import Functions
	void initEventList(int);
	int isTeacher(std::string[], int);


	//Editor Function

	
	int selectEvent(int);
	void printEvent(int);
	bool editor();
		
	int getNEvents() { return numEvents; }
	Event** getEventListPtr() { return eventList; }


};