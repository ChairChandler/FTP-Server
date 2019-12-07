#include <QtTest>
#include "fakeaccountdatabasefactory.h"
#include "fakeit.hpp"
#pragma GCC diagnostic ignored "-Wpadded"
#pragma GCC diagnostic ignored "-Wpragmas" //turn off warning about below turning warning off
#pragma GCC diagnostic ignored "-Wdisabled-macro-expansion"

#include "cmds/cmdmode.h"

using namespace fakeit;

class CmdModeTest : public QObject
{
    Q_OBJECT
    const int COMMAND_CHANNEL_SOCKET = 0;
public:
    CmdModeTest();
    ~CmdModeTest();

private slots:
    void cleanup();
    void test_execute_accountWasntCreated_resultAccountNotFoundException();
    void test_execute_accountCreated_resultModeSet();

private:
    AccountInfo createAccount();
};

CmdModeTest::CmdModeTest()
{

}

CmdModeTest::~CmdModeTest()
{

}

void CmdModeTest::cleanup()
{
    FTPcommand::setAccountDatabaseFactory(AccountDatabaseSingletonFactoryDefault());
}

void CmdModeTest::test_execute_accountWasntCreated_resultAccountNotFoundException()
{
    Mock<AccountDatabase> database;
    When(OverloadedMethod(database, getAccountInfo, AccountInfo(int))).Throw(AccountDatabase::AccountNotFoundException());

    FakeAccountDatabaseSingletonFactory::setMock(database);
    FTPcommand::setAccountDatabaseFactory(FakeAccountDatabaseSingletonFactory());

    Mock<Mode> mode;

    CmdMode cmd(COMMAND_CHANNEL_SOCKET, &mode.get());
    QVERIFY_EXCEPTION_THROWN(cmd.execute(), CmdMode::AccountNotFoundException);
}

void CmdModeTest::test_execute_accountCreated_resultModeSet()
{
    AccountInfo account;

    Mock<AccountDatabase> database;
    When(OverloadedMethod(database, getAccountInfo, AccountInfo(int))).Return(createAccount());
    When(Method(database, setAccountInfo)).Do([&account](AccountInfo acc){account = acc;});

    FakeAccountDatabaseSingletonFactory::setMock(database);
    FTPcommand::setAccountDatabaseFactory(FakeAccountDatabaseSingletonFactory());

    Mock<Mode> mode;

    CmdMode cmd(COMMAND_CHANNEL_SOCKET, &mode.get());
    cmd.execute();
    QVERIFY(&mode.get() == account.mode);
}

AccountInfo CmdModeTest::createAccount()
{
    AccountInfo acc;
    acc.commandChannelSocket = COMMAND_CHANNEL_SOCKET;
    return acc;
}

QTEST_APPLESS_MAIN(CmdModeTest)

#include "tst_cmdmodetest.moc"
