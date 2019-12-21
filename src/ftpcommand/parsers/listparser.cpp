#include "listparser.h"
#include <QRegExp>
#include <QStringList>

QString ListParser::getPath() const {
    return path;
}

bool ListParser::parse(const QString &input) {
    QRegExp r("^LIST( .+)?$");
    if(r.indexIn(input) > -1) {
        auto list = input.split(' ');
        list.removeFirst();
        path = list.join('_');
        return true;
    } else {
        return false;
    }
}
