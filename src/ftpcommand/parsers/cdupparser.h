#ifndef CDUPPARSER_H
#define CDUPPARSER_H

#include "ftpcommand/commandparser.h"

//CDUP <CRLF>

/**
 * @brief Parse CDUP ftp command.
 */
class CdupParser: public CommandParser {

    public:
        /**
        * @return True if parse done successfuly
        */
        virtual bool parse(const QString &input) override;
};

#endif // CDUPPARSER_H
