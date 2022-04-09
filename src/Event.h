#pragma once

#include "utils.h"
#include "Attendant.h"

class Event {
private:
	std::string name;
	int hours;
	Attendant* attendants[];
};