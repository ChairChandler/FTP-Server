#include <QtTest>
#include "test.h"
#pragma GCC diagnostic ignored "-Wpadded"


#include "accountdatabase.h"

class AccountDatabaseTest : public QObject
{
    Q_OBJECT
    using DB = AccountDatabase;
    DB *db;
    const QString ACCOUNT_NAME = "NAME";
    const int USER_SOCKET_ON_SERVER_SIDE_COMMAND_CHANNEL = 1;

public:
    AccountDatabaseTest();
    ~AccountDatabaseTest();

private slots:
    void init();
    void test_getAccountInfo_byName_accountWasntCreated_resultAccountNotFoundException();
    void test_getAccountInfo_bySocket_accountWasntCreated_resultAccountNotFoundException();
    void test_setAccountInfo_accountWasntCreated_resultAccountNotFoundException();
    void test_addAccountInfo_accountWasntCreated_resultAccountCreated();
    void test_addAccountInfo_accountCreated_resultAccountExistsException();
    void test_getAccountInfo_byName_accountCreated_resultEqualAccounts();
    void test_getAccountInfo_bySocket_accountCreated_resultEqualAccounts();
    void test_setAccountInfo_accountCreated_resultEqualAccounts();
    void test_resetDatabase_accountCreated_resultEmptyDatabase();

private:
    DB::AccountInfo getAccount();
};

AccountDatabaseTest::AccountDatabaseTest()
{
    db = &AccountDatabase::getInstance();
}

AccountDatabaseTest::~AccountDatabaseTest()
{

}

void AccountDatabaseTest::init()
{
    db->accounts.clear();
}

void AccountDatabaseTest::test_getAccountInfo_byName_accountWasntCreated_resultAccountNotFoundException()
{
    QVERIFY_EXCEPTION_THROWN(db->getAccountInfo(getAccount().name), DB::AccountNotFoundException);
}

void AccountDatabaseTest::test_getAccountInfo_bySocket_accountWasntCreated_resultAccountNotFoundException()
{
    QVERIFY_EXCEPTION_THROWN(db->getAccountInfo(getAccount().commandChannelSocket), DB::AccountNotFoundException);
}

void AccountDatabaseTest::test_setAccountInfo_accountWasntCreated_resultAccountNotFoundException()
{
    QVERIFY_EXCEPTION_THROWN(db->setAccountInfo(getAccount()), DB::AccountNotFoundException);
}

void AccountDatabaseTest::test_addAccountInfo_accountWasntCreated_resultAccountCreated()
{
    db->addAccountInfo(getAccount());
}

void AccountDatabaseTest::test_addAccountInfo_accountCreated_resultAccountExistsException()
{
    db->addAccountInfo(getAccount());
    QVERIFY_EXCEPTION_THROWN(db->addAccountInfo(getAccount()), DB::AccountExistsException);
}

void AccountDatabaseTest::test_getAccountInfo_byName_accountCreated_resultEqualAccounts()
{
    db->addAccountInfo(getAccount());
    QCOMPARE(db->getAccountInfo(ACCOUNT_NAME), getAccount());
}

void AccountDatabaseTest::test_getAccountInfo_bySocket_accountCreated_resultEqualAccounts()
{
    db->addAccountInfo(getAccount());
    QCOMPARE(db->getAccountInfo(USER_SOCKET_ON_SERVER_SIDE_COMMAND_CHANNEL), getAccount());
}

void AccountDatabaseTest::test_setAccountInfo_accountCreated_resultEqualAccounts()
{
    db->addAccountInfo(getAccount());
    DB::AccountInfo account = getAccount();
    account.dataChannelSocket = 1;
    db->setAccountInfo(account);
    QCOMPARE(db->getAccountInfo(USER_SOCKET_ON_SERVER_SIDE_COMMAND_CHANNEL), account);
}

void AccountDatabaseTest::test_resetDatabase_accountCreated_resultEmptyDatabase()
{
    db->addAccountInfo(getAccount());
    db->resetDatabase();
    QVERIFY_EXCEPTION_THROWN(db->getAccountInfo(ACCOUNT_NAME), DB::AccountNotFoundException);
}

AccountDatabase::AccountInfo AccountDatabaseTest::getAccount()
{
    DB::AccountInfo account;
    account.name = ACCOUNT_NAME;
    account.commandChannelSocket = USER_SOCKET_ON_SERVER_SIDE_COMMAND_CHANNEL;
    return account;
}

QTEST_APPLESS_MAIN(AccountDatabaseTest)

#include "tst_accountdatabasetest.moc"
