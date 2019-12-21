#include "xmlmessage.h"

XmlMessage::XmlMessage(const QString &tag) {
    message += elementBegin + tag;
}

XmlMessage& XmlMessage::key(const QString &key) {
    message += ' ' + key;
    return *this;
}

XmlMessage& XmlMessage::value(const QString &value) {
    message += QString("='%1'").arg(value);
    return *this;
}

void XmlMessage::end() {
    message += elementEnd;
}

QString XmlMessage::getMessage() const {
    return message;
}
