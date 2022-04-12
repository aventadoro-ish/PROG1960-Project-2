#include "Attendant.h"

/********************************************************************/
/*                      class Attendant()                           */
/********************************************************************/

int Attendant::instCount = 0;// TODO: temp var for testing

Attendant::Attendant() {
    name = "John Doe";
    participantCount = 0;
    refCount = 0;

    for (int i = 0; i < 7; i++) {
        nHoursArr[i] = 0;
    }
    ++instCount; // TODO: temp var for testing
    //std::cout << " attendand constructor (" << instCount << ")\n";



}

Attendant::Attendant(std::string name, int participantCount) {
    this->name = name;
    this->participantCount = participantCount;
    refCount = 0;
    
    for (int i = 0; i < 7; i++) {
        nHoursArr[i] = 0;
    }


    ++instCount; // TODO: temp var for testing
    //std::cout << " attendand constructor (" << instCount << ")\n";

}


Attendant::~Attendant() {
    if (refCount > 1) {
        std::cout << "Deleting attendant with multiple references to it!\n";
    }

    --instCount; // TODO: temp var for testing
}



std::string Attendant::getName() const {
    return name;
}

void Attendant::setName(std::string name) {
    this->name = name;
}

int Attendant::getParticipantCount() const {
    return participantCount;
}

void Attendant::setParticipantCount(int participantCount) {
    this->participantCount = participantCount;
}


std::string Attendant::strRepr() const {
    return "Attendant " + name + " (" + std::to_string(participantCount) + ")";
}


int Attendant::getNBusyHoursOnDay(int day) {
    return nHoursArr[day];
}

int Attendant::getNBusyHoursOnDay(DaysOfWeek day) {
    return getNBusyHoursOnDay((int)day);
}


/********************************************************************/
/*                      class Instructor()                          */
/********************************************************************/
int Instructor::getParticipantCount() const {
    return 0;
}



/********************************************************************/
/*                      class StudentStream()                       */
/********************************************************************/
int StudentStream::getParticipantCount() const {
    return Attendant::getParticipantCount();
}




