#include "FTPservice.h"

bool operator<(const NamedException &, const NamedException &) {
    return true;
}

AbstractFTPservice::AbstractFTPservice(AbstractFTPcommand * const newCmd): cmd(newCmd) {

}

AbstractFTPservice::AbstractFTPservice(AbstractFTPcommand * const newCmd, AbstractFTPservice::ExceptionReplyCode newReplyCodes): cmd(newCmd), replyCodes(newReplyCodes) {

}

QString AbstractFTPservice::parseReplyBefore(AbstractFTPcommand * const) {
    return "";
}

QString AbstractFTPservice::parseReplyAfter(AbstractFTPcommand * const) {
    return ReplyCodes::C200.toString();
}

void AbstractFTPservice::start() {
    try{
        errorMsg.clear(); //clear error help to run service again (?)
        cmd->execute();
    } catch(NamedException &e) {
        for(auto excName: replyCodes.keys()) { //find register exception and return assigned reply to it
            if(excName.name() == e.name()) {
                errorMsg =  QString("%1 %2").arg(replyCodes[excName]->getId()).arg(e.what());
            }
        }

        throw std::runtime_error("Unhandled service exception.");

    } catch(std::exception) {
        throw std::runtime_error("Unhandled service exception.");
    }
}

QString AbstractFTPservice::replyBefore() {
    return parseReplyBefore(cmd.get());
}

QString AbstractFTPservice::replyAfter() {
    return errorMsg.isEmpty() ? parseReplyAfter(cmd.get()) : errorMsg;
}
