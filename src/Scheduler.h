#pragma once
#include "Parameters.h"
#include "Event.h"

class Scheduler {
private:
	Parameters param;
	Event* events[MAX_EVENTS];
	int nEvents;

public:
	Scheduler();
	~Scheduler();

	Parameters getParam() const;
    void setParam(Parameters param);

	void appendEvent(const Event e);
};