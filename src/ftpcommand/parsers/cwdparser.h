#ifndef CWDPARSER_H
#define CWDPARSER_H

#include "ftpcommand/commandparser.h"

//CWD  <SP> <pathname> <CRLF>
//<pathname> ::= <string>
//<string> ::= <char> | <char><string>
//<char> ::= any of the 128 ASCII characters except <CR> and <LF>

/**
 * @brief Parse CWD ftp command.
 */
class CwdParser: public CommandParser {

    private:
        QString path;

    public:
        /**
        * @return True if parse done successfuly
        */
        virtual bool parse(const QString &input) override;
        QString getPath() const;
};

#endif // CWDPARSER_H
