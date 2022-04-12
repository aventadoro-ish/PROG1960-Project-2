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
	int instructorTimeCostMultiplier;
	int studentTimeCostMultiplier;
	bool isEarlyPreffered;

public:
	Parameters();
	Parameters(std::string fileExt) : CSV(fileExt){
		// assign default preferences
		maxClassLength = DEFAULT_MAX_CLASS_LENGH;
		instructorTimeCostMultiplier = DEFAULT_INSTRUCTOR_TIME_COST_MULTIPLIER;
		studentTimeCostMultiplier = DEFAULT_STUDENT_TIME_COST_MULTIPLIER;
		isEarlyPreffered = DEFAULT_IS_EARLY_PREFERED;

		importCSV();
		oph = OpHours();
		rooms = new Room * [MAX_ROOMS];
		nRooms = 0;

;
	}
	~Parameters();

	void assignFromCSV();
	int findMatchingIndex(std::string);


    OpHours getOph() const;
    void setOph(OpHours oph);

	int getMaxClassLength() const;
	void setMaxClassLength(int maxClassLength);

	void appendRoom(const Room& r);

	Room** getRoomsPtr();
	int getRoomNumber();

	void testPrintParams();

    int getInstructorTimeCostMultiplier() const;
    void setInstructorTimeCostMultiplier(int instructorTimeCostMultiplier);

    int getStudentTimeCostMultiplier() const;
    void setStudentTimeCostMultiplier(int studentTimeCostMultiplier);

    bool getIsEarlyPreffered() const;
    void setIsEarlyPreffered(bool isEarlyPreffered);

};

