#pragma once
#include "utils.h"
#include "Parameters.h"
#include "Event.h"
#include "TimeSlots.h"

#include <ostream>

//Matvey Regentov


/* Handles the scheduling algorithm itself and schedule output as a .csv file
 * Usage:
 * - init with or pass Parameters object (keeps a reference to instance)
 * - append Event instances (copies data to duplicate instances)
 * - set error stream
 * - validate input
 * - syncAttendantReferences() to get rid of attendant duplicates
 * - generateSchedule(int seed) with seed to randomize output (also, exports the output)
 */
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
	// keeps reference to the object, which must not be deleted before Scheduler gets destroyed
	void setParam(Parameters* param) { this->param = param; }

	// Deletes duplicate Attendant instances
	void syncAttendantReferences();

	// Checks for obvious errors in the input
	int validateInput();

	// Copies data, given reference can then be deleted
	void appendEvent(const Event& e);

	// also exports the schedule to file
	void generateSchedule(int shuffleSeed);
	
	std::ostream* getErrorStream() const { return errorStream; }
	void setErrorStream(std::ostream& errorStream) { this->errorStream = &errorStream; }

};