#ifndef FTPCOMMAND_H
#define FTPCOMMAND_H

#include <memory>
#include "account/accountdatabase.h"

/**
* @brief Abstract class for ftp command.
* @abstract Abstract class for ftp command.
*/
class AbstractFTPcommand {

    private:
        using FactoryRef = std::unique_ptr<AbstractAccountDatabaseSingletonFactory>;
        static inline auto factory = FactoryRef(new AccountDatabaseSingletonFactoryDefault);

    protected:
        AbstractFTPcommand() = default;
        /**
        * @return Default account database, or modified account database.
        */
        InterfaceAccountDatabase& getDatabase() const;

    public:
        static void setAccountDatabaseFactory(const AbstractAccountDatabaseSingletonFactory &newFactory);
        virtual void execute() = 0;
        virtual ~AbstractFTPcommand() = default;
};

#endif // FTPCOMMAND_H
