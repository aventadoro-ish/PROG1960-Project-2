#include "Scheduler.h"
#include <algorithm>    // std::random_shuffle

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


	for (int i = 0; i < param.getRoomNumber(); i++) {
		std::cout << param.getRoomsPtr()[i]->getSeats() << std::endl;
	}

	for (int i = 0; i < nEvents; i++) {
		Event* e = events[i];
		const Attendant** atts = (const Attendant**)(e->getAttendatnsPtr());

		TimeSlot* ts = tsm->getFreeSlot(e->getRoomReq(), atts, e->getCurrentAttCount());
		if (ts == NULL) {
			std::cout << "tsm.getFreeSlot() returned a null pointer!" << std::endl;
		}



	}

}
