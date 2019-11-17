#include "asciitransmission.h"

AsciiTransmission::AsciiTransmission() {

}

bool AsciiTransmission::operator==(Transmission &transmission) {
    if(dynamic_cast<AsciiTransmission*>(&transmission)) {
        return true;
    } else {
        return false;
    }
}
