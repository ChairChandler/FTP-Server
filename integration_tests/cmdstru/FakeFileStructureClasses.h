#ifndef FAKEFILESTRUCTURECLASSES_H
#define FAKEFILESTRUCTURECLASSES_H

#include "structure/structure.h"

class FakeClassA: public Structure {
    virtual bool operator==(Structure &t) override {
        if(dynamic_cast<FakeClassA*>(&t)) {
            return true;
        } else {
            return false;
        }
    }
};

class FakeClassB: public Structure {
    virtual bool operator==(Structure &t) override {
        if(dynamic_cast<FakeClassB*>(&t)) {
            return true;
        } else {
            return false;
        }
    }
};

#endif // FAKEFILESTRUCTURECLASSES_H
