#include "Parameters.h"

Parameters::Parameters() {
    oph = OpHours();
    rooms = new Room* [MAX_ROOMS];
    nRooms = 0;

    // assign default preferences
    maxClassLength = DEFAULT_MAX_CLASS_LENGH;
    instructorTimeCostMultiplier = DEFAULT_INSTRUCTOR_TIME_COST_MULTIPLIER;
    studentTimeCostMultiplier = DEFAULT_STUDENT_TIME_COST_MULTIPLIER;
    isEarlyPreffered = DEFAULT_IS_EARLY_PREFERED;
}

Parameters::Parameters(std::string fileExt) : CSV(fileExt) {
    oph = OpHours();
    rooms = new Room * [MAX_ROOMS];
    nRooms = 0;

    // assign default preferences
    maxClassLength = DEFAULT_MAX_CLASS_LENGH;
    instructorTimeCostMultiplier = DEFAULT_INSTRUCTOR_TIME_COST_MULTIPLIER;
    studentTimeCostMultiplier = DEFAULT_STUDENT_TIME_COST_MULTIPLIER;
    isEarlyPreffered = DEFAULT_IS_EARLY_PREFERED;

    importCSV(); // not running it the second time breakes it
    assignFromCSV();
}


Parameters::~Parameters() {
    for (int i = 0; i < nRooms; i++) {
        delete rooms[i];
    }
    delete rooms;
}

bool Parameters::assignFromCSV() {
    int index;
    std::string* buffer;
    int dayOfWeek;

    if ((index = (findMatchingIndex("rooms") >= 0))) {
        while (true) {
            buffer = getRowData(index);

            //std::cout << buffer[0] << "; " << buffer[2] << "; " << buffer[1][0] << std::endl;

            if (buffer[1] == "") break;

            Room temp = Room(buffer[0], std::stoi(buffer[2]), buffer[1][0]);
            appendRoom(temp);
            index++;
        }
        index++;

    }
    else {
        std::cout << "ERROR: ROOMS INDEX NOT FOUND. (Parameters::assignFromCSV function)";
        return false;
    }

    if (index = (findMatchingIndex("work days"))) {
        index++;
        while (true) {
            buffer = getRowData(index);
            if (buffer[1] == "") break;
            dayOfWeek = dowStrToInt(buffer[0]);
            oph.setStartTime(dayOfWeek, stoi(buffer[1]));
            oph.setEndTime(dayOfWeek, stoi(buffer[2]));
            index++;
        }
    }
    else {
        std::cout << "ERROR: OPH INDEX NOT FOUND. (Parameters::assignFromCSV function)";
        return false;
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
int Parameters::getInstructorTimeCostMultiplier() const
{
    return instructorTimeCostMultiplier;
}

void Parameters::setInstructorTimeCostMultiplier(int instructorTimeCostMultiplier)
{
    this->instructorTimeCostMultiplier = instructorTimeCostMultiplier;
}

int Parameters::getStudentTimeCostMultiplier() const
{
    return studentTimeCostMultiplier;
}

void Parameters::setStudentTimeCostMultiplier(int studentTimeCostMultiplier)
{
    this->studentTimeCostMultiplier = studentTimeCostMultiplier;
}

bool Parameters::getIsEarlyPreffered() const
{
    return isEarlyPreffered;
}

void Parameters::setIsEarlyPreffered(bool isEarlyPreffered)
{
    this->isEarlyPreffered = isEarlyPreffered;
}

void Parameters::printAll() {
    
}

bool Parameters::editor() {
    clearEx(3);
    std::cout << "NOTE: USE NUM KEYS TO NAVIGATE THIS EDITOR\n\n";
    std::cout << "Please select a parameter to modify:\n";
    std::cout << "1. Max Class Length = " << getMaxClassLength() << std::endl;
    std::cout << "2. Instructor Time Cost Muiltiplier = " << getInstructorTimeCostMultiplier() << std::endl;
    std::cout << "3. Student Time Cost Multiplier = " << getStudentTimeCostMultiplier() << std::endl;
    std::cout << "4. isEarlyPreffered? = " << getIsEarlyPreffered() << std::endl;
    std::cout << "\n5. Exit to main menu\n\n";
    int menuSel = 0;
    std::cin >> menuSel;
    int buff;
    switch (menuSel) {
    case 1:
        std::cout << "Please enter a new max class length: ";
        std::cin >> buff;
        setMaxClassLength(buff);
        break;
    case 2:
        std::cout << "Please enter a new Instructor Time Cost Multiplier: ";
        std::cin >> buff;
        setInstructorTimeCostMultiplier(buff);
        break;
    case 3:
        std::cout << "Please enter a new Student Time Cost Multiplier: ";
        std::cin >> buff;
        setStudentTimeCostMultiplier(buff);
        break;
    case 4:
        std::cout << "What would you like to set IsEarlyPrefferred to: ";
        std::cout << "\n\n1. True\n2. False\n";
        std::cin >> buff;
        switch (buff) {
        case 1:
            setIsEarlyPreffered(true);
            break;
        case 2:
            setIsEarlyPreffered(false);
            break;
        }
        break;
    case 5:
        return false;
    }
    return true;
}
