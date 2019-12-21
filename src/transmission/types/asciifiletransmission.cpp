#include "asciifiletransmission.h"

void AsciiTransmissionReader::init(const QFile &file) {
    this->file = &const_cast<QFile&>(file);
    using Flags = QFile::OpenModeFlag;

    if(!this->file->open(QFile::OpenMode(Flags::Text|Flags::ReadOnly))) {
        throw FileOpeningException();
    } else {
        stream = new QTextStream(this->file);
    }
}

InterfaceTransmissionFileAccess::BufferInfo AsciiTransmissionReader::readDataPortion() {
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

void AsciiTransmissionWriter::init(const QFile &file) {
    this->file = &const_cast<QFile&>(file);
    using Flags = QFile::OpenModeFlag;

    if(!this->file->open(QFile::OpenMode(Flags::Text|Flags::WriteOnly))) {
        throw FileOpeningException();
    } else {
        stream = new QTextStream(this->file);
    }
}

void AsciiTransmissionWriter::writeDataPortion(BufferInfo info) {
    int iSize = static_cast<int>(info.second);

    QByteArray array(iSize, '\0');

    for(int i=0; i<iSize; i++) {
        ulong index = static_cast<unsigned long>(i);
        array[i] = info.first[index].toLatin1();
    }

    *stream << array;
}

void AsciiTransmissionWriter::cleanUp() {
    file->close();
}

AsciiFileTransmission::AsciiFileTransmission(): AbstractFileTransmission(reader, writer) {

}
