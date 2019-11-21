#include "binarytransmission.h"

void BinaryTransmissionReader::init(QFile &file) {
    this->file = &file;
    using Flags = QFile::OpenModeFlag;
    if(!file.open(QFile::OpenMode(Flags::ReadOnly))) {
        throw FileOpeningException();
    } else {
        stream = new QDataStream(&file);
        buffSize = Transmission::getBuffSize();
    }
}

TransmissionFileAccessInterface::BufferInfo BinaryTransmissionReader::readDataPortion() {
    int iSize = static_cast<int>(buffSize);

    char *data = new char[buffSize];

    data_size readBytes = static_cast<data_size>(stream->readRawData(data, iSize));
    QByteArray line(data, static_cast<int>(readBytes));
    std::copy(line.begin(), line.end(), buff.begin());

    delete[] data;
    return BufferInfo(buff, readBytes);
}

bool BinaryTransmissionReader::isEndOfFile() {
    return file->atEnd();
}

void BinaryTransmissionReader::cleanUp() {
    file->close();
}

void BinaryTransmissionWriter::init(QFile &file) {
    this->file = &file;
    using Flags = QFile::OpenModeFlag;
    file.open(QFile::OpenMode(Flags::WriteOnly));
    stream = new QDataStream(&file);
    buffSize = Transmission::getBuffSize();
}

void BinaryTransmissionWriter::writeDataPortion(BufferInfo info) {
    QByteArray array(static_cast<int>(info.second), 0);

    for(int i=0; i<static_cast<int>(info.second); i++) {
        ulong index = static_cast<unsigned long>(i);
        array[i] = info.first[index].toLatin1();
    }

    stream->writeRawData(array, static_cast<int>(info.second));
}

void BinaryTransmissionWriter::cleanUp() {
    file->close();
}

BinaryTransmission::BinaryTransmission(): Transmission(reader, writer) {

}

bool BinaryTransmission::operator==(Transmission &transmission) {
    if(dynamic_cast<BinaryTransmission*>(&transmission)) {
        return true;
    } else {
        return false;
    }
}
