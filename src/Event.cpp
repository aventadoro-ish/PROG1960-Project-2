#include "Event.h"

Event::Event() {
	name = "";
	hours = 0;
	
	for (int i = 0; i < MAX_ATTENDANTS; ++i) {
		attendants[i] = NULL;
	}

	currentAttCount = 0;

}

Event::~Event() {
	//delete[] attendants;	// this: C4154 deletion of an array expression; conversion to pointer supplied
	//delete[] &attendants; // does not give a warning, but still crashes the program
	for (int i = 0; i < currentAttCount; ++i) {
		delete attendants[i];
	}
}


std::string Event::getName() const {
	return name;
}

void Event::setName(std::string name) {
	this->name = name;
}

int Event::getHours() const {
	return hours;
}

void Event::setHours(int hours) {
	this->hours = hours;
}

Attendant* Event::getAttendatnsPtr() {
	return *attendants;
}

std::string Event::getAttendantNamesStr() const {
	if (currentAttCount == 0) {
		return "/nobody/";
	}

	std::string out = attendants[0]->getName();
	for (int i = 1; i < currentAttCount; ++i) {
		out += " " + attendants[i]->getName();
	}
	
	return out;
}


void Event::appendAttendant(const Attendant& att) {
	if (currentAttCount >= MAX_ATTENDANTS) {
		std::string errMessage = "Attendant Limit reached for event" + this->name + ", while adding attendant" + att.strRepr();
		throw std::exception(errMessage.c_str()); // TODO: exception - change to custom when it is implemented
	}
	attendants[currentAttCount] = new Attendant(att.getName(), att.getParticipantCount());


	++currentAttCount;
}


void Event::appendAttendant(std::string name, int partCount) {
	if (currentAttCount >= MAX_ATTENDANTS) {
		std::string errMessage = "Attendant Limit reached for event" + this->name + ", while adding attendant" + name;
		throw errMessage; // TODO: exception - change to custom when it is implemented
	}

	attendants[currentAttCount]->setName(name);
	attendants[currentAttCount]->setParticipantCount(partCount);

	++currentAttCount;
}

std::ostream& operator<<(std::ostream& out_stream, const Event& evt) {
	out_stream << "Event:" << evt.getName() << " (" << evt.getHours() << "h): " << evt.getAttendantNamesStr();
	return out_stream;
}


int Event::getCurrentAttCount() const {
    return currentAttCount;
}

Attendant* Event::getAttendant(int idx) const {
	if (idx > currentAttCount) {
		std::string errorMes = "Attendant idx out of bounds for event: " + name +
			". Max attendants: " + std::to_string(currentAttCount) + ", passed index: " + std::to_string(idx);
		throw std::exception(errorMes.c_str());
	}

	return attendants[idx];

}

RoomType Event::getRoomReq() const {
    return roomReq;
}

void Event::setRoomReq(RoomType roomReq) {
    this->roomReq = roomReq;
}

