#include "FakeTransmissionClasses.h"
#pragma GCC diagnostic ignored "-Wuninitialized"

FakeClassA::FakeClassA(): Transmission(*reader, *writer) {

}

bool FakeClassA::operator==(Transmission &t) {
    if(dynamic_cast<FakeClassA*>(&t)) {
        return true;
    } else {
        return false;
    }
}

FakeClassB::FakeClassB(): Transmission(*reader, *writer) {

}

bool FakeClassB::operator==(Transmission &t) {
    if(dynamic_cast<FakeClassB*>(&t)) {
        return true;
    } else {
        return false;
    }
}
