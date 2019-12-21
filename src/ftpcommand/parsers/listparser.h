#ifndef LISTPARSER_H
#define LISTPARSER_H

#include "ftpcommand/commandparser.h"

//LIST [<SP> <pathname>] <CRLF>
//<pathname> ::= <string>
//<string> ::= <char> | <char><string>
//<char> ::= any of the 128 ASCII characters except <CR> and <LF>

/**
 * @brief Parse LIST ftp command.
 */
class ListParser: public CommandParser {

    private:
        QString path;

    public:
        /**
        * @return True if parse done successfuly
        */
        virtual bool parse(const QString &input) override;
        QString getPath() const;
};

#endif // LISTPARSER_H
