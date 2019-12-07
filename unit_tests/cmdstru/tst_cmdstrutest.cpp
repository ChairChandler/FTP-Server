#include <QtTest>
#include "fakeaccountdatabasefactory.h"
#include "fakeit.hpp"
#pragma GCC diagnostic ignored "-Wpadded"
#pragma GCC diagnostic ignored "-Wpragmas" //turn off warning about below turning warning off
#pragma GCC diagnostic ignored "-Wdisabled-macro-expansion"

#include "cmds/cmdstru.h"

using namespace fakeit;

class CmdStruTest : public QObject
{
    Q_OBJECT
    const int COMMAND_CHANNEL_SOCKET = 0;

public:
    CmdStruTest();
    ~CmdStruTest();

private slots:
    void cleanup();
    void test_execute_accountWasntCreated_resultAccountNotFoundException();
    void test_execute_accountCreated_resultFileStructureSet();

private:
    AccountInfo createAccount();
};

CmdStruTest::CmdStruTest()
{

}

CmdStruTest::~CmdStruTest()
{

}

void CmdStruTest::cleanup()
{
    FTPcommand::setAccountDatabaseFactory(AccountDatabaseSingletonFactoryDefault());
}

void CmdStruTest::test_execute_accountWasntCreated_resultAccountNotFoundException()
{
    Mock<AccountDatabase> database;
    When(OverloadedMethod(database, getAccountInfo, AccountInfo(int))).Throw(AccountDatabase::AccountNotFoundException());

    FakeAccountDatabaseSingletonFactory::setMock(database);
    FTPcommand::setAccountDatabaseFactory(FakeAccountDatabaseSingletonFactory());
    Mock<Structure> structure;

    CmdStru cmd(COMMAND_CHANNEL_SOCKET, &structure.get());
    QVERIFY_EXCEPTION_THROWN(cmd.execute(), CmdStru::AccountNotFoundException);
}

void CmdStruTest::test_execute_accountCreated_resultFileStructureSet()
{
    AccountInfo account;

    Mock<AccountDatabase> database;
    When(OverloadedMethod(database, getAccountInfo, AccountInfo(int))).Return(createAccount());
    When(Method(database, setAccountInfo)).Do([&account](AccountInfo acc){account = acc;});

    FakeAccountDatabaseSingletonFactory::setMock(database);
    FTPcommand::setAccountDatabaseFactory(FakeAccountDatabaseSingletonFactory());

    Mock<Structure> structure;

    CmdStru cmd(COMMAND_CHANNEL_SOCKET, &structure.get());
    cmd.execute();

    QVERIFY(&structure.get() == account.structure);
}

AccountInfo CmdStruTest::createAccount()
{
    AccountInfo acc;
    acc.commandChannelSocket = COMMAND_CHANNEL_SOCKET;
    return acc;
}

QTEST_APPLESS_MAIN(CmdStruTest)

#include "tst_cmdstrutest.moc"
