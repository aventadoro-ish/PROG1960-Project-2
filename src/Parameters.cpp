#include "Parameters.h"

Parameters::Parameters() {
    oph = OpHours();
    rooms = new Room* [MAX_ROOMS];
    nRooms = 0;
    maxClassLength = DEFAULT_MAX_CLASS_LENGH;
}

Parameters::~Parameters() {

}

void Parameters::assignFromCSV() {
    int index;
    std::string* buffer;
    int dayOfWeek;
    
    index = (findMatchingIndex("rooms") + 1);
    while (true) {
       buffer = getRowData(index);
       if (buffer[1] == "") break;
       Room temp = Room(buffer[0], stoi(buffer[2]), buffer[1][0]);
       appendRoom(temp);
       index++;
    }

    index = (findMatchingIndex("oph") + 1);
    while (true) {
        buffer = getRowData(index);
        if (buffer[1] == "") break;
        dayOfWeek = dowStrToInt(buffer[0]);
        oph.setStartTime(dayOfWeek, stoi(buffer[1]));
        oph.setEndTime(dayOfWeek, stoi(buffer[2]));
        index++;
    }
    //-------------------------------//
    // ADD NEWINFO ONCE STANDARDIZED //
    //-------------------------------//
    
}


int Parameters::findMatchingIndex(std::string heading) {
    char* target;
    for (int i = 0; i < getRowCount(); i++) {
        target = sToLower(getArrVal(i, 0));
        if (heading.compare(target) == 0) {
            return i;
        }
    }
    return -1;
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

    std::cout << r.getName();

    rooms[nRooms] = new Room();
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

void Parameters::testPrintParams() {
    std::cout << "HOURS:\n";
    std::cout << "MON " << oph.getTotalHoursOnDay(0) << std::endl;
    std::cout << "TUE " << oph.getTotalHoursOnDay(1) << std::endl;
    std::cout << "WED " << oph.getTotalHoursOnDay(2) << std::endl;
    std::cout << "THU " << oph.getTotalHoursOnDay(3) << std::endl;
    std::cout << "FRI " << oph.getTotalHoursOnDay(4) << std::endl;
    std::cout << "SAT " << oph.getTotalHoursOnDay(5) << std::endl;
    std::cout << "SUN " << oph.getTotalHoursOnDay(6) << std::endl;


    std::cout << "ROOMS:\n";
    for (int i = 0; i < nRooms; i++)
    {
        std::cout << rooms[i]->getName() << std::endl;
        std::cout << rooms[i]->getSeats() << std::endl;
    }
}