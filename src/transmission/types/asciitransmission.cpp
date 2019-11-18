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

Transmission::Buffer& AsciiTransmissionReader::readDataPortion() {
    QString line = stream->read(static_cast<long long>(buff.size()));
    std::copy(line.begin(), line.end(), buff.begin());
    return buff;
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

void AsciiTransmissionWriter::writeDataPortion(Transmission::Buffer &txt) {
    *stream << txt.data();
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
