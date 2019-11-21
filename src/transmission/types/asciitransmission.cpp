#include "asciitransmission.h"

void AsciiTransmissionReader::init(QFile &file) {
    this->file = &file;
    using Flags = QFile::OpenModeFlag;
    if(!file.open(QFile::OpenMode(Flags::Text|Flags::ReadOnly))) {
        throw FileOpeningException();
    } else {
        stream = new QTextStream(&file);
    }
}

TransmissionFileAccessInterface::BufferInfo AsciiTransmissionReader::readDataPortion() {
    QString line = stream->read(static_cast<long long>(buff.size()));
    std::copy(line.begin(), line.end(), buff.begin());
    data_size buffSize = static_cast<size_t>(line.size());

    return BufferInfo(buff, buffSize);
}

bool AsciiTransmissionReader::isEndOfFile() {
    return file->atEnd();
}

void AsciiTransmissionReader::cleanUp() {
    file->close();
}

void AsciiTransmissionWriter::init(QFile &file) {
    this->file = &file;
    using Flags = QFile::OpenModeFlag;
    file.open(QFile::OpenMode(Flags::Text|Flags::WriteOnly));
    stream = new QTextStream(&file);
}

void AsciiTransmissionWriter::writeDataPortion(BufferInfo info) {
    QByteArray array(static_cast<int>(info.second), '\0');

    for(int i=0; i<static_cast<int>(info.second); i++) {
        ulong index = static_cast<unsigned long>(i);
        array[i] = info.first[index].toLatin1();
    }

    *stream << array;
}

void AsciiTransmissionWriter::cleanUp() {
    file->close();
}

AsciiTransmission::AsciiTransmission(): Transmission(reader, writer) {

}

bool AsciiTransmission::operator==(Transmission &transmission) {
    if(dynamic_cast<AsciiTransmission*>(&transmission)) {
        return true;
    } else {
        return false;
    }
}
