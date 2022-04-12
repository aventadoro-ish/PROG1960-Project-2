#include "Scheduler.h"
#include <algorithm>    // std::random_shuffle

using namespace std;


int getNthSmallesIndex(int nth, const int temp[]);
// retunrs -1 if not found
int findAttendantInArray(string name, int partCount, Attendant* bufPtr[], int bufSize);
void error(string errMes, bool isCritical = true);

Scheduler::Scheduler() {
	std::cout << "parameter-less Scheduler constructor called!!!" << std::endl;
	param = Parameters();
	for (int i = 0; i < MAX_EVENTS; ++i) {
		events[i] = NULL;
	}
	nEvents = 0;

	tsm = new TimeSlotManager(param.getRoomsPtr(), param.getRoomNumber(), param.getOph());
}

Scheduler::Scheduler(Parameters para) {
	param = para;
	for (int i = 0; i < MAX_EVENTS; ++i) {
		events[i] = NULL;
	}
	nEvents = 0;

	tsm =  new TimeSlotManager(param.getRoomsPtr(), param.getRoomNumber(), param.getOph());
}

Scheduler::~Scheduler() {
	for (int i = 0; i < nEvents; ++i) {
		delete events[i];
	}
}


Parameters Scheduler::getParam() const {
	return param;
}

void Scheduler::setParam(Parameters param) {
	this->param = param;
}

void Scheduler::appendEventSplit(const Event& e) {
	// divide round up
	int splits = (e.getHours() + param.getMaxClassLength() - 1) / param.getMaxClassLength();
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
		int thisEventHours = std::min(totalHours - hCounter, param.getMaxClassLength());
		hCounter += thisEventHours;

		events[nEvents]->setHours(thisEventHours);
		events[nEvents]->setName(e.getName());
		++nEvents;
	}
}
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

void Scheduler::generateSchedule(int shuffleSeed) {
	Event** eCopy = new Event* [nEvents];
	for (int i = 0; i < nEvents; i++) {
		eCopy[i] = events[i];
	}

	std::srand(shuffleSeed);
	std::random_shuffle(eCopy, eCopy + nEvents);

	for (int i = 0; i < nEvents; i++) {
		Event* e = events[i];
		Attendant** atts = (e->getAttendatnsPtr());
		cout << "Allocating " << e->getName() << endl;


		int daysRequired = divide_int_round_up(e->getHours(), param.getMaxClassLength());
		if (daysRequired > param.getOph().getNWorkDays()) {
			cout << param.getOph().getNWorkDays() << "  " << daysRequired << "\n";
			error("An event \"" + e->getName() + "\" requires more days for classes due " \
				"to max_class_len limitation of " + to_string(param.getMaxClassLength()) + " hours.");
		}

		int hoursAllocated = 0;
		// looks for long slots first, if not found, reduces the target
		int targetClassLenght = min(e->getHours(), param.getMaxClassLength());
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

				int dayOfWeek = getNthSmallesIndex(dayPriority, dailyScoresForEvent);
				// reduces priority for this day for next iter
				dailyScoresForEvent[dayOfWeek] = INT_MAX;

				cout << "\t\ttrying " << daysOfWeekToStr(intToDaysOfWeek(dayOfWeek));


				if (param.getOph().getTotalHoursOnDay(dayOfWeek) < thisClassLength) {
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


					// TODO: change timeslot name to that of the event
					for (int i = 0; i < e->getCurrentAttCount(); i++) {
						ts->appendUniqueAttendant(atts[i]);
					}

					hoursAllocated += thisClassLength;
				}
					
			}
		}

		if (hoursAllocated < e->getHours()) {
			cout << e->getName() << " WAS NOT ALLOCATED!!!\n";
		}




		//int dailyScoresForEvent[7];
		//getDailyScoreForEvent(e, dailyScoresForEvent);
		//
		//int daysAllocated = 0;
		//int totalHours = 0;
		//for (int dayIdx = 0; dayIdx < 7; dayIdx++) {
		//	int dayOfWeek = getNthSmallesIndex(dayIdx, dailyScoresForEvent);
		//	dailyScoresForEvent[dayOfWeek] = INT_MAX;

		//	int hours = min(e->getHours() - totalHours, param.getMaxClassLength());

		//	std::pair<int, int> p = tsm->getFreeSlotIdxOnDay(
		//		e->getRoomReq(), atts,
		//		e->getCurrentAttCount(), dayOfWeek, hours);

		//	totalHours += hours;

		//	for (int h = 0; h < hours; h++) {
		//		TimeSlot* ts = tsm->getTimeSlot(p.first + h, p.second);
		//		
		//		for (int i = 0; i < e->getCurrentAttCount(); i++) {
		//			ts->appendAttendant(*atts[i]);
		//		}

		//	}
		//	++daysAllocated;
		//	if (daysAllocated == daysRequired) {
		//		break;
		//	}

		//}
		//if (daysAllocated != daysRequired) {
		//	cout << "***";
		//}



		//int splits = (e->getHours() + param.getMaxClassLength() - 1) / param.getMaxClassLength();
		//int dayCounter = 0;
		//int thisDayHours = 0;
		//
		//for (int i = 0; i < e->getHours(); i++) {

		//	TimeSlot* ts = tsm->getFreeSlot(e->getRoomReq(), atts, e->getCurrentAttCount(), dayCounter);
		//	
		//	++thisDayHours;
		//	if (thisDayHours >= param.getMaxClassLength()) {
		//		++dayCounter;
		//		thisDayHours = 0;
		//	}

		//}
	}

	tsm->print(std::cout);

}

void Scheduler::getDailyScoreForEvent(Event* e, int resArrayPtr[7]) {
	for (int attIdx = 0; attIdx < e->getCurrentAttCount(); attIdx++) {
		Attendant* att = e->getAttendatnsPtr()[attIdx];

		for (int day = 0; day < 7; day++) {
			resArrayPtr[day] = 0;
			if (att->getParticipantCount() == 0) {
				// instructor
				resArrayPtr[day] += att->getNBusyHoursOnDay(day) * param.getInstructorTimeCostMultiplier();
			} else {
				// student
				resArrayPtr[day] += att->getNBusyHoursOnDay(day) * param.getStudentTimeCostMultiplier();
			}

		}
	}
}


int Scheduler::getBestDayForClass(Event* e, int nthBest) {
	cout << "Method Scheduler::getBestDayForClass is not implemented!" << endl;
	// TODO: implement Scheduler::getBestDayForClass

	int temp[7] = { 0, 0, 0, 0, 0, 0, 0 };
	
	getDailyScoreForEvent(e, temp);
	
	return -1;

}





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

int getNthSmallesIndex(int nth, const int temp[]) {
	//for (int i = 0; i < 7; i++) {
	//	cout << temp[i] << " ";
	//}
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


void error(string errMes, bool isCritical) {
	cout << errMes << endl;

	if (isCritical) {
		throw exception(errMes.c_str());
	}
}
