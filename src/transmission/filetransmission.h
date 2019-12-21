#ifndef FILETRANSMISSION_H
#define FILETRANSMISSION_H

#include <QFile>
#include <memory>
#include "bsdsocket/bsdsocketfactory.h"
#include "exception/namedexception.h"

class InterfaceTransmissionFileAccess;
class InterfaceTransmissionReader;
class InterfaceTransmissionWriter;

/**
* @brief Abstract class for handle low-level transmission.
* @abstract Abstract class for handle low-level transmission.
*/
class AbstractFileTransmission {

    private:
        static const size_t BUFF_SIZE = 1024;

    public:
        using InternalBuffer = std::array<char, BUFF_SIZE>; //bsd socket transmission buffer
        using ExternalBuffer = std::array<QChar, BUFF_SIZE>; //filesystem transmission buffer

    private:
        InternalBuffer privateBuff;
        InterfaceTransmissionReader &reader;
        InterfaceTransmissionWriter &writer;

        using FactoryRef = std::unique_ptr<InterfaceBsdSocketFactory>;
        static inline auto bsdSocketFactory = FactoryRef(new BsdSocketFactoryDefault);

        bool isConnection(int dataChannelSocket);

        void cleanupSend(const QFile &file);
        void cleanupReceive(const QFile &file);

        void copyConverted(const ExternalBuffer &src, InternalBuffer &dst);
        void copyConverted(const InternalBuffer &src, ExternalBuffer &dst);

    public:

        static void setBsdSocketFactory(const InterfaceBsdSocketFactory &newFactory);
        static size_t getBuffSize();

        /**
        * @param reader Interface to the transmission reader
        * @param writer Interface to the transmission writer
        */
        AbstractFileTransmission(const InterfaceTransmissionReader &reader, const InterfaceTransmissionWriter &writer);
        /**
        * @param dataChannelSocket Socket to communication with client on data channel
        * @param file File to be sent
        */
        void send(int dataChannelSocket, const QFile &file);
        /**
        * @param dataChannelSocket Socket to communication with client on data channel
        * @param file File where received data will we written
        */
        void receive(int dataChannelSocket, const QFile &file);

        virtual ~AbstractFileTransmission() = default;

        struct FileTransmissionReceiveException: public NamedException {
            virtual const char* what() const noexcept override {
                return "Cannot receive data from the user.";
            }
            virtual QString name() override {
                return "FileTransmissionReceiveException";
            }
        };

        struct FileTransmissionSendException: public NamedException {
            virtual const char* what() const noexcept override {
                return "Cannot send data to the user.";
            }
            virtual QString name() override {
                return "FileTransmissionSendException";
            }
        };
};

/**
* @interface
* @brief Transmission interface for reader and writer. Init and cleanup are call respectively before and after the transmission.
*/
class InterfaceTransmissionFileAccess {

    public:
        using data_size = size_t;
        using BufferInfo = QPair<AbstractFileTransmission::ExternalBuffer, data_size>;

        /**
        * @brief Open file
        * @param file File to be read/write
        */
        virtual void init(const QFile &file) = 0;
        /**
        * @brief Close file
        */
        virtual void cleanUp() = 0;
        virtual ~InterfaceTransmissionFileAccess() = default;

        struct FileOpeningException: public NamedException {
            virtual const char* what() const noexcept override {
                return "Cannot open file.";
            }
            virtual QString name() override {
                return "FileOpeningException";
            }
        };
};

/**
* @brief Interface for transmission reader.
* @interface
*/
class InterfaceTransmissionReader: public InterfaceTransmissionFileAccess {

    public:
        /**
        * @brief Read data from the file and write them to the buffer
        * @return Buffer with data size.
        */
        virtual BufferInfo readDataPortion() = 0;
        virtual bool isEndOfFile() = 0;
};

/**
* @brief Interface for transmission writer.
* @interface
*/
class InterfaceTransmissionWriter: public InterfaceTransmissionFileAccess {

    public:
        /**
        * @brief Read data from the buffer and write them to the file
        * @param info Buffer with data size.
        */
        virtual void writeDataPortion(BufferInfo info) = 0;
};

#endif // FILETRANSMISSION_H
