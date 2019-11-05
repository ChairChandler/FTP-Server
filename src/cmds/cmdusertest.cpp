#include "cmdusertest.h"
#include <QtTest/QTest>
#include "cmduser.h"

void CmdUserTest::initTestCase() {
    accountDatabase = &AccountDatabase::getInstance();
}

void CmdUserTest::test_execute_newAccount_accountAdded() {
    CmdUser cmdUser("Name", 0);
}


QTEST_MAIN(CmdUserTest)
