#ifndef FAKETRANSMISSIONCLASSES_H
#define FAKETRANSMISSIONCLASSES_H
#include "transmission/transmission.h"
#include <QTextStream>
#pragma GCC diagnostic ignored "-Wpadded"

class FakeTransmissionReader: public TransmissionReaderInterface {

    private:
        QFile *file;
        bool eof;
        Transmission::Buffer buff;
        static constexpr std::string_view EXAMPLE_TEXT = "FIRST_TEXT";
    public:

        static QString getSentText();
        virtual void init(QFile &file) override;
        virtual Transmission::Buffer& readDataPortion() override;
        virtual bool isEndOfFile() override;
        virtual void cleanUp() override;
        virtual ~FakeTransmissionReader() override = default;
};

class FakeTransmissionWriter: public TransmissionWriterInterface {

    private:
        QFile *file;
        QString recvData;

    public:
        QString getRecvData() const;
        virtual void init(QFile &file) override;
        virtual void writeDataPortion(Transmission::Buffer& txt) override;
        virtual void cleanUp() override;
        virtual ~FakeTransmissionWriter() override = default;
};

class FakeClass: public Transmission {

    private:
        FakeTransmissionReader reader;
        FakeTransmissionWriter writer;

    public:
        FakeClass();
        QString getRecvData() const;
        virtual ~FakeClass() override = default;
        virtual bool operator==(Transmission &t) override;
};

#endif // FAKETRANSMISSIONCLASSES_H
