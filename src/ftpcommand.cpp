#include "ftpcommand.h"

FTPcommand::FTPcommand(): database(AccountDatabase::getInstance()) {

}

AccountDatabase &FTPcommand::getDatabase() const
{
    return database;
}

FTPcommand::~FTPcommand() {

}
