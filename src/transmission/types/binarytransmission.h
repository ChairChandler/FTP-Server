#ifndef BINARYTRANSMISSION_H
#define BINARYTRANSMISSION_H
#include "transmission/transmission.h"
#include <QTextStream>

class BinaryTransmissionReader: public TransmissionReaderInterface {

    private:
        QFile *file;
        QTextStream *stream;
        Transmission::Buffer buff;

    public:
        virtual void init(QFile &file) override;
        virtual Transmission::Buffer& readDataPortion() override;
        virtual bool isEndOfFile() override;
        virtual void cleanUp() override;
        virtual ~BinaryTransmissionReader() override = default;
};

class BinaryTransmissionWriter: public TransmissionWriterInterface {

    private:
        QFile *file;
        QTextStream *stream;

    public:
        virtual void init(QFile &file) override;
        virtual void writeDataPortion(Transmission::Buffer& txt) override;
        virtual void cleanUp() override;
        virtual ~BinaryTransmissionWriter() override = default;
};

/**
 * @brief Send or receive file through data channel in binary chars
 */
class BinaryTransmission: private Transmission {

    private:
        BinaryTransmissionReader reader;
        BinaryTransmissionWriter writer;

    public:
       BinaryTransmission();
       virtual bool operator==(Transmission &transmission) = 0;
       virtual ~BinaryTransmission() = default;
};

#endif // BINARYTRANSMISSION_H
