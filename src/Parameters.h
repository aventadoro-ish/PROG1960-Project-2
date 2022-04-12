#pragma once
#include "utils.h"
#include "OpHours.h"
#include "Room.h"
#include "CSV.h"


class Parameters : private CSV {
private:
	OpHours oph;
	Room** rooms;
	int nRooms;

	int maxClassLength;

public:
	Parameters();
	Parameters(std::string fileExt) : CSV(fileExt){
		importCSV();
		oph = OpHours();
		rooms = new Room * [MAX_ROOMS];
		nRooms = 0;
		maxClassLength = DEFAULT_MAX_CLASS_LENGH;
	}
	~Parameters();

	bool assignFromCSV();
	int findMatchingIndex(std::string);


    OpHours getOph() const;
    void setOph(OpHours oph);

	int getMaxClassLength() const;
	void setMaxClassLength(int maxClassLength);

	void appendRoom(const Room& r);

	Room** getRoomsPtr();
	int getRoomNumber();

	void testPrintParams();
};

