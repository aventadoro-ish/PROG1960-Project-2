#include "Parameters.h"

Parameters::Parameters() {
    oph = OpHours();
}

Parameters::~Parameters() {

}

OpHours Parameters::getOph() const {
    return oph;
}

void Parameters::setOph(OpHours oph) {
    this->oph = oph;
}

