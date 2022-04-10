#pragma once
#include "utils.h"

class OpHours {
private:
	int startTimes[7];
	int endTimes[7];
public:
	OpHours(int start[7], int end[7]);
	~OpHours();

	int getTotalHours() const;
	int getTotalHoursOnDay(int day) const;
	int getTotalHoursOnDay(DaysOfWeek day) const;

	std::pair<int, int> getHoursOnDay(int day) const;
	std::pair<int, int> getHoursOnDay(DaysOfWeek day) const;

	DaysOfWeek getNthHourDayOfWeek(int n) const;

};
