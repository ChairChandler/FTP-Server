#include "retrparser.h"
#include <QRegExp>
#include <QStringList>

QString RetrParser::getFilename() const {
    return fileName;
}

bool RetrParser::parse(const QString &input) {
    QRegExp r("^RETR .+$");
    if(r.indexIn(input) > -1) {
        auto list = input.split(' ');
        list.removeFirst();
        fileName = list.join('_');
        return true;
    } else {
        return false;
    }
}
