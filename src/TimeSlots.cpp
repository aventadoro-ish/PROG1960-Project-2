#include "TimeSlots.h"

/********************************************************************/
/*                      class TimeSlot()                            */
/********************************************************************/
TimeSlot::TimeSlot() {
	startTime = 0;
	day = DaysOfWeek::MON;
	room = NULL;

	for (int i = 0; i < MAX_ATTENDANTS; ++i) {
		attendants[i] = NULL;
	}

	currentAttCount = 0;

}

TimeSlot::TimeSlot(int startTime, DaysOfWeek dow, Room* room) {
	this->startTime = startTime;
	day = dow;
	this->room = room;

	for (int i = 0; i < MAX_ATTENDANTS; ++i) {
		attendants[i] = NULL;
	}

	currentAttCount = 0;

}

TimeSlot::~TimeSlot() {
	for (int i = 0; i < MAX_ATTENDANTS; ++i) {
		delete attendants[i];
	}
}


int TimeSlot::getStartTime() const {
	return startTime;
}

void TimeSlot::setStartTime(int startTime) {
	this->startTime = startTime;
}

DaysOfWeek TimeSlot::getDay() const {
	return day;
}

void TimeSlot::setDay(DaysOfWeek day) {
	this->day = day;
}

Room* TimeSlot::getRoom() const {
	return room;
}

void TimeSlot::setRoom(Room* room) {
	this->room = room;
}

Attendant* TimeSlot::getAttendantsPtr() const{
	return *attendants;
}


/********************************************************************/
/*                      class TimeSlotManager()                     */
/********************************************************************/
TimeSlotManager::TimeSlotManager(Room rooms[], int nRooms, const OpHours& opHours) {
	this->rooms = rooms;
	
	nHours = opHours.getTotalHours();
	this->nRooms = nRooms;
	
	nTimeSlots = nHours * nRooms;

	for (int nthHour = 0; nthHour <= nHours; ++nthHour) {
		slots[nthHour] = new TimeSlot * [nRooms];

		for (int r = 0; r < nRooms; ++r) {
			slots[nthHour][r] = new TimeSlot(nthHour, opHours.getNthHourDayOfWeek(nthHour), &rooms[r]);
		}

	}




}

TimeSlotManager::~TimeSlotManager() {

}

TimeSlot* TimeSlotManager::getTimeSlot(int day, int hour, Room* room) {
	return NULL; // TODO: fix
}
