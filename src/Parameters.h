#pragma once
#include "utils.h"
#include "OpHours.h"
#include "Room.h"

class Parameters {
private:
	OpHours oph;
	Room** rooms;
	int nRooms;

	int maxClassLength;

public:
	Parameters();
	~Parameters();

    OpHours getOph() const;
    void setOph(OpHours oph);

	int getMaxClassLength() const;
	void setMaxClassLength(int maxClassLength);

	void appendRoom(const Room r);

};