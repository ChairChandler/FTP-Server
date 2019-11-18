#include "FakeTransmissionClasses.h"
#include <QtGlobal>

QString FakeTransmissionReader::getSentText() {
    return EXAMPLE_TEXT.data();
}

void FakeTransmissionReader::init(QFile &file) {
    using Flags = QFile::OpenModeFlag;
    if(!file.open(QFile::OpenMode(Flags::ReadOnly|Flags::ExistingOnly|Flags::Text))) {
        throw FileOpeningException();
    } else {
        this->file = &file;
    }
}

Transmission::Buffer& FakeTransmissionReader::readDataPortion() {
    std::copy(EXAMPLE_TEXT.begin(), EXAMPLE_TEXT.end(), buff.begin());
    eof = true;

    return buff;
}

bool FakeTransmissionReader::isEndOfFile() {
    return eof;
}

void FakeTransmissionReader::cleanUp() {
    file->close();
}

FakeClass::FakeClass(): Transmission(reader, writer) {

}

QString FakeClass::getRecvData() const {
    return writer.getRecvData();
}

QString FakeTransmissionWriter::getRecvData() const {
    return recvData;
}

void FakeTransmissionWriter::init(QFile &file) {
    using Flags = QFile::OpenModeFlag;
    file.open(QFile::OpenMode(Flags::WriteOnly|Flags::Text));
    this->file = &file;
}

void FakeTransmissionWriter::writeDataPortion(Transmission::Buffer& txt) {
    QString buff(txt.data() + '\0');
    recvData += buff;
}

void FakeTransmissionWriter::cleanUp() {
    file->close();
}

bool FakeClass::operator==(Transmission &t) {
    Q_UNUSED(t)
    return false;
}
