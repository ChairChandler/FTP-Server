#ifndef TRANSMISSION_H
#define TRANSMISSION_H
#include <QFile>

class TransmissionReaderInterface;
class TransmissionWriterInterface;

class Transmission {

    private:
        static const size_t BUFF_SIZE = 1024;
        const std::array<char, 2> EOF_BYTES = {0x7F, 0x2};
        std::array<char, BUFF_SIZE> localBuff;
        TransmissionReaderInterface &reader;
        TransmissionWriterInterface &writer;


        void copyConverted(std::array<QChar, BUFF_SIZE>&, std::array<char, BUFF_SIZE>&);
        void copyConverted(std::array<char, BUFF_SIZE>&, std::array<QChar, BUFF_SIZE>&);

        bool containsEOF();
        void deleteEOF();

        size_t eofStart, eofStop;

    public:
        using Buffer = std::array<QChar, BUFF_SIZE>;

        Transmission(TransmissionReaderInterface&, TransmissionWriterInterface&);
        void send(int dataChannelSocket, QFile &file);
        void receive(int dataChannelSocket, QFile &file);
        virtual ~Transmission() = default;
        virtual bool operator==(Transmission &transmission) = 0;
};

class TransmissionFileAccessInterface {

    public:
        virtual void init(QFile &file) = 0;
        virtual void cleanUp() = 0;
        virtual ~TransmissionFileAccessInterface() = default;
};

class TransmissionReaderInterface: public TransmissionFileAccessInterface {

    public:
        virtual Transmission::Buffer& readDataPortion() = 0;
        virtual bool isEndOfFile() = 0;
        virtual ~TransmissionReaderInterface() = default;

        struct FileOpeningException: std::exception {};
};

class TransmissionWriterInterface: public TransmissionFileAccessInterface {

    public:
        virtual void writeDataPortion(Transmission::Buffer& txt) = 0;
        virtual ~TransmissionWriterInterface() = default;
};

#endif // TRANSMISSION_H
