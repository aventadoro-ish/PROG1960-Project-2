#pragma once
#include "utils.h"
#include "Room.h"
#include "Attendant.h"
#include "OpHours.h"
#include "Printable2DArray.h"

class TimeSlot {
private:
	int startTime;
	DaysOfWeek day;
	Room* room;
	Attendant* attendants[MAX_ATTENDANTS];
    int nAttendants;
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

    bool hasAttenant(std::string name, int nParticipant);
    void appendAttendant(const Attendant& att);


    std::string getStrRepr();


};

class TimeSlotManager : public Printable2DArray {
private:
    TimeSlot* * * slots;
    Room** rooms;

    int nRooms;
    int nHours;
    int nTimeSlots;

    int dayStartIdxs[7];

    DaysOfWeek getDayFromSlotIdx(int hourIdx);
    bool areAttendantsBusyDuring(int hourIdx, const Attendant* atts[], int nAtts);

    int getXLen();
    int getYLen();

    std::string getHeaderForRow(int y);
    std::string getHeaderForCol(int x);

    std::string getCellAsStr(int x, int y);

public:
    TimeSlotManager() {}
    TimeSlotManager(Room* rooms[], int nRooms, const OpHours& opHours);
    ~TimeSlotManager();

    TimeSlot* getFreeSlot(RoomType roomReq, const Attendant* atts[], int nAtts, int dayOfWeekOffset = -1);


};