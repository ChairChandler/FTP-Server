#include "rmdparser.h"
#include <QRegExp>
#include <QStringList>

QString RmdParser::getPath() const {
    return path;
}

bool RmdParser::parse(const QString &input) {
    QRegExp r("^RMD .+$");
    if(r.indexIn(input) > -1) {
        auto list = input.split(' ');
        list.removeFirst();
        path = list.join('_');
        return true;
    } else {
        return false;
    }
}
