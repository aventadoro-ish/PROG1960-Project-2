#include "Room.h"

//Matvey Regentov

RoomType charToRoomType(char c) {
	c |= 0b00100000; // decapitalize

	switch (c) {
	case 'l': return RoomType::LECTURE_HALL;
	case 't': return RoomType::TECH_LAB;
	case 'c': return RoomType::COMPUTER_LAB;
	case 's': return RoomType::SPORTS_HALL;
	default:
		return RoomType::NULL_ROOM;
	}
}

std::string roomTypeToString(RoomType rt) {
	switch (rt) {
	case RoomType::LECTURE_HALL:return "Lecture Hall";
	case RoomType::TECH_LAB:	return "Tech Lab";
	case RoomType::COMPUTER_LAB:return "Computer Lab";
	case RoomType::SPORTS_HALL:	return "Sports Hall";
	default:					return "Null Room";
	}

}

RoomType intToRoomType(int t) {
	switch(t){
	case 0: return RoomType::LECTURE_HALL;
	case 1: return RoomType::TECH_LAB;
	case 2: return RoomType::COMPUTER_LAB;
	case 3: return RoomType::SPORTS_HALL;
	default:
		return RoomType::NULL_ROOM;
	}

}

std::ostream& operator<<(std::ostream& out_stream, const Room& r) {
	out_stream << "Room \"" << r.getName() << "\" (" << roomTypeToString(r.getType()) << ") seats: " << r.getSeats();
	return out_stream;
}

Room::Room() {
	//std::cout << "Room\n";

	name = "-";
	seats = 0;
	type = RoomType::NULL_ROOM;
}

Room::Room(std::string name, int seats, RoomType type) {
	//std::cout << "Room\n";

	this->name = name;
	this->seats = seats;
	this->type = type;
}

Room::Room(std::string name, int seats, char typeChar) {
	//std::cout << "Room\n";

	this->name = name;
	this->seats = seats;
	this->type = charToRoomType(typeChar);
}

Room::~Room() {
	//std::cout << "!Room\n";

}

std::string Room::getName() const {
	return name;
}

void Room::setName(std::string name) {
	this->name = name;
}

int Room::getSeats() const {
	return seats;
}

void Room::setSeats(int seats) {
	this->seats = seats;
}

RoomType Room::getType() const {
	return type;
}

void Room::setType(RoomType type) {
	this->type = type;
}

void Room::setType(std::string type) {
	RoomType temp;
	temp = charToRoomType(type[0]);
	setType(temp);
}

