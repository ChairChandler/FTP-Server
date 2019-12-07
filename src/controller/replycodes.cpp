#include "replycodes.h"
#include <QRegExp>

ReplyCode::ReplyCode(int replyID, QString replyMessage): id(replyID), standardMessage(replyMessage) {

}

ReplyCode::ReplyCode(int replyID, QString replyMessage, QList<QString> args): id(replyID), standardMessage(replyMessage) {
    for(QString val: args) {
        QRegExp r(val);
        int indx = r.indexIn(replyMessage);

        if(indx > -1) {
            keywords[val] = indx;
        } else {
            throw std::runtime_error(QString("Invalid reply keyword %0").arg(val).toUtf8());
        }
    }
}

QString ReplyCode::toString() const {
    return QString("%1 %2").arg(id).arg(standardMessage);
}

QString ReplyCode::toString(QMap<QString, QString> replacementArgs) const {
    QString str(standardMessage);
    for(QString key: replacementArgs) {
        int pos = keywords[key];
        str.replace(pos, key.size(), replacementArgs[key]);
    }

    return QString("%1 %2").arg(id).arg(str);
}

int ReplyCode::getId() const {
    return id;
}

QString ReplyCode::getStandardMessage() const {
    return standardMessage;
}
