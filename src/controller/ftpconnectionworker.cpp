#include "ftpconnectionworker.h"
#include <QTimer>
#include <features.h>
#include "xmloutput/xmlcout.h"
#include "xmloutput/xmlexception.h"

#include "services/srv/portservice.h"
#include "services/srv/pwdservice.h"
#include "services/srv/typeservice.h"
#include "services/srv/listservice.h"
#include "services/srv/cwdservice.h"
#include "services/srv/cdupservice.h"
#include "services/srv/mkdservice.h"
#include "services/srv/rmdservice.h"
#include "services/srv/storservice.h"
#include "services/srv/retrservice.h"

#include "ftpcommand/parsers/portparser.h"
#include "ftpcommand/parsers/pwdparser.h"
#include "ftpcommand/parsers/typeparser.h"
#include "ftpcommand/parsers/listparser.h"
#include "ftpcommand/parsers/cwdparser.h"
#include "ftpcommand/parsers/cdupparser.h"
#include "ftpcommand/parsers/mkdparser.h"
#include "ftpcommand/parsers/rmdparser.h"
#include "ftpcommand/parsers/storparser.h"
#include "ftpcommand/parsers/retrparser.h"

FTPconnectionWorker::FTPconnectionWorker(int clientCommandChannel): clientCommandChannel(clientCommandChannel) {

}

FTPconnectionWorker::~FTPconnectionWorker() {
    emit done(clientCommandChannel);
}

void FTPconnectionWorker::run() {
    forever {
        try{
            QString cmd = receiveCommandString();

            //client like FileZilla send twice empty string to signalize end of connection
            if(cmd.isEmpty()) {
                break;
            }

            AbstractFTPservice * const srv = createService(cmd);

            if(!handleService(srv)) {
                break;
            }
        } catch(XmlException &e) {
            e.print();
            break;
        } catch(std::exception &e) {
            XmlException("server").
                    key("phase").value("run").
                    key("status").value("error").
                    key("socket").value(QString::number(clientCommandChannel)).
                    key("what").value(e.what()).
                    end().
                    print();
            break;
        }
    }
}

void FTPconnectionWorker::setBsdSocketFactory(const InterfaceBsdSocketFactory &newFactory) {
    bsdSocket = FactoryRef(newFactory.clone());
}

void FTPconnectionWorker::setTimeoutMs(int value) {
    timeoutMs = value;
}

QString FTPconnectionWorker::receiveCommandString() {
    QByteArray array(1024, '\0');
    if(bsdSocket->read(clientCommandChannel, array.data(), static_cast<size_t>(array.size())) == -1) {
        throw XmlException("server").
                key("phase").value("run").
                key("status").value("error").
                key("socket").value(QString::number(clientCommandChannel)).
                key("what").value("Connection closed during receiving cmd.").
                end();
    }

    //clients like FileZilla append this string to the command
    return QString(array).remove("\r\n");
}

AbstractFTPservice* FTPconnectionWorker::createService(const QString &cmd) {
    AbstractFTPservice *s = nullptr;

    //if command parse had been done successfully then run service assigned to it
    if(PortParser port; port.parse(cmd)) {
        s = new PortService(clientCommandChannel, port.getAddr());
    } else if(PwdParser pwd; pwd.parse(cmd)) {
        s = new PwdService(clientCommandChannel);
    } else if(TypeParser type; type.parse(cmd)) {
        s = new TypeService(clientCommandChannel, type.getType());
    } else if(ListParser list; list.parse(cmd)) {
        s = new ListService(clientCommandChannel, list.getPath());
    } else if(CwdParser cwd; cwd.parse(cmd)) {
        s = new CwdService(clientCommandChannel, cwd.getPath());
    } else if(CdupParser cdup; cdup.parse(cmd)) {
        s = new CdupService(clientCommandChannel);
    } else if(MkdParser mkd; mkd.parse(cmd)) {
        s = new MkdService(clientCommandChannel, mkd.getPath());
    } else if(RmdParser rmd; rmd.parse(cmd)) {
        s = new RmdService(clientCommandChannel, rmd.getPath());
    } else if(StorParser stor; stor.parse(cmd)) {
        s = new StorService(clientCommandChannel, stor.getFilename());
    } else if(RetrParser retr; retr.parse(cmd)) {
        s = new RetrService(clientCommandChannel, retr.getFilename());
    }

    //if could not parse command properly
    if(!s) {
        XmlCout("server").
                key("phase").value("run").
                key("status").value("warning").
                key("socket").value(QString::number(clientCommandChannel)).
                key("what").value("Invalid command.").
                key("cmd").value(cmd);
    } else {
        XmlCout("server").
                key("phase").value("run").
                key("socket").value(QString::number(clientCommandChannel)).
                key("cmd").value(cmd);
    }

    return s;
}

bool FTPconnectionWorker::waitForSentReply(const QString &message) {
    bool success = false, retry = true;
    QTimer timer;

    //stop trying send reply after timeout
    timer.singleShot(timeoutMs, this, [&retry](){retry = false;});

    do{
        if(isConnection() && sendReplyMessage(message)) {
            XmlCout("server").
                    key("phase").value("run").
                    key("socket").value(QString::number(clientCommandChannel)).
                    key("reply").value(message);

            success = true;
            break;
        }
    }while(retry);

    return success;
}

bool FTPconnectionWorker::sendReplyMessage(const QString &message) {
    QByteArray array = message.toUtf8() + '\r';
    return bsdSocket->write(clientCommandChannel, array.data(), static_cast<size_t>(array.size())) == array.size();
}

bool FTPconnectionWorker::isConnection() {
    char error;
    socklen_t len = sizeof(error);
    int retval = bsdSocket->getsockopt(clientCommandChannel, SOL_SOCKET, SO_ERROR, &error, &len);

    if (retval) {
        return false;
    } else {
        return true;
    }
}

bool FTPconnectionWorker::handleResponse(const QString &response) {
    if(!waitForSentReply(response)) {
        printError();
        return false;
    } else {
        return true;
    }
}

void FTPconnectionWorker::printError() {
    sockaddr_in addr = db.getAccountInfo(clientCommandChannel).getCommandChannelAddress();
    char buff[64] = "";
    inet_ntop(addr.sin_family, &addr.sin_addr, buff, sizeof(buff));

    QString ip(buff);
    XmlCout("server").
            key("phase").value("run").
            key("status").value("error").
            key("socket").value(QString::number(clientCommandChannel)).
            key("what").value("Cannot send reply.").
            key("ip").value(ip.isEmpty()? "Unknown" : ip);
}

bool FTPconnectionWorker::handleService(AbstractFTPservice * const service) {
    QString response;

    //if service is not null
    if(service) {
        response = service->replyBefore();
        if(/*!response.isEmpty() && */!handleResponse(response)) {
            return false;
        }

        service->start();
        response = service->replyAfter();
    } else {
        response = ReplyCodes::C200.toString();
    }

    if(handleResponse(response)) {
        return true;
    } else {
        return false;
    }
}
