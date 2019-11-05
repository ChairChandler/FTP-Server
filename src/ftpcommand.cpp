#include "ftpcommand.h"

FTPcommand::FTPcommand(): database(AccountDatabase::getInstance()) {

}

AccountDatabase &FTPcommand::getDatabase()
{
    return database;
}

FTPcommand::~FTPcommand() {

}
