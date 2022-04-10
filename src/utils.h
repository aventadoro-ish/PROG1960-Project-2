#pragma once
#include <iostream>
#include <string>


#define MAX_ATTENDANTS 10
#define MAX_ROOMS 100
#define MAX_EVENTS 100

#define DEFAULT_MAX_CLASS_LENGH 3

enum class DaysOfWeek {
	MON,
	TUE,
	WED,
	THU,
	FRI,
	SAT,
	SUN
};

std::string daysOfWeekToStr(DaysOfWeek d);
DaysOfWeek intToDaysOfWeek(int d);
int dowStrToInt(std::string d);


char* sToLower(std::string);//Lowercase Strings