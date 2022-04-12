#pragma once
#include "utils.h"
#include "Parameters.h"
#include "Event.h"
#include "TimeSlots.h"

class Scheduler {
private:
	Parameters param;
	Event* events[MAX_EVENTS];
	int nEvents;
	TimeSlotManager* tsm;

	void appendEventSplit(const Event& e);
	void appendEventNonSplit(const Event& e);
	
	// based on class load for each day returns nthBest day to schedule an event for all participants
	// if tie between days return the one where the class can be scheduled earlier or later based on param
	int getBestDayForClass(Event* e, int nthBest = 1);

	// based on class load for each day modifies resArray to have score for each day
	// the lower the score, the lesser load
	void getDailyScoreForEvent(Event* e, int resArrayPtr[7]);

public:
	Scheduler();
	Scheduler(Parameters para);
	~Scheduler();

	Parameters getParam() const;
    void setParam(Parameters param);

	void appendEvent(const Event& e);

	void generateSchedule(int shuffleSeed);

	void syncAttendantReferences();


};