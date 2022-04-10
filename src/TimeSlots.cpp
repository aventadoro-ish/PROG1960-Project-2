#include "TimeSlots.h"

/********************************************************************/
/*                      class TimeSlot()                            */
/********************************************************************/
TimeSlot::TimeSlot() {
	startTime = 0;
	day = DaysOfWeek::MON;
	room = NULL;
	isOcc = false;

	for (int i = 0; i < MAX_ATTENDANTS; ++i) {
		attendants[i] = NULL;
	}

	currentAttCount = 0;

}

TimeSlot::TimeSlot(int startTime, DaysOfWeek dow, Room* room) {
	this->startTime = startTime;
	day = dow;
	this->room = room;
	isOcc = false;


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

bool TimeSlot::isOccupied() {
	return isOcc;
}



/********************************************************************/
/*                      class TimeSlotManager()                     */
/********************************************************************/
TimeSlotManager::TimeSlotManager(Room rooms[], int nRooms, const OpHours& opHours) {
	this->rooms = rooms;
	
	nHours = opHours.getTotalHours();
	this->nRooms = nRooms;
	
	nTimeSlots = nHours * nRooms;

	slots = new TimeSlot * *[nHours];
	for (int h = 0; h < nHours; ++h) {
		slots[h] = new TimeSlot * [nRooms];
		for (int r = 0; r < nRooms; ++r) {
				slots[h][r] = new TimeSlot(h, opHours.getNthHourDayOfWeek(h), &rooms[r]);
		}
	}



}

TimeSlotManager::~TimeSlotManager() {
	for (int h = 0; h < nHours; ++h) {
		for (int r = 0; r < nRooms; ++r) {
			delete slots[h][r];
		}
		delete slots[h];
	}
	delete slots;
}
