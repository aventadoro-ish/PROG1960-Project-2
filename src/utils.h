#pragma once
#include <iostream>
#include <string>


#define MAX_ATTENDANTS 10

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