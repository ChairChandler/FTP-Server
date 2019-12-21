#include "typeparser.h"
#include <QRegExp>

AccountInfo::TransmissionType TypeParser::getType() const {
    return type;
}

bool TypeParser::parse(const QString &input) {
    QRegExp a("^TYPE A"), b("^TYPE I$");
    if(a.indexIn(input) > -1) {
        type = AccountInfo::TransmissionType::Ascii;
        return true;
    } else if(b.indexIn(input) > -1) {
        type = AccountInfo::TransmissionType::Binary;
        return true;
    } else {
        return false;
    }
}
