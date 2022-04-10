#pragma once
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


public:
	Scheduler();
	Scheduler(Parameters para);
	~Scheduler();

	Parameters getParam() const;
    void setParam(Parameters param);

	void appendEvent(const Event& e);

	void generateSchedule(int shuffleSeed);

};