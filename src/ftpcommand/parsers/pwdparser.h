#ifndef PWDPARSER_H
#define PWDPARSER_H

#include "ftpcommand/commandparser.h"

//PWD  <CRLF>

/**
 * @brief Parse PWD ftp command.
 */
class PwdParser: public CommandParser {

    public:
        /**
        * @return True if parse done successfuly
        */
        virtual bool parse(const QString &input) override;
};

#endif // PWDPARSER_H
