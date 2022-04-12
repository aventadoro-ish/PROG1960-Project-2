#pragma once
#include "utils.h"

class Attendant {
private:
	std::string name;
	int participantCount;
	int refCount;
	int nHoursArr[7];

public:
	Attendant();
	Attendant(std::string name, int participantCount);
	~Attendant();

	virtual std::string getName() const;
	virtual void setName(std::string name);

	virtual int getParticipantCount() const;
	virtual void setParticipantCount(int participantCount);

	virtual std::string strRepr() const;

	int incRefCount() {	return ++refCount; }
	int decRefCount() { return --refCount; }
	int getRefCount() { return refCount;  }

	int getNBusyHoursOnDay(DaysOfWeek day);
	int getNBusyHoursOnDay(int day);
	int incNHoursOnDay(int day) { return ++nHoursArr[day]; }
	int dayNHoursOnDay(int day) { return --nHoursArr[day]; }

	static int instCount; // TODO: temp var for testing


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
