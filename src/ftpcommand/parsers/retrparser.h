#ifndef RETRPARSER_H
#define RETRPARSER_H

#include "ftpcommand/commandparser.h"

//RETR <SP> <pathname> <CRLF>
//<pathname> ::= <string>
//<string> ::= <char> | <char><string>
//<char> ::= any of the 128 ASCII characters except <CR> and <LF>

/**
 * @brief Parse RETR ftp command.
 */
class RetrParser: public CommandParser {

    private:
        QString fileName;

    public:
        /**
        * @return True if parse done successfuly
        */
        virtual bool parse(const QString &input) override;
        QString getFilename() const;
};
#endif // RETRPARSER_H
