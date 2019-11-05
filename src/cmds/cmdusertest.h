#ifndef CMDUSERTEST_H
#define CMDUSERTEST_H

#include <QObject>
#include "src/accountdatabase.h"

class CmdUserTest : public QObject
{
    AccountDatabase *accountDatabase;
    Q_OBJECT
private slots:
    void initTestCase();
    void test_execute_newAccount_accountAdded();
};

#endif // CMDUSERTEST_H
