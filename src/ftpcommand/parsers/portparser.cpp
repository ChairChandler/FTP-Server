#include "portparser.h"
#include <QRegExp>
#include <QStringList>

sockaddr_in PortParser::getAddr() const {
    return addr;
}

QString PortParser::getIp() const {
    return ip;
}

QString PortParser::getPort() const {
    return port;
}


QString PortParser::retrieveIP(QStringList &addresStringList) {
    QStringList ipStringList;

    for(int i=0; i<4; i++) {
        ipStringList << addresStringList.takeAt(0);
    }
    return ipStringList.join('.');
}

QString PortParser::retrieveNextPortPart(QStringList &addresStringList) {
    return addresStringList.takeFirst();
}

uint16_t PortParser::calculatePort(uint p1, uint p2) {
    return static_cast<uint16_t>((p1 * 256) + p2);
}

bool PortParser::parse(const QString &input) {
    QRegExp t("^PORT [0-9]+,[0-9]+,[0-9]+,[0-9]+,[0-9]+,[0-9]+$");
    if(t.indexIn(input) > -1) {

        QStringList addresStringList = input.section(' ', 1).split(',');

        ip = retrieveIP(addresStringList);
        uint p1 = retrieveNextPortPart(addresStringList).toUInt();
        uint p2 = retrieveNextPortPart(addresStringList).toUInt();

        uint16_t readyPort = calculatePort(p1, p2);
        port = QString(readyPort);

        memset(&addr, 0, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_port = htons(readyPort);
        inet_pton(AF_INET, ip.toStdString().c_str(), &addr.sin_addr);

        return true;
    } else {
        return false;
    }
}
