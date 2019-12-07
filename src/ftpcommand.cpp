#include "ftpcommand.h"

FTPcommand::FTPcommand() {

}

AccountDatabase& FTPcommand::getDatabase() const {
    return factory->getInstance();
}

void FTPcommand::setAccountDatabaseFactory(const AccountDatabaseSingletonFactory &newFactory) {
    factory = FactoryRef(newFactory.clone());
}
