#include "binaryfiletransmission.h"

void BinaryTransmissionReader::init(const QFile &file) {
    this->file = &const_cast<QFile&>(file);
    using Flags = QFile::OpenModeFlag;

    if(!this->file->open(QFile::OpenMode(Flags::ReadOnly))) {
        throw FileOpeningException();
    } else {
        stream = new QDataStream(this->file);
        buffSize = AbstractFileTransmission::getBuffSize(); //size of bsd socket transmission buffer
    }
}

InterfaceTransmissionFileAccess::BufferInfo BinaryTransmissionReader::readDataPortion() {
    int iSize = static_cast<int>(buffSize);

    QByteArray charBuff(iSize, '\0');

    data_size readBytes = static_cast<data_size>(stream->readRawData(charBuff.data(), iSize));
    QByteArray line(charBuff.data(), static_cast<int>(readBytes));
    std::copy(line.begin(), line.end(), buff.begin());

    return BufferInfo(buff, readBytes);
}

bool BinaryTransmissionReader::isEndOfFile() {
    return file->atEnd();
}

void BinaryTransmissionReader::cleanUp() {
    file->close();
}

void BinaryTransmissionWriter::init(const QFile &file) {
    this->file = &const_cast<QFile&>(file);
    using Flags = QFile::OpenModeFlag;

    if(!this->file->open(QFile::OpenMode(Flags::WriteOnly))) {
        throw FileOpeningException();
    } else {
        stream = new QDataStream(this->file);
        buffSize = AbstractFileTransmission::getBuffSize();
    }
}

void BinaryTransmissionWriter::writeDataPortion(BufferInfo info) {
    int iSize = static_cast<int>(info.second);

    QByteArray array(iSize, 0);

    for(int i=0; i<iSize; i++) {
        ulong index = static_cast<unsigned long>(i);
        array[i] = static_cast<char>(info.first[index].unicode());
    }

    stream->writeRawData(array, iSize);
}

void BinaryTransmissionWriter::cleanUp() {
    file->close();
}

BinaryFileTransmission::BinaryFileTransmission(): AbstractFileTransmission(reader, writer) {

}
