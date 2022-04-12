#include "Scheduler.h"
#include <algorithm>    // std::random_shuffle

#include <fstream>

using namespace std;

int getNthSmallesIndex(int nth, const int temp[]);
// retunrs -1 if not found
int findAttendantInArray(string name, int partCount, Attendant* bufPtr[], int bufSize);


/********************************INSTANTIATING******************************************/
// sets default data
Scheduler::Scheduler() {
	std::cout << "parameter-less Scheduler constructor called!!!" << std::endl;
	param = new Parameters();
	for (int i = 0; i < MAX_EVENTS; ++i) {
		events[i] = NULL;
	}
	nEvents = 0;
	errorStream = &std::cerr;

	tsm = new TimeSlotManager(param->getRoomsPtr(), param->getRoomNumber(), param->getOph());
}

// sets default data except for papameters
Scheduler::Scheduler(Parameters* para) {
	param = para;
	for (int i = 0; i < MAX_EVENTS; ++i) {
		events[i] = NULL;
	}
	nEvents = 0;

	errorStream = &std::cerr;

	tsm =  new TimeSlotManager(param->getRoomsPtr(), param->getRoomNumber(), param->getOph());
}

Scheduler::~Scheduler() {
	for (int i = 0; i < nEvents; ++i) {
		delete events[i];
	}
	delete tsm;
}

/********************************DATA_FLOW**********************************************/
// creates new instance of the event and plainly copies data
void Scheduler::appendEventSplit(const Event& e) {
	// divide round up
	int splits = (e.getHours() + param->getMaxClassLength() - 1) / param->getMaxClassLength();
	int totalHours = e.getHours();
	int hCounter = 0;

	for (int i = 0; i < splits; ++i) {
		if (nEvents >= MAX_EVENTS) {
			throw std::exception("Max number of events supassed for a schedule!");
		}

		events[nEvents] = new Event();

		for (int i = 0; i < e.getCurrentAttCount(); ++i) {
			events[nEvents]->appendAttendant(*e.getAttendant(i));
		}
		int thisEventHours = std::min(totalHours - hCounter, param->getMaxClassLength());
		hCounter += thisEventHours;

		events[nEvents]->setHours(thisEventHours);
		events[nEvents]->setName(e.getName());
		++nEvents;
	}
}

// creates new instance(s) of the event(s) dividing hours between them
void Scheduler::appendEventNonSplit(const Event& e) {

	if (nEvents >= MAX_EVENTS) {
		throw std::exception("Max number of events supassed for a schedule!");
	}

	events[nEvents] = new Event();
	for (int i = 0; i < e.getCurrentAttCount(); ++i) {
		events[nEvents]->appendAttendant(*e.getAttendant(i));
	}

	events[nEvents]->setHours(e.getHours());
	events[nEvents]->setName(e.getName());
	events[nEvents]->setRoomReq(e.getRoomReq());

	++nEvents;
}

void Scheduler::appendEvent(const Event& e) {
	appendEventNonSplit(e);
	//appendEventSplit(e);

}

/********************************UTILITY************************************************/

void Scheduler::syncAttendantReferences() {
	Attendant* attsBuf[MAX_TOTAL_ATTENDANTS];
	int nUniqueAtts = 0;


	for (int eIdx = 0; eIdx < nEvents; eIdx++) {
		for (int attIdx = 0; attIdx < events[eIdx]->getCurrentAttCount(); attIdx++) {
			string thisName = events[eIdx]->getAttendant(attIdx)->getName();
			int thisPartCount = events[eIdx]->getAttendant(attIdx)->getParticipantCount();

			int idx = findAttendantInArray(thisName, thisPartCount, attsBuf, nUniqueAtts);

			if (idx == -1) {
				attsBuf[nUniqueAtts] = new Attendant(thisName, thisPartCount);
				idx = nUniqueAtts;
				++nUniqueAtts;
			}

			events[eIdx]->changeAttendantPtr(attIdx, attsBuf[idx]);
			attsBuf[idx]->incRefCount();

		}

	}
}

int Scheduler::validateInput() {
	for (int eIdx = 0; eIdx < nEvents; eIdx++) {
		Event* e = events[eIdx];

		// has room of required type and number of seats
		int requiredNSeats = e->getTotalParticipants();

		bool hasRoom = false;
		bool hasSeats = false;

		for (int rIdx = 0; rIdx < param->getRoomNumber(); rIdx++) {
			Room* r = param->getRoomsPtr()[rIdx];

			if (e->getRoomReq() == r->getType()) {
				hasRoom = true;
				if (r->getSeats() >= requiredNSeats) hasSeats = true;
			}
		}

		if (!hasRoom) {
			error("Invalid Input: room of type (" + roomTypeToString(e->getRoomReq()) +
				") required for event (" + e->strRepr() + ") was not given.\n");
		}
		if (!hasSeats) {
			error("Invalid Input: room of size (" + to_string(requiredNSeats) +
				") and type required for event (" + e->strRepr() + ") was not given.\n");
		}

	}
	return 0; // TODO: error code
}

void Scheduler::error(string errMes, bool isCritical) {
	*errorStream << errMes << endl;

	if (isCritical) {
		throw exception(errMes.c_str());
	}
}


/********************************SCHEDULING*********************************************/
void Scheduler::generateSchedule(int shuffleSeed) {
	Event** eCopy = new Event* [nEvents];
	for (int i = 0; i < nEvents; i++) {
		eCopy[i] = events[i];
	}

	std::srand(shuffleSeed);
	std::random_shuffle(eCopy, eCopy + nEvents);

	for (int i = 0; i < nEvents; i++) {
		Event* e = events[i];
		int allocCode = allocateEvent(e);
	}


	// write to file
	ofstream file;
	cout << "Output file name: " << "Output\\Output Schedule" + to_string(shuffleSeed) + ".csv\n";
	file.open("Output\\Output Schedule" + to_string(shuffleSeed) + ".csv");
	if (!file.is_open()) {
		error("could not open output file", true);
	}

	tsm->print(file);
	file.close();

	delete tsm;
	tsm = new TimeSlotManager(param->getRoomsPtr(), param->getRoomNumber(), param->getOph());

}

void Scheduler::getDailyScoreForEvent(Event* e, int resArrayPtr[7]) {
	for (int attIdx = 0; attIdx < e->getCurrentAttCount(); attIdx++) {
		Attendant* att = e->getAttendatnsPtr()[attIdx];

		for (int day = 0; day < 7; day++) {
			resArrayPtr[day] = 0;
			if (att->getParticipantCount() == 0) {
				// instructor
				resArrayPtr[day] += att->getNBusyHoursOnDay(day) * param->getInstructorTimeCostMultiplier();
			} else {
				// student
				resArrayPtr[day] += att->getNBusyHoursOnDay(day) * param->getStudentTimeCostMultiplier();
			}

		}
	}
}

int Scheduler::allocateEvent(Event* e) {
	static int dayOrderBugFix = 0;
	Attendant** atts = (e->getAttendatnsPtr());
	cout << "Allocating " << e->getName() << endl;


	int daysRequired = divide_int_round_up(e->getHours(), param->getMaxClassLength());
	if (daysRequired > param->getOph().getNWorkDays()) {
		cout << param->getOph().getNWorkDays() << "  " << daysRequired << "\n";
		error("An event \"" + e->getName() + "\" requires more days for classes due " \
			"to max_class_len limitation of " + to_string(param->getMaxClassLength()) + " hours.");
	}

	int hoursAllocated = 0;
	// looks for long slots first, if not found, reduces the target
	int targetClassLenght = min(e->getHours(), param->getMaxClassLength());
	for (; targetClassLenght > 0; --targetClassLenght) {
		if (hoursAllocated >= e->getHours()) break;
		cout << "\ttargenClassLen = " << targetClassLenght << endl;

		// min stops from overshoting required hours per week
		int thisClassLength = min(targetClassLenght, e->getHours() - hoursAllocated);

		// used for prioritizing least busy days of the week
		int dailyScoresForEvent[7];
		getDailyScoreForEvent(e, dailyScoresForEvent);

		// goes over all days of the week and tries to find slots with enough consecutive hours
		for (int dayPriority = 0; dayPriority < 7; dayPriority++) {
			if (hoursAllocated >= e->getHours()) break;

			getDailyScoreForEvent(e, dailyScoresForEvent);
			int dayOfWeek = getNthSmallesIndex(dayPriority, dailyScoresForEvent);

			dayOfWeek = (dayOrderBugFix++ + dayOfWeek) % 7;

			// reduces priority for this day for next iter
			dailyScoresForEvent[dayOfWeek] = INT_MAX;

			cout << "\t\ttrying " << daysOfWeekToStr(intToDaysOfWeek(dayOfWeek));


			if (param->getOph().getTotalHoursOnDay(dayOfWeek) < thisClassLength) {
				cout << " operational hours\n";
				continue;
			}
			// try to find slots
			std::pair<int, int> slotIdx = tsm->getFreeSlotIdxOnDay(e->getRoomReq(),
				(const Attendant**)atts, e->getCurrentAttCount(), dayOfWeek, thisClassLength);

			if (slotIdx.first < 0 || slotIdx.second < 0) {
				cout << " slots not found\n";
				continue;
			}
			cout << endl;
			// succedes to find the slot
			for (int hour = 0; hour < thisClassLength; hour++) {
				TimeSlot* ts = tsm->getTimeSlot(slotIdx.first + hour, slotIdx.second);

				cout << "\t\t\t allocating to " << daysOfWeekToStr(ts->getDay()) <<
					" " << to_string(ts->getStartTime()) << " in room " <<
					ts->getRoom()->getName() << endl;

				for (int i = 0; i < e->getCurrentAttCount(); i++) {
					ts->appendUniqueAttendant(atts[i]);
				}
				ts->setName(e->getName());

				hoursAllocated += thisClassLength;
			}

		}
	}

	if (hoursAllocated < e->getHours()) {
		error(e->getName() + " WAS NOT ALLOCATED!!!\n");
		return 0;
	}
	
	return 1;
}

int Scheduler::getBestDayForClass(Event* e, int nthBest) {
	cout << "Method Scheduler::getBestDayForClass is not implemented!" << endl;
	// TODO: implement Scheduler::getBestDayForClass

	int temp[7] = { 0, 0, 0, 0, 0, 0, 0 };
	
	getDailyScoreForEvent(e, temp);
	
	return -1;

}


/********************************NON-MEMBERS********************************************/

int getNthSmallesIndex(int nth, const int temp[]) {
	int order[7] = { 0, 1, 2, 3, 4, 5, 6 };

	for (int n = 0; n <= nth; n++) {
		for (int idx = n; idx < 7; idx++) {
			if (temp[order[idx]] > order[n]) {
				order[n] = idx;
			}
		}
	}

	return order[nth % 7];

}

int findAttendantInArray(string name, int partCount, Attendant* bufPtr[], int bufSize) {
	for (int i = 0; i < bufSize; i++) {
		bool isNameMatch = bufPtr[i]->getName() == name;
		bool isPartCountMatch = bufPtr[i]->getParticipantCount() == partCount;

		if (isNameMatch && isPartCountMatch) {
			return i;
		}
	}

	return -1;
}
