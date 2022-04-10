#include "Parameters.h"

Parameters::Parameters() {
    oph = OpHours();
    rooms = new Room * [MAX_ROOMS];
    nRooms = 0;
    maxClassLength = DEFAULT_MAX_CLASS_LENGH;
}

Parameters::~Parameters() {

}

OpHours Parameters::getOph() const {
    return oph;
}

void Parameters::setOph(OpHours oph) {
    this->oph = oph;
}

void Parameters::appendRoom(const Room& r) {
    if (nRooms >= MAX_ROOMS) {
        throw std::exception("Maximum number of rooms reached for Parameters object @" + (uint64_t) this);
    }

    rooms[nRooms] = new Room;
    rooms[nRooms]->setName(r.getName());
    rooms[nRooms]->setSeats(r.getSeats());
    rooms[nRooms]->setType(r.getType());
    
    ++nRooms;

}

Room** Parameters::getRoomsPtr() {
    return rooms;
}

int Parameters::getRoomNumber() {
    return nRooms;
}

int Parameters::getMaxClassLength() const
{
    return maxClassLength;
}

void Parameters::setMaxClassLength(int maxClassLength)
{
    this->maxClassLength = maxClassLength;
}

