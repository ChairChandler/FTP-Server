#include "xmlcout.h"

XmlCout::XmlCout(const QString &tag): XmlMessage(tag) {

}

void XmlCout::turnOutputOn() {
    outputOn = true;
}

void XmlCout::addStream(const QTextStream &stream) {
    outStreams << const_cast<QTextStream*>(&stream);
}

void XmlCout::turnOutputOff() {
    outputOn = false;
}

XmlCout::~XmlCout() {
    XmlMessage::end();
    for(QTextStream *out: outStreams) {
        *out << XmlMessage::getMessage() << endl;
    }

    if(outputOn) {
        cout << XmlMessage::getMessage() << endl;
    }
}
