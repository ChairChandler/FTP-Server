#ifndef STORPARSER_H
#define STORPARSER_H

#include "ftpcommand/commandparser.h"

//STOR <SP> <pathname> <CRLF>
//<pathname> ::= <string>
//<string> ::= <char> | <char><string>
//<char> ::= any of the 128 ASCII characters except <CR> and <LF>

/**
 * @brief Parse STOR ftp command.
 */
class StorParser: public CommandParser {

    private:
        QString fileName;

    public:
        /**
        * @return True if parse done successfuly
        */
        virtual bool parse(const QString &input) override;
        QString getFilename() const;
};

#endif // STORPARSER_H
