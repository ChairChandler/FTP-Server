#include "binarytransmission.h"

BinaryTransmission::BinaryTransmission() {

}

bool BinaryTransmission::operator==(Transmission &transmission) {
    if(dynamic_cast<BinaryTransmission*>(&transmission)) {
        return true;
    } else {
        return false;
    }
}
