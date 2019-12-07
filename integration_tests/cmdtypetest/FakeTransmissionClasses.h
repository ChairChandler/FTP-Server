#ifndef FAKETRANSMISSIONCLASSES_H
#define FAKETRANSMISSIONCLASSES_H
#include "transmission/transmission.h"

class FakeClassA: public Transmission {

    private:
        TransmissionReaderInterface *reader;
        TransmissionWriterInterface *writer;

    public:
        FakeClassA();
        virtual ~FakeClassA() override = default;
        virtual bool operator==(Transmission &t) override;
};

class FakeClassB: public Transmission {

    private:
        TransmissionReaderInterface *reader;
        TransmissionWriterInterface *writer;

    public:
        FakeClassB();
        virtual ~FakeClassB() override = default;
        virtual bool operator==(Transmission &t) override;
};

#endif // FAKETRANSMISSIONCLASSES_H
