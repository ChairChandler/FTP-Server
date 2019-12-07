#ifndef ASCIITRANSMISSION_H
#define ASCIITRANSMISSION_H
#include "transmission/transmission.h"
#include <QTextStream>

class AsciiTransmissionReader: public TransmissionReaderInterface {

    private:
        QFile *file;
        QTextStream *stream;
        Transmission::ExternalBuffer buff;

    public:
        virtual void init(QFile &file) override;
        virtual BufferInfo readDataPortion() override;
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
        virtual void writeDataPortion(BufferInfo info) override;
        virtual void cleanUp() override;
        virtual ~AsciiTransmissionWriter() override = default;
};

/**
 * @brief Send or receive file through data channel in ASCII chars
 */
class AsciiTransmission: public Transmission {

    private:
        AsciiTransmissionReader reader;
        AsciiTransmissionWriter writer;

    public:
        AsciiTransmission();
        virtual bool operator==(Transmission &transmission) override;
        virtual ~AsciiTransmission() override = default;

        using FileOpeningException = TransmissionReaderInterface::FileOpeningException;
};

#endif // ASCIITRANSMISSION_H
