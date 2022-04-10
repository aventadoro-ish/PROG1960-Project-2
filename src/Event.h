#pragma once
#include "utils.h"
#include "Attendant.h"
#include "Room.h"

class Event;
std::ostream& operator<<(std::ostream& out_stream, const Event& evt);

class Event {
private:
	std::string name;
	int hours;
	Attendant* attendants[MAX_ATTENDANTS];
	int currentAttCount;
	RoomType roomReq;

public:
	Event();
	~Event();

	std::string getName() const;
	void setName(std::string name);

	int getHours() const;
	void setHours(int hours);

	int getCurrentAttCount() const;

	Attendant* getAttendatnsPtr();
	std::string getAttendantNamesStr() const;

	void appendAttendant(const Attendant&);
	void appendAttendant(std::string, int);
	Attendant* getAttendant(int idx) const;

    RoomType getRoomReq() const;
    void setRoomReq(RoomType roomReq);

};


