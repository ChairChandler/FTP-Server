#ifndef MKDPARSER_H
#define MKDPARSER_H

#include "ftpcommand/commandparser.h"

//MKD  <SP> <pathname> <CRLF>
//<pathname> ::= <string>
//<string> ::= <char> | <char><string>
//<char> ::= any of the 128 ASCII characters except <CR> and <LF>

/**
 * @brief Parse MKD ftp command.
 */
class MkdParser: public CommandParser {

    private:
        QString path;

    public:
        /**
        * @return True if parse done successfuly
        */
        virtual bool parse(const QString &input) override;
        QString getPath() const;
};

#endif // MKDPARSER_H
