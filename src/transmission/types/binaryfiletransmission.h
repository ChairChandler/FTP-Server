#ifndef BINARYFILETRANSMISSION_H
#define BINARYFILETRANSMISSION_H

#include <QDataStream>
#include "transmission/filetransmission.h"

/**
* @brief Read file in binary chars
*/
class BinaryTransmissionReader: public InterfaceTransmissionReader {

    private:
        QFile *file;
        QDataStream *stream;
        AbstractFileTransmission::ExternalBuffer buff;
        size_t buffSize;

    public:
        virtual void init(const QFile &file) override;
        virtual BufferInfo readDataPortion() override;
        virtual bool isEndOfFile() override;
        virtual void cleanUp() override;
};

/**
* @brief Write to file binary chars
*/
class BinaryTransmissionWriter: public InterfaceTransmissionWriter {

    private:
        QFile *file;
        QDataStream *stream;
        size_t buffSize;

    public:
        virtual void init(const QFile &file) override;
        virtual void writeDataPortion(BufferInfo buffer) override;
        virtual void cleanUp() override;
};

/**
 * @brief Send or receive file through data channel in binary chars
 */
class BinaryFileTransmission: public AbstractFileTransmission {

    private:
        BinaryTransmissionReader reader;
        BinaryTransmissionWriter writer;

    public:
       BinaryFileTransmission();
};

#endif // BINARYFILETRANSMISSION_H
