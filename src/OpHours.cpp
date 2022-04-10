#include "OpHours.h"

OpHours::OpHours(int start[7], int end[7]) {
	for (int i = 0; i < 7; ++i) {
		startTimes[i] = start[i];
		endTimes[i] = end[i];
	}
}

OpHours::~OpHours() {

}


int OpHours::getTotalHours() const {
	int total = 0;
	for (int i = 0; i < 7; ++i) {
		total += getTotalHoursOnDay(i);
	}

	return total;
}

int OpHours::getTotalHoursOnDay(int day) const {
	return endTimes[day] - startTimes[day];
}

int OpHours::getTotalHoursOnDay(DaysOfWeek day) const {
	return getTotalHoursOnDay((int)day);
}

std::pair<int, int> OpHours::getHoursOnDay(int day) const {
	return std::pair<int, int>(startTimes[day], endTimes[day]);
}

std::pair<int, int> OpHours::getHoursOnDay(DaysOfWeek day) const {
	return getHoursOnDay((int)day);
}

DaysOfWeek OpHours::getNthHourDayOfWeek(int n) const {
	int hPass = 0;
	for (int i = 0; i < 7; ++i) {
		hPass += getTotalHoursOnDay(i);

		if (hPass >= n) {
			return intToDaysOfWeek(n);
		}
	}

}
