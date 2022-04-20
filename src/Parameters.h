#pragma once
#include "utils.h"
#include "OpHours.h"
#include "Room.h"
#include "CSV.h"

//Matvey Regentov


class Parameters : private CSV {
private:
	OpHours oph;
	Room** rooms;
	int nRooms;

	int maxClassLength;
	int instructorTimeCostMultiplier;
	int studentTimeCostMultiplier;
	bool isEarlyPreffered;

public:
	Parameters();
	Parameters(std::string fileExt);
	~Parameters();

	bool assignFromCSV();
	int findMatchingIndex(std::string);


    OpHours getOph() const;//
    void setOph(OpHours oph);

	int getMaxClassLength() const;//
	void setMaxClassLength(int maxClassLength);

	void appendRoom(const Room& r);

	Room** getRoomsPtr();
	int getRoomNumber();//

	void testPrintParams();

    int getInstructorTimeCostMultiplier() const;//
    void setInstructorTimeCostMultiplier(int instructorTimeCostMultiplier);

    int getStudentTimeCostMultiplier() const;//
    void setStudentTimeCostMultiplier(int studentTimeCostMultiplier);

    bool getIsEarlyPreffered() const;//
    void setIsEarlyPreffered(bool isEarlyPreffered);

	void printAll();
	bool editor();
	
};

