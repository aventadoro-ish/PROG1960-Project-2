#include "Scheduler.h"

Scheduler::Scheduler() {
    param = Parameters();
    for (int i = 0; i < MAX_EVENTS; ++i) {
        events[i] = NULL;
    }
    nEvents = 0;
}

Scheduler::~Scheduler() {
    
}


Parameters Scheduler::getParam() const {
    return param;
}

void Scheduler::setParam(Parameters param) {
    this->param = param;
}

void Scheduler::appendEvent(const Event e) {
    if (e.getHours() <= param.getMaxClassLength()) {
        events[nEvents] = new Event;

        for (int i = 0; i < e.getCurrentAttCount(); ++i) {
            events[nEvents]->appendAttendant(*e.getAttendant(i));
        }

        events[nEvents]->setHours(e.getHours());
        events[nEvents]->setName(e.getName());
    }
}


