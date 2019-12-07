#ifndef TRANSMISSION_H
#define TRANSMISSION_H
#pragma GCC diagnostic ignored "-Wpadded"
#include <QFile>
#include <memory>
#include "bsdsocketfactory.h"

class TransmissionFileAccessInterface;
class TransmissionReaderInterface;
class TransmissionWriterInterface;

class Transmission {

    private:
        static const size_t BUFF_SIZE = 1024;

    public:
        using InternalBuffer = std::array<char, BUFF_SIZE>;
        using ExternalBuffer = std::array<QChar, BUFF_SIZE>;

    private:
        const std::array<char, 2> EOF_BYTES = {0x7F, 0x2};
        InternalBuffer localBuff;
        TransmissionReaderInterface &reader;
        TransmissionWriterInterface &writer;
        using FactoryRef = std::unique_ptr<BsdSocketFactory>;
        static inline auto bsdSocketFactory = FactoryRef(new BsdSocketFactoryDefault);



        void copyConverted(std::array<QChar, BUFF_SIZE> &src, std::array<char, BUFF_SIZE> &dst);
        void copyConverted(std::array<char, BUFF_SIZE> &src, std::array<QChar, BUFF_SIZE> &dst);

        bool containsEOF();

        size_t eofStart, eofStop;

    public:

        static void setBsdSocketFactory(const BsdSocketFactory &newFactory);
        static size_t getBuffSize();
        Transmission(TransmissionReaderInterface&, TransmissionWriterInterface&);
        void send(int dataChannelSocket, QFile &file);
        void receive(int dataChannelSocket, QFile &file);


        virtual ~Transmission() = default;
        virtual bool operator==(Transmission &transmission) = 0;
};

class TransmissionFileAccessInterface {

    public:
        using data_size = size_t;
        using BufferInfo = QPair<Transmission::ExternalBuffer, data_size>;
        virtual void init(QFile &file) = 0;
        virtual void cleanUp() = 0;
        virtual ~TransmissionFileAccessInterface() = default;
};

class TransmissionReaderInterface: public TransmissionFileAccessInterface {

    public:
        virtual BufferInfo readDataPortion() = 0;
        virtual bool isEndOfFile() = 0;
        virtual ~TransmissionReaderInterface() = default;

        struct FileOpeningException: std::exception {};
};

class TransmissionWriterInterface: public TransmissionFileAccessInterface {

    public:
        virtual void writeDataPortion(BufferInfo info) = 0;
        virtual ~TransmissionWriterInterface() = default;
};

#endif // TRANSMISSION_H
