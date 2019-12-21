#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

#include <QString>

/**
* @brief Interface for parse ftp commands.
* @interface
*/
class CommandParser {

    public:
        /**
        * @return True if parse done successfuly
        */
        virtual bool parse(const QString &input) = 0;
        virtual ~CommandParser() = default;
};

#endif // COMMANDPARSER_H
