#include <QtTest>
#include <string_view>
#include "fakeit.hpp"
#include "accountdatabase.h"
#include "fakeaccountdatabasefactory.h"
#pragma GCC diagnostic ignored "-Wpragmas" //turn off warning about below turning warning off
#pragma GCC diagnostic ignored "-Wdisabled-macro-expansion"

#include "cmds/cmdquit.h"

using namespace fakeit;

class CmdQuitTest : public QObject
{
    Q_OBJECT
    CmdQuit cmd;
    static constexpr std::string_view USER_NAME = "NAME";
    static constexpr int USER_SOCKET_ON_SERVER_COMMAND_CHANNEL = 0;
public:
    CmdQuitTest();
    ~CmdQuitTest();

private slots:
    void cleanup();
    void test_execute_userWasntCreated_resultAccountNotFoundException();
    void test_execute_userCreatedAndLogged_resultLoggedOut();
    void test_execute_userCreatedButUnlogged_resultAccountIsUnloggedException();

private:
    AccountInfo createUser(LoginStatus status) const;
    QString toQString(std::string_view view) const;
};

CmdQuitTest::CmdQuitTest(): cmd(USER_SOCKET_ON_SERVER_COMMAND_CHANNEL)
{

}

CmdQuitTest::~CmdQuitTest()
{

}

void CmdQuitTest::cleanup()
{
    FTPcommand::setAccountDatabaseFactory(AccountDatabaseSingletonFactoryDefault());
}

void CmdQuitTest::test_execute_userWasntCreated_resultAccountNotFoundException()
{
    Mock<AccountDatabase> database;
    When(OverloadedMethod(database, getAccountInfo, AccountInfo(int))).Throw(AccountDatabase::AccountNotFoundException());

    FakeAccountDatabaseSingletonFactory::setMock(database);
    FTPcommand::setAccountDatabaseFactory(FakeAccountDatabaseSingletonFactory());
    QVERIFY_EXCEPTION_THROWN(cmd.execute(), CmdQuit::AccountNotFoundException);
}

void CmdQuitTest::test_execute_userCreatedAndLogged_resultLoggedOut()
{
    AccountInfo accountAfter;

    Mock<AccountDatabase> database;
    When(OverloadedMethod(database, getAccountInfo, AccountInfo(int))).Return(createUser(LoginStatus::LoggedIn));
    When(Method(database, setAccountInfo)).Do([&accountAfter](AccountInfo acc){accountAfter = acc;});

    FakeAccountDatabaseSingletonFactory::setMock(database);
    FTPcommand::setAccountDatabaseFactory(FakeAccountDatabaseSingletonFactory());

    cmd.execute();

    QCOMPARE(accountAfter.status, LoginStatus::LoggedOut);
}

void CmdQuitTest::test_execute_userCreatedButUnlogged_resultAccountIsUnloggedException()
{
    AccountInfo accountAfter;

    Mock<AccountDatabase> database;
    When(OverloadedMethod(database, getAccountInfo, AccountInfo(int))).Return(createUser(LoginStatus::LoggedOut));

    QVERIFY_EXCEPTION_THROWN(cmd.execute(), CmdQuit::AccountIsUnloggedException);
}

AccountInfo CmdQuitTest::createUser(LoginStatus status) const
{
    AccountInfo account;
    account.name = toQString(USER_NAME);
    account.commandChannelSocket = USER_SOCKET_ON_SERVER_COMMAND_CHANNEL;
    account.status = status;
    return account;
}

QString CmdQuitTest::toQString(std::string_view view) const
{
    return QString::fromStdString(std::string(view));
}

QTEST_APPLESS_MAIN(CmdQuitTest)

#include "tst_cmdquittest.moc"
