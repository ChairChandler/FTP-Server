#include "storparser.h"
#include <QRegExp>
#include <QStringList>

QString StorParser::getFilename() const {
    return fileName;
}

bool StorParser::parse(const QString &input) {
    QRegExp r("^STOR .+$");
    if(r.indexIn(input) > -1) {
        auto list = input.split(' ');
        list.removeFirst();
        fileName = list.join('_');
        return true;
    } else {
        return false;
    }
}
