#include <QtTest>


#include "accountdatabase.h"

#pragma GCC diagnostic ignored "-Wpadded"
class AccountDatabaseTest : public QObject
{
    Q_OBJECT
    using DB = AccountDatabase;
    DB *db;
    DB::AccountInfo account;
    const QString ACCOUNT_NAME = "NAME";
    const int COMMAND_STREAM_SOCKET = 1;

public:
    AccountDatabaseTest();
    ~AccountDatabaseTest();

private slots:
    void test_getAccountInfo_byName_accountWasntCreated_resultThrow();
    void test_getAccountInfo_bySocket_accountWasntCreated_resultThrow();
    void test_setAccountInfo_accountWasntCreated_resultThrow();
    void test_addAccountInfo_accountWasntCreated_resultPass();
    void test_addAccountInfo_accountCreated_resultThrow();
    void test_getAccountInfo_byName_accountCreated_resultEqualAccounts();
    void test_getAccountInfo_bySocket_accountCreated_resultEqualAccounts();
    void test_setAccountInfo_accountCreated_resultEqualAccounts();
};

AccountDatabaseTest::AccountDatabaseTest()
{
    account.name = ACCOUNT_NAME;
    account.commandStreamSocket = COMMAND_STREAM_SOCKET;
    db = &AccountDatabase::getInstance();
}

AccountDatabaseTest::~AccountDatabaseTest()
{

}

void AccountDatabaseTest::test_getAccountInfo_byName_accountWasntCreated_resultThrow()
{
    QVERIFY_EXCEPTION_THROWN(db->getAccountInfo(""), DB::AccountNotFoundException);
}

void AccountDatabaseTest::test_getAccountInfo_bySocket_accountWasntCreated_resultThrow()
{
    QVERIFY_EXCEPTION_THROWN(db->getAccountInfo(0), DB::AccountNotFoundException);
}

void AccountDatabaseTest::test_setAccountInfo_accountWasntCreated_resultThrow()
{
    QVERIFY_EXCEPTION_THROWN(db->setAccountInfo(DB::AccountInfo()), DB::AccountNotFoundException);
}

void AccountDatabaseTest::test_addAccountInfo_accountWasntCreated_resultPass()
{
    db->addAccountInfo(account);
}

void AccountDatabaseTest::test_addAccountInfo_accountCreated_resultThrow()
{
    QVERIFY_EXCEPTION_THROWN(db->addAccountInfo(account);, DB::AccountExistsException);
}

void AccountDatabaseTest::test_getAccountInfo_byName_accountCreated_resultEqualAccounts()
{
    QCOMPARE(db->getAccountInfo(ACCOUNT_NAME), account);
}

void AccountDatabaseTest::test_getAccountInfo_bySocket_accountCreated_resultEqualAccounts()
{
    QCOMPARE(db->getAccountInfo(COMMAND_STREAM_SOCKET), account);
}

void AccountDatabaseTest::test_setAccountInfo_accountCreated_resultEqualAccounts()
{
    account.dataStreamSocket = 1;
    db->setAccountInfo(account);
    QCOMPARE(db->getAccountInfo(COMMAND_STREAM_SOCKET), account);
}

QTEST_APPLESS_MAIN(AccountDatabaseTest)

#include "tst_accountdatabasetest.moc"
