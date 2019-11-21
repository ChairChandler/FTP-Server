#ifndef BINARYTRANSMISSION_H
#define BINARYTRANSMISSION_H
#include "transmission/transmission.h"
#include <QDataStream>

class BinaryTransmissionReader: public TransmissionReaderInterface {

    private:
        QFile *file;
        QDataStream *stream;
        Transmission::ExternalBuffer buff;
        size_t buffSize;

    public:
        virtual void init(QFile &file) override;
        virtual BufferInfo readDataPortion() override;
        virtual bool isEndOfFile() override;
        virtual void cleanUp() override;
        virtual ~BinaryTransmissionReader() override = default;
};

class BinaryTransmissionWriter: public TransmissionWriterInterface {

    private:
        QFile *file;
        QDataStream *stream;
        size_t buffSize;

    public:
        virtual void init(QFile &file) override;
        virtual void writeDataPortion(BufferInfo buffer) override;
        virtual void cleanUp() override;
        virtual ~BinaryTransmissionWriter() override = default;
};

/**
 * @brief Send or receive file through data channel in binary chars
 */
class BinaryTransmission: public Transmission {

    private:
        BinaryTransmissionReader reader;
        BinaryTransmissionWriter writer;

    public:
       BinaryTransmission();
       virtual bool operator==(Transmission &transmission) override;
       virtual ~BinaryTransmission() override = default;

       using FileOpeningException = TransmissionReaderInterface::FileOpeningException;
};

#endif // BINARYTRANSMISSION_H
