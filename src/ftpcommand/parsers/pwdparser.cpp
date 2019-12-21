#include "pwdparser.h"
#include <QRegExp>

bool PwdParser::parse(const QString &input) {
    QRegExp r("^PWD$");
    if(r.indexIn(input) > -1) {
        return true;
    } else {
        return false;
    }
}
