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