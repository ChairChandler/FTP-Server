#include "filetransmission.h"
#include "ftpfilesystem/filelocker.h"
#include <QMutexLocker>

AbstractFileTransmission::AbstractFileTransmission(const InterfaceTransmissionReader &reader, const InterfaceTransmissionWriter &writer):
    reader(const_cast<InterfaceTransmissionReader&>(reader)),
    writer(const_cast<InterfaceTransmissionWriter&>(writer)) {

}

void AbstractFileTransmission::send(int dataChannelSocket, const QFile &file) {

    //if file is currently locked for modification or deletion
    if(!FileLocker::trySoftLockFile(file.fileName())) {
        throw InterfaceTransmissionFileAccess::FileOpeningException();
    }

    //file can be modified by another process or something else independent from ftp server
    try {
        reader.init(file);
    } catch (InterfaceTransmissionFileAccess::FileOpeningException &e) {
        FileLocker::hardUnLockFile(file.fileName());
        throw e;
    }

    forever {
        auto [buffer, size] = reader.readDataPortion();

        copyConverted(buffer, privateBuff);

        //if data has not been send due to error and connection is closed
        if(bsdSocketFactory->write(dataChannelSocket, privateBuff.data(), size) < 0 && !isConnection(dataChannelSocket)) {
            cleanupSend(file);
            throw FileTransmissionSendException();
        }

        if(reader.isEndOfFile()) {
            break;
        }
    }

    cleanupSend(file);
}

void AbstractFileTransmission::receive(int dataChannelSocket, const QFile &file) {

    //if file is currently locked for modification or deletion
    if(!FileLocker::tryHardLockFile(file.fileName())) {
        throw InterfaceTransmissionFileAccess::FileOpeningException();
    }

    //file can be modified by another process or something else independent from ftp server
    try {
        writer.init(file);
    } catch (InterfaceTransmissionFileAccess::FileOpeningException &e) {
        FileLocker::hardUnLockFile(file.fileName());
        throw e;
    }

    using DataTransmission = InterfaceTransmissionFileAccess;
    using data_size = DataTransmission::data_size;

    data_size receivedDataSize;
    ExternalBuffer buffer;

    forever {
        receivedDataSize = static_cast<data_size>(bsdSocketFactory->read(dataChannelSocket, privateBuff.data(), privateBuff.size()));

        if(receivedDataSize > 0) {
            copyConverted(privateBuff, buffer);

            DataTransmission::BufferInfo info(buffer, receivedDataSize);
            writer.writeDataPortion(info);

        //if not received data but connection is active
        } else if(!receivedDataSize && isConnection(dataChannelSocket)){
            break;

        //if not received data due to error or connection is closed
        } else {
            cleanupReceive(file);
            QFileInfo(file).dir().remove(file.fileName());
            throw FileTransmissionReceiveException();
        }
    }

    cleanupReceive(file);
}

bool AbstractFileTransmission::isConnection(int dataChannelSocket) {
    char error;
    socklen_t len = sizeof(error);
    int retval = bsdSocketFactory->getsockopt(dataChannelSocket, SOL_SOCKET, SO_ERROR, &error, &len);

    if (retval) {
        return false;
    } else {
        return true;
    }
}

void AbstractFileTransmission::setBsdSocketFactory(const InterfaceBsdSocketFactory &newFactory) {
    bsdSocketFactory = FactoryRef(newFactory.clone());
}

void AbstractFileTransmission::cleanupSend(const QFile &file) {
    reader.cleanUp();
    FileLocker::softUnLockFile(file.fileName());
}

void AbstractFileTransmission::cleanupReceive(const QFile &file) {
    writer.cleanUp();
    FileLocker::hardUnLockFile(file.fileName());
}

void AbstractFileTransmission::copyConverted(const ExternalBuffer &src, InternalBuffer &dst) {
    size_t i = 0;
    for(QChar c: src) {
       dst[i++] = static_cast<char>(c.unicode());
    }
}

void AbstractFileTransmission::copyConverted(const InternalBuffer &src, ExternalBuffer &dst) {
    size_t i = 0;
    for(char c: src) {
        dst[i++] = c;
    }
}

size_t AbstractFileTransmission::getBuffSize() {
    return BUFF_SIZE;
}
