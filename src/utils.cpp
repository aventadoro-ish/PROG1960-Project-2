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

int dowStrToInt(std::string d) {
	if (d.compare("MON") == 0) return 0;
	if (d.compare("TUE") == 0) return 1;
	if (d.compare("WED") == 0) return 2;
	if (d.compare("THU") == 0) return 3;
	if (d.compare("FRI") == 0) return 4;
	if (d.compare("SAT") == 0) return 5;
	if (d.compare("SUN") == 0) return 6;
	
}

char* sToLower(std::string x) {
	char c[20];
	x.copy(c, x.size(), 0);
	c[x.size()] = '\0';
	for (int i = 0; i < x.size(); i++) {
		c[i] = std::tolower(c[i]);
	}
	return c;
}