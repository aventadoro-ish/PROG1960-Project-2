#pragma once
#include <iostream>
#include <string>

#define divide_int_round_up(i, div) (i + div - 1) / div

#define MAX_ATTENDANTS 10
#define MAX_ROOMS 100
#define MAX_EVENTS 100
#define MAX_TOTAL_ATTENDANTS 1000

#define DEFAULT_MAX_CLASS_LENGH 3
#define DEFAULT_INSTRUCTOR_TIME_COST_MULTIPLIER 2
#define DEFAULT_STUDENT_TIME_COST_MULTIPLIER 1
#define DEFAULT_IS_EARLY_PREFERED true

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

void moveCursor(int x, int y);
void clearEx(int numOfLines);
char* sToLower(std::string);//Lowercase Strings