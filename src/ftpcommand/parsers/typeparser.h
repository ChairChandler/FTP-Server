#ifndef TYPEPARSER_H
#define TYPEPARSER_H
#pragma GCC diagnostic ignored "-Wpadded"

#include "ftpcommand/commandparser.h"
#include "account/accountinfo.h"

//TYPE <SP> <type-code> <CRLF>
//<type-code> ::= A [<sp> <form-code>] | I
//<form-code> ::= N | T | C

/**
 * @brief Parse TYPE ftp command.
 */
class TypeParser: public CommandParser {

    private:
        AccountInfo::TransmissionType type;

    public:
        /**
        * @return True if parse done successfuly
        */
        virtual bool parse(const QString &input) override;
        AccountInfo::TransmissionType getType() const;
};

#endif // TYPEPARSER_H
