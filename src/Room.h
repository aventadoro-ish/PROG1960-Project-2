#pragma once
#include "utils.h"

enum class RoomType {
	NULL_ROOM,
	LECTURE_HALL,
	TECH_LAB,
	COMPUTER_LAB,
	SPORTS_HALL
};

/* Works with both upper and lower case letters
 * 'l' -> RoomType::LECTURE_HALL
 * 't' -> RoomType::TECH_LAB
 * 'c' -> RoomType::COMPUTER_LAB
 * 's' -> RoomType::SPORTS_HALL
 * else -> RoomType::NULL_ROOM
 */
RoomType charToRoomType(char c);

class Room {
private:
	std::string name;
	int seats;
	RoomType type;

public:
	Room();
	Room(std::string name, int seats, RoomType type);
	Room(std::string name, int seats, char typeChar);
	~Room();

	std::string getName() const;
	void setName(std::string name);

	int getSeats() const;
	void setSeats(int seats);

	RoomType getType() const;
	void setType(RoomType type);
	void setType(std::string);

};
