#ifndef PORTPARSER_H
#define PORTPARSER_H

#include "ftpcommand/commandparser.h"
#include "bsdsocket/bsdsocketfactory.h"

//PORT <SP> <host-port> <CRLF>
//<host-port> ::= <host-number>,<port-number>
//<host-number> ::= <number>,<number>,<number>,<number>
//<port-number> ::= <number>,<number>
//<number> ::= any decimal integer 1 through 255

/**
 * @brief Parse PORT ftp command.
 */
class PortParser: public CommandParser {

    private:
        sockaddr_in addr;
        QString ip, port;

        QString retrieveIP(QStringList &ipWithPort);
        QString retrieveNextPortPart(QStringList &addresStringList);
        uint16_t calculatePort(uint p1, uint p2);

    public:
        /**
        * @return True if parse done successfuly
        */
        virtual bool parse(const QString &input) override;
        sockaddr_in getAddr() const;
        QString getIp() const;
        QString getPort() const;
};

#endif // PORTPARSER_H
