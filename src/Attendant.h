#pragma once
#include "utils.h"

class Attendant {
private:
	std::string name;
	int participantCount;

public:
    Attendant();
    Attendant(std::string name, int participantCount);
    ~Attendant();

    virtual std::string getName() const;
    virtual void setName(std::string name);

    virtual int getParticipantCount() const;
    virtual void setParticipantCount(int participantCount);

    virtual std::string strRepr() const;

};

class Instructor : public Attendant {
public:
    Instructor(): Attendant() {}
    Instructor(std::string name): Attendant(name, 0) {}
    ~Instructor() {}

    int getParticipantCount() const;

};

class StudentStream : public Attendant {
public:
    StudentStream() : Attendant() {}
    StudentStream(std::string name, int participantCount) : Attendant(name, participantCount) {}
    ~StudentStream() {}

    int getParticipantCount() const;

};