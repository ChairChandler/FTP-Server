#ifndef FTPCOMMAND_H
#define FTPCOMMAND_H
#include "accountdatabase.h"

class FTPcommand {

    private:
        AccountDatabase &database;

    protected:
        FTPcommand();
        AccountDatabase& getDatabase() const;

    public:
        virtual void execute() = 0;
        virtual ~FTPcommand() = default;
};

enum CommandList {

    //Requirement for working properly
    USER,//Minimum cmds
    QUIT,
    PORT,
    TYPE,
    MODE,
    STRU,
    RETR,//Minimum cmds
    STOR,//Minimum cmds
    NOOP,

    //Additional commands
    RMD,//Minimum cmds
    MKD,//Minimum cmds
    CWD,
    CDUP,
    PWD,
    LIST,
    HELP
};

#endif // FTPCOMMAND_H
