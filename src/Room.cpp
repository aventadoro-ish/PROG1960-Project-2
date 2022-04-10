#include "Room.h"

Room::Room() {
    name = "-";
    seats = 0;
    type = RoomType::NULL_ROOM;
}

Room::Room(std::string name, int seats, RoomType type) {
    this->name = name;
    this->seats = seats;
    this->type = type;
}

Room::Room(std::string name, int seats, char typeChar) {
    this->name = name;
    this->seats = seats;
    this->type = charToRoomType(typeChar);
}

Room::~Room() {

}



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
