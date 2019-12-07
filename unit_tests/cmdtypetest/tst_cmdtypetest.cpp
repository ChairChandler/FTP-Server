#include <QtTest>
#include "fakeaccountdatabasefactory.h"
#include "fakeit.hpp"
#pragma GCC diagnostic ignored "-Wpadded"
#pragma GCC diagnostic ignored "-Wpragmas" //turn off warning about below turning warning off
#pragma GCC diagnostic ignored "-Wdisabled-macro-expansion"

#include "cmds/cmdtype.h"

using namespace fakeit;

class CmdTypeTest : public QObject
{
    Q_OBJECT
    const int COMMAND_CHANNEL_SOCKET = 0;
public:
    CmdTypeTest();
    ~CmdTypeTest();

private slots:
    void cleanup();
    void test_execute_accountWasntCreated_resultAccountNotFoundException();
    void test_execute_accountCreated_resultTransmissionSet();

private:
    AccountInfo createAccount();
};

CmdTypeTest::CmdTypeTest()
{

}

CmdTypeTest::~CmdTypeTest()
{

}

void CmdTypeTest::cleanup()
{
    FTPcommand::setAccountDatabaseFactory(AccountDatabaseSingletonFactoryDefault());
}

void CmdTypeTest::test_execute_accountWasntCreated_resultAccountNotFoundException()
{
    Mock<AccountDatabase> database;
    When(OverloadedMethod(database, getAccountInfo, AccountInfo(int))).Throw(AccountDatabase::AccountNotFoundException());

    FakeAccountDatabaseSingletonFactory::setMock(database);
    FTPcommand::setAccountDatabaseFactory(FakeAccountDatabaseSingletonFactory());

    Mock<Transmission> transmission;

    CmdType cmd(COMMAND_CHANNEL_SOCKET, &transmission.get());
    QVERIFY_EXCEPTION_THROWN(cmd.execute(), CmdType::AccountNotFoundException);
}

void CmdTypeTest::test_execute_accountCreated_resultTransmissionSet()
{
    AccountInfo account;

    Mock<AccountDatabase> database;
    When(OverloadedMethod(database, getAccountInfo, AccountInfo(int))).Return(createAccount());
    When(Method(database, setAccountInfo)).Do([&account](AccountInfo acc){account = acc;});

    FakeAccountDatabaseSingletonFactory::setMock(database);
    FTPcommand::setAccountDatabaseFactory(FakeAccountDatabaseSingletonFactory());

    Mock<Transmission> transmission;

    CmdType cmd(COMMAND_CHANNEL_SOCKET, &transmission.get());
    cmd.execute();
    QVERIFY(&transmission.get() == account.transmission);
}

AccountInfo CmdTypeTest::createAccount()
{
    AccountInfo acc;
    acc.commandChannelSocket = COMMAND_CHANNEL_SOCKET;
    return acc;
}

QTEST_APPLESS_MAIN(CmdTypeTest)

#include "tst_cmdtypetest.moc"
