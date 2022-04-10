#pragma once
#include "utils.h"
#include "OpHours.h"

class Parameters {
private:
	OpHours oph;
public:
	Parameters();
	~Parameters();

    OpHours getOph() const;
    void setOph(OpHours oph);

};