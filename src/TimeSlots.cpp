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

	nAttendants = 0;

}

TimeSlot::TimeSlot(int startTime, DaysOfWeek dow, Room* room) {
	this->startTime = startTime;
	day = dow;
	this->room = room;
	isOcc = false;


	for (int i = 0; i < MAX_ATTENDANTS; ++i) {
		attendants[i] = NULL;
	}

	nAttendants = 0;

}

TimeSlot::~TimeSlot() {
	std::cout << "~Timeslot destructor " << std::endl;
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

bool TimeSlot::hasAttenant(std::string name, int nParticipant) {
	if (!isOcc) {
		return false;
	}

	for (int i = 0; i < nAttendants; i++) {
		if (attendants[i]->getName() == name && attendants[i]->getParticipantCount() == nParticipant) {
			return true;
		}
	}
	return false;
		
}

void TimeSlot::appendAttendant(const Attendant& att) {
	if (nAttendants >= MAX_ATTENDANTS) {
		std::string errMes = "Unable adding attendants to TimeSlot(" + 
			daysOfWeekToStr(day) + " " + std::to_string(startTime) + "h";
		std::cout << errMes << std::endl;
		throw std::exception(errMes.c_str());
	}

	attendants[nAttendants] = new Attendant(att.getName(), att.getParticipantCount());
	++nAttendants;

	isOcc = true;
}

std::string TimeSlot::getStrRepr() {
	std::string instructors = "";
	std::string students = "";

	for (int i = 0; i < nAttendants; i++) {
		if (attendants[i]->getParticipantCount() == 0) {
			// instructor
			if (instructors.length() > 0) {
				instructors += "| ";
			}
			instructors += "instructor" + attendants[i]->getName();
		}
		else {
			// students
			if (students.length() > 0) {
				students += "| ";
			}
			students += attendants[i]->getName() + " (" + std::to_string(attendants[i]->getParticipantCount()) + ")";


		}
	}
	return instructors + "| " + students;
}

std::string TimeSlotManager::getHeaderForCol(int x) {
	return slots[0][x]->getRoom()->getName();
}

std::string TimeSlotManager::getHeaderForRow(int y) {
	return  daysOfWeekToStr(slots[y][0]->getDay()) + " " + std::to_string(slots[y][0]->getStartTime());
}


/********************************************************************/
/*                      class TimeSlotManager()                     */
/********************************************************************/
//TimeSlotManager::TimeSlotManager() {
//	std::cout << "Parameter-less constructor for TimeSlotManager must not be called. Ever." << std::endl;
//	slots = NULL;
//	rooms = NULL;
//
//	nRooms = 0;
//	nHours = 0;
//	nTimeSlots = 0;
//
//	dayStartIdxs[0] = 0;
//	dayStartIdxs[1] = 0;
//	dayStartIdxs[2] = 0;
//	dayStartIdxs[3] = 0;
//	dayStartIdxs[4] = 0;
//	dayStartIdxs[5] = 0;
//	dayStartIdxs[6] = 0;
//}

TimeSlotManager::TimeSlotManager(Room* rooms[], int nRooms, const OpHours& opHours) {
	std::cout << "TSM constructor" << std::endl;
	this->rooms = rooms;
	
	nHours = opHours.getTotalHours();
	this->nRooms = nRooms;
	
	nTimeSlots = nHours * nRooms;

	int hPass = 0;
	dayStartIdxs[0] = 0;
	hPass += opHours.getTotalHoursOnDay(0);
	for (int i = 1; i < 7; i++) {
		dayStartIdxs[i] = hPass;
		hPass += opHours.getTotalHoursOnDay(i);
	}

	slots = new TimeSlot * *[nHours];
	for (int h = 0; h < nHours; ++h) {
		slots[h] = new TimeSlot * [nRooms];
		for (int r = 0; r < nRooms; ++r) {

			slots[h][r] = new TimeSlot(h, opHours.getNthHourDayOfWeek(h), rooms[r]);

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

// Printable2DArray methods
int TimeSlotManager::getXLen() {
	return nRooms;
}
int TimeSlotManager::getYLen() {
	return nHours;
}

std::string TimeSlotManager::getCellAsStr(int x, int y) {
	return slots[y][x]->getStrRepr();
}

TimeSlot* TimeSlotManager::getFreeSlot(RoomType roomReq, const Attendant* atts[], int nAtts, int dayOfWeekOffset) {
	int startHourSlot = 0;
	if (dayOfWeekOffset != -1) {
		startHourSlot = dayStartIdxs[dayOfWeekOffset];
	}

	int totalParticipantCount = 0;
	for (int i = 0; i < nAtts; i++)	{
		totalParticipantCount += atts[i]->getParticipantCount();
	}

	for (int hour = startHourSlot; hour < nHours; hour++) {
		if (areAttendantsBusyDuring(hour, atts, nAtts)) {
			continue;
		}

		for (int room = 0; room < nRooms; room++) {
			TimeSlot* ts = slots[hour][room];

			if (ts->getRoom()->getType() != roomReq) continue;

			if (ts->getRoom()->getSeats() < totalParticipantCount) continue;

			return ts;


		}
	}

	std::string errMes = "No timeslots left that meet requirements: totalSeats=" + std::to_string(totalParticipantCount) +
		" roomRequiremnet=" + roomTypeToString(roomReq) + " for attendants: ";
	for (int i = 0; i < nAtts; i++)	{
		errMes += atts[i]->getName() + ", ";
	}

	std::cout << errMes << std::endl;
	throw std::exception(errMes.c_str());

}


// PRIVATE:

DaysOfWeek TimeSlotManager::getDayFromSlotIdx(int hourIdx) {
	if (dayStartIdxs[0] <= hourIdx < dayStartIdxs[1]) return DaysOfWeek::MON;
	else if (dayStartIdxs[1] <= hourIdx && hourIdx < dayStartIdxs[2]) return DaysOfWeek::TUE;
	else if (dayStartIdxs[2] <= hourIdx && hourIdx < dayStartIdxs[3]) return DaysOfWeek::WED;
	else if (dayStartIdxs[3] <= hourIdx && hourIdx < dayStartIdxs[4]) return DaysOfWeek::THU;
	else if (dayStartIdxs[4] <= hourIdx && hourIdx < dayStartIdxs[5]) return DaysOfWeek::FRI;
	else if (dayStartIdxs[5] <= hourIdx && hourIdx < dayStartIdxs[6]) return DaysOfWeek::SAT;
	else if (dayStartIdxs[6] <= hourIdx && hourIdx < nHours) return DaysOfWeek::SUN;
	else throw std::exception("Error while finding day of the week from hourSlotIdx. hourSlotIdx > nHours");
}

bool TimeSlotManager::areAttendantsBusyDuring(int hourIdx, const Attendant* atts[], int nAtts) {
	for (int roomIdx = 0; roomIdx < nRooms; roomIdx++) {
		for (int attIdx = 0; attIdx < nAtts; attIdx++) {
			std::string name = atts[attIdx]->getName();
			int nP = atts[attIdx]->getParticipantCount();

			if (slots[hourIdx][roomIdx]->hasAttenant(name, nP)) {
				return true;
			}
		}
	}
	return false;
}


