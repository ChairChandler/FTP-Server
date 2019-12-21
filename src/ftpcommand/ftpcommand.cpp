#include "ftpcommand.h"

InterfaceAccountDatabase& AbstractFTPcommand::getDatabase() const {
    return factory->getInstance();
}

void AbstractFTPcommand::setAccountDatabaseFactory(const AbstractAccountDatabaseSingletonFactory &newFactory) {
    factory = FactoryRef(newFactory.clone());
}
