#include "xmlexception.h"

XmlException::XmlException(const QString &tag): XmlMessage(tag), std::runtime_error("") {

}

XmlException &XmlException::key(const QString &key) {
    XmlMessage::key(key);
    return *this;
}

XmlException &XmlException::value(const QString &value) {
    XmlMessage::value(value);
    return *this;
}

XmlException &XmlException::end() {
    XmlMessage::end();
    return *this;
}

void XmlException::turnOutputOff() {
    outputOn = false;
}

void XmlException::turnOutputOn() {
    outputOn = true;
}

void XmlException::addStream(const QTextStream &stream) {
    outStreams << const_cast<QTextStream*>(&stream);
}

const char *XmlException::what() const noexcept {
    return XmlMessage::getMessage().toLatin1();
}

void XmlException::print() {
    for(QTextStream *out: outStreams) {
        *out << what() << endl;
    }

    if(outputOn) {
        cout << what() << endl;
    }
}
