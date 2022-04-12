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


void moveCursor(int x, int y) {
	if (x == 0) {
		printf("\33[H\33[%dB\33[%dC", y, x-1);
	}
	else if (y == 0) {
		printf("\33[H\33[%dB\33[%dC", y-1, x);
	}
	else printf("\33[H\33[%dB\33[%dC", y, x);
	
}
void clearEx(int numOfLines) {
	if (numOfLines == 0) {
		printf_s("\33[H\33[0J");
		for (int i = 0; i < 300; i++) {
			printf("\33 M");
		}
		printf("\33[H\33[0J");
	}
	else {
		printf("\33[100A\33[100D");
		printf("\33[H\33[%dB\33[0J", numOfLines);
	}
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