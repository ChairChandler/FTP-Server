#ifndef FAKEMODECLASSES_H
#define FAKEMODECLASSES_H

#include "mode/mode.h"

class FakeClassA: public Mode {
    virtual bool operator==(Mode &t) override {
        if(dynamic_cast<FakeClassA*>(&t)) {
            return true;
        } else {
            return false;
        }
    }
};

class FakeClassB: public Mode {
    virtual bool operator==(Mode &t) override {
        if(dynamic_cast<FakeClassB*>(&t)) {
            return true;
        } else {
            return false;
        }
    }
};

#endif // FAKEMODECLASSES_H
