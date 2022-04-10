#pragma once
#include "utils.h"
#include "Room.h"
#include "Attendant.h"

class TimeSlot {
private:
	int startTime;
	DaysOfWeek day;
	Room* room;
	Attendant* attendants[MAX_ATTENDANTS];
    int currentAttCount;

public:
    TimeSlot();
    TimeSlot(int startTime, DaysOfWeek dow, Room* room);
    ~TimeSlot();

    int getStartTime() const;
    void setStartTime(int startTime);

    DaysOfWeek getDay() const;
    void setDay(DaysOfWeek day);

    Room* getRoom() const;
    void setRoom(Room* room);

    Attendant* getAttendantsPtr() const;

};

class TimeSlotManager {

};