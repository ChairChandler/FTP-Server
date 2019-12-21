#include "mkdparser.h"
#include <QRegExp>
#include <QStringList>

QString MkdParser::getPath() const {
    return path;
}

bool MkdParser::parse(const QString &input) {
    QRegExp r("^MKD .+$");
    if(r.indexIn(input) > -1) {
        auto list = input.split(' ');
        list.removeFirst();
        path = list.join('_');
        return true;
    } else {
        return false;
    }
}
