#ifndef FTPCOMMAND_H
#define FTPCOMMAND_H
#include "accountdatabase.h"
#include <memory>

class FTPcommand {

    private:
        using FactoryRef = std::unique_ptr<AccountDatabaseSingletonFactory>;
        static inline auto factory = FactoryRef(new AccountDatabaseSingletonFactoryDefault);

    protected:
        FTPcommand();
        AccountDatabase& getDatabase() const;

    public:
        static void setAccountDatabaseFactory(const AccountDatabaseSingletonFactory &newFactory);
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
    LIST
};

#endif // FTPCOMMAND_H
