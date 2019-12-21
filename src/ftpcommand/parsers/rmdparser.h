#ifndef RMDPARSER_H
#define RMDPARSER_H

#include "ftpcommand/commandparser.h"

//RMD  <SP> <pathname> <CRLF>
//<pathname> ::= <string>
//<string> ::= <char> | <char><string>
//<char> ::= any of the 128 ASCII characters except <CR> and <LF>

/**
 * @brief Parse RMD ftp command.
 */
class RmdParser: public CommandParser {

    private:
        QString path;

    public:
        /**
        * @return True if parse done successfuly
        */
        virtual bool parse(const QString &input) override;
        QString getPath() const;
};

#endif // RMDPARSER_H
