#pragma once
#include "utils.h"
#include "Parameters.h"
#include "Event.h"
#include "TimeSlots.h"

#include <ostream>

//Matvey Regentov

class Scheduler {
private:
	Parameters* param;
	Event* events[MAX_EVENTS];
	int nEvents;
	TimeSlotManager* tsm;
	std::ostream* errorStream;

	void appendEventSplit(const Event& e);
	void appendEventNonSplit(const Event& e);
	
	// based on class load for each day returns nthBest day to schedule an event for all participants
	// if tie between days return the one where the class can be scheduled earlier or later based on param
	int getBestDayForClass(Event* e, int nthBest = 1);

	// based on class load for each day modifies resArray to have score for each day
	// the lower the score, the lesser load
	void getDailyScoreForEvent(Event* e, int resArrayPtr[7]);

	// tries to fit the event into existing tsm table
	int allocateEvent(Event* e);

	void error(std::string errMes, bool isCritical = false);



public:
	Scheduler();
	Scheduler(Parameters* para);
	~Scheduler();

	Parameters* getParam() const { return param; }
	void setParam(Parameters* param) { this->param = param; }

	void syncAttendantReferences();

	int validateInput();


	void appendEvent(const Event& e);

	void generateSchedule(int shuffleSeed);
	
	std::ostream* getErrorStream() const { return errorStream; }
	void setErrorStream(std::ostream& errorStream) { this->errorStream = &errorStream; }

};