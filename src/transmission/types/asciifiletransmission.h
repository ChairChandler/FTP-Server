#ifndef ASCIIFILETRANSMISSION_H
#define ASCIIFILETRANSMISSION_H

#include <QTextStream>
#include "transmission/filetransmission.h"

/**
* @brief Read file in ASCII chars
*/
class AsciiTransmissionReader: public InterfaceTransmissionReader {

    private:
        QFile *file;
        QTextStream *stream;
        AbstractFileTransmission::ExternalBuffer buff;

    public:
        virtual void init(const QFile &file) override;
        virtual BufferInfo readDataPortion() override;
        virtual bool isEndOfFile() override;
        virtual void cleanUp() override;
};

/**
* @brief Write to file ASCII chars
*/
class AsciiTransmissionWriter: public InterfaceTransmissionWriter {

    private:
        QFile *file;
        QTextStream *stream;

    public:
        virtual void init(const QFile &file) override;
        virtual void writeDataPortion(BufferInfo info) override;
        virtual void cleanUp() override;
};

/**
 * @brief Send or receive file through data channel in ASCII chars
 */
class AsciiFileTransmission: public AbstractFileTransmission {

    private:
        AsciiTransmissionReader reader;
        AsciiTransmissionWriter writer;

    public:
        AsciiFileTransmission();
};

#endif // ASCIIFILETRANSMISSION_H
