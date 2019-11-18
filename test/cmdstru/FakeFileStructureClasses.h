#ifndef FAKEFILESTRUCTURECLASSES_H
#define FAKEFILESTRUCTURECLASSES_H

#include "filestructure.h"

class FakeClassA: public FileStructure {
    virtual bool operator==(FileStructure &t) override {
        if(dynamic_cast<FakeClassA*>(&t)) {
            return true;
        } else {
            return false;
        }
    }
};

class FakeClassB: public FileStructure {
    virtual bool operator==(FileStructure &t) override {
        if(dynamic_cast<FakeClassB*>(&t)) {
            return true;
        } else {
            return false;
        }
    }
};

#endif // FAKEFILESTRUCTURECLASSES_H
