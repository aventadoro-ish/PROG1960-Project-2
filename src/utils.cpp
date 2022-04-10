#include "utils.h"

std::string daysOfWeekToStr(DaysOfWeek d) {
	switch (d) {
	case DaysOfWeek::MON: return "Monday";
	case DaysOfWeek::TUE: return "Tuesday";
	case DaysOfWeek::WED: return "Wednesday";
	case DaysOfWeek::THU: return "Thursday";
	case DaysOfWeek::FRI: return "Friday";
	case DaysOfWeek::SAT: return "Saturday";
	case DaysOfWeek::SUN: return "Sunday";
	default: return "---";
	}
}

DaysOfWeek intToDaysOfWeek(int d) {
	switch (d) {
	case 0: return DaysOfWeek::MON;
	case 1: return DaysOfWeek::TUE;
	case 2: return DaysOfWeek::WED;
	case 3: return DaysOfWeek::THU;
	case 4: return DaysOfWeek::FRI;
	case 5: return DaysOfWeek::SAT;
	case 6: return DaysOfWeek::SUN;
	default: throw std::exception("Invalid Day of week index" + d);
	}
}