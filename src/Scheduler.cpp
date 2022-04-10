#include "Scheduler.h"
#include <algorithm>    // std::random_shuffle

Scheduler::Scheduler() {
	param = Parameters();
	for (int i = 0; i < MAX_EVENTS; ++i) {
		events[i] = NULL;
	}
	nEvents = 0;
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

void Scheduler::appendEvent(const Event& e) {
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

void Scheduler::generateSchedule(int shuffleSeed) {
	Event** eCopy = new Event* [nEvents];
	for (int i = 0; i < nEvents; i++) {
		eCopy[i] = events[i];
	}

	std::srand(shuffleSeed);
	std::random_shuffle(eCopy, eCopy + nEvents);

	for (int i = 0; i < nEvents; i++) {
		
	}

}
