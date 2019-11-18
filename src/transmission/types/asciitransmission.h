#ifndef ASCIITRANSMISSION_H
#define ASCIITRANSMISSION_H
#include "src/transmission/transmission.h"
#include <QTextStream>

class AsciiTransmissionReader: public TransmissionReaderInterface {

    private:
        QFile *file;
        QTextStream *stream;
        Transmission::Buffer buff;

    public:
        virtual void init(QFile &file) override;
        virtual Transmission::Buffer& readDataPortion() override;
        virtual bool isEndOfFile() override;
        virtual void cleanUp() override;
        virtual ~AsciiTransmissionReader() override = default;
};

class AsciiTransmissionWriter: public TransmissionWriterInterface {

    private:
        QFile *file;
        QTextStream *stream;

    public:
        virtual void init(QFile &file) override;
        virtual void writeDataPortion(Transmission::Buffer& txt) override;
        virtual void cleanUp() override;
        virtual ~AsciiTransmissionWriter() override = default;
};

/**
 * @brief Send or receive file through data channel in ASCII chars
 */
class AsciiTransmission: Transmission {

    private:
        AsciiTransmissionReader reader;
        AsciiTransmissionWriter writer;

    public:
        AsciiTransmission();
        virtual bool operator==(Transmission &transmission) = 0;
        virtual ~AsciiTransmission() = default;
};

#endif // ASCIITRANSMISSION_H
