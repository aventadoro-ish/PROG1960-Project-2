#pragma once
#include "utils.h"

//Matvey Regentov

class OpHours {
private:
	int startTimes[7];
	int endTimes[7];
public:
	OpHours();
	OpHours(int start[7], int end[7]);
	~OpHours();

	int getTotalHours() const;
	int getTotalHoursOnDay(int day) const;
	int getTotalHoursOnDay(DaysOfWeek day) const;

	std::pair<int, int> getHoursOnDay(int day) const;
	std::pair<int, int> getHoursOnDay(DaysOfWeek day) const;

	DaysOfWeek getNthHourDayOfWeek(int n) const;

	void setStartTime(int, int);
	void setEndTime(int, int);

	int getNWorkDays();

};
