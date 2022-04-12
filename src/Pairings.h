#pragma once
#include "CSV.h"
#include "Event.h"
#include "KeyNav.h"

class Pairings : public KeyNav{
private:
	Event* eventList;
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

	
	void editor();
	void printEvents();
};