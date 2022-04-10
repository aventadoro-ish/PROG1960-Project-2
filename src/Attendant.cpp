#include "Attendant.h"

/********************************************************************/
/*                      class Attendant()                           */
/********************************************************************/

Attendant::Attendant() {
    name = "John Doe";
    participantCount = 0;
}

Attendant::Attendant(std::string name, int participantCount) {
    this->name = name;
    this->participantCount = participantCount;
}


Attendant::~Attendant() {
   
}

std::string Attendant::getName() const {
    return name;
}

void Attendant::setName(std::string name) {
    this->name = name;
}

int Attendant::getParticipantCount() const {
    return ;
}

void Attendant::setParticipantCount(int participantCount) {
    this->participantCount = participantCount;
}


std::string Attendant::strRepr() const {
    return "Attendant " + name + " (" + std::to_string(participantCount) + ")";
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




