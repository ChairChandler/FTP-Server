#include "replycodes.h"

ReplyCode::ReplyCode(int replyID, QString replyMessage): id(replyID), standardMessage(replyMessage) {

}

QString ReplyCode::toString() const {
    return QString("%1 %2").arg(id).arg(standardMessage);
}

int ReplyCode::getId() const {
    return id;
}

QString ReplyCode::getStandardMessage() const {
    return standardMessage;
}
