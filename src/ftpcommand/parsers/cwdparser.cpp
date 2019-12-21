#include "cwdparser.h"
#include <QRegExp>
#include <QDir>
#include <QStringList>

QString CwdParser::getPath() const {
    return path;
}

bool CwdParser::parse(const QString &input) {
    QRegExp r("^CWD .+$");
    if(r.indexIn(input) > -1) {
        auto list = input.split(' ');
        list.removeFirst();
        path = list.join('_');
        return true;
    } else {
        return false;
    }
}
