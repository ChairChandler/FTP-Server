#include "binarytransmission.h"

void BinaryTransmissionReader::init(QFile &file) {
    this->file = &file;
    using Flags = QFile::OpenModeFlag;
    if(!file.open(QFile::OpenMode(Flags::Text|Flags::ExistingOnly))) {
        throw FileOpeningException();
    } else {
        stream = new QTextStream(&file);
    }
}

Transmission::Buffer& BinaryTransmissionReader::readDataPortion() {
    QString line = stream->read(static_cast<long long>(buff.size()));
    std::copy(line.begin(), line.end(), buff.begin());
    return buff;
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
    file.open(QFile::OpenMode(Flags::Text));
    stream = new QTextStream(&file);
}

void BinaryTransmissionWriter::writeDataPortion(Transmission::Buffer &txt) {
    *stream << txt.data();
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
