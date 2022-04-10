#pragma once
#include "utils.h"
#include "Room.h"
#include "Attendant.h"
#include "OpHours.h"

class TimeSlot {
private:
	int startTime;
	DaysOfWeek day;
	Room* room;
	Attendant* attendants[MAX_ATTENDANTS];
    int currentAttCount;
    bool isOcc;

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

    bool isOccupied();

};

class TimeSlotManager {
private:
    TimeSlot* * * slots;
    Room* rooms;

    int nRooms;
    int nHours;
    int nTimeSlots;


public:
    TimeSlotManager(Room rooms[], int nRooms, const OpHours& opHours);
    ~TimeSlotManager();

};