#include <QtTest>
#include <string_view>
#include "fakeaccountinfobuilder.h"
#include "fakeaccountdatabasefactory.h"
#include "ftpfilesystem/ftpfilesystem.h"
#include "fakeit.hpp"
#pragma GCC diagnostic ignored "-Wpragmas" //turn off warning about below turning warning off
#pragma GCC diagnostic ignored "-Wdisabled-macro-expansion"

#include "cmds/cmduser.h"

using namespace fakeit;

class CmdUserTest : public QObject
{
    Q_OBJECT
    static constexpr std::string_view USER_NAME = "NAME";
    static constexpr int USER_SOCKET_ON_SERVER_SIDE_COMMAND_CHANNEL = 0;
public:
    CmdUserTest();
    ~CmdUserTest();

private slots:
    void cleanup();
    void test_execute_accountWasntCreated_resultAccountCreatedAndLoggedIn();
    void test_execute_accountCreatedAndLoggedIn_resultAccountIsLoggedException();
    void test_execute_accountCreatedAndLoggedOut_resultLoggedIn();

private:
    AccountInfo createUser(LoginStatus status);
    QString toQString(std::string_view view);
};

CmdUserTest::CmdUserTest()
{

}

CmdUserTest::~CmdUserTest()
{

}

void CmdUserTest::cleanup()
{
    FTPcommand::setAccountDatabaseFactory(AccountDatabaseSingletonFactoryDefault());
    CmdUser::setAccountInfoBuilder(AccountInfoBuilderDefault());
}

void CmdUserTest::test_execute_accountWasntCreated_resultAccountCreatedAndLoggedIn()
{
    AccountInfo account;

    Mock<AccountDatabase> database;
    When(Method(database, addAccountInfo)).Do([&account](AccountInfo acc){account = acc;});

    FakeAccountDatabaseSingletonFactory::setMock(database);
    FTPcommand::setAccountDatabaseFactory(FakeAccountDatabaseSingletonFactory());


    Mock<AccountInfoBuilder> builder;

    When(Method(builder, buildFileSystem)).Return(nullptr);
    When(Method(builder, buildMode)).Return(nullptr);
    When(Method(builder, buildStructure)).Return(nullptr);
    When(Method(builder, buildTransmission)).Return(nullptr);
    When(Method(builder, buildFileSystem)).Return(nullptr);
    When(Method(builder, buildDataChannelSocket)).Return(0);
    When(Method(builder, clone)).Return(&builder.get());

    FakeAccountInfoBuilder::setMock(builder);
    CmdUser::setAccountInfoBuilder(FakeAccountInfoBuilder());

    CmdUser cmd(toQString(USER_NAME), USER_SOCKET_ON_SERVER_SIDE_COMMAND_CHANNEL);
    cmd.execute();

    QVERIFY(account.name == toQString(USER_NAME) && account.commandChannelSocket == USER_SOCKET_ON_SERVER_SIDE_COMMAND_CHANNEL);
    QCOMPARE(account.status, LoginStatus::LoggedIn);
}

void CmdUserTest::test_execute_accountCreatedAndLoggedIn_resultAccountIsLoggedException()
{
    Mock<AccountDatabase> database;
    When(Method(database, addAccountInfo)).Throw(AccountDatabase::AccountExistsException());
    When(OverloadedMethod(database, getAccountInfo, AccountInfo(QString))).Return(createUser(LoginStatus::LoggedIn));

    FakeAccountDatabaseSingletonFactory::setMock(database);
    FTPcommand::setAccountDatabaseFactory(FakeAccountDatabaseSingletonFactory());

    Mock<AccountInfoBuilder> builder;

    When(Method(builder, buildFileSystem)).Return(nullptr);
    When(Method(builder, buildMode)).Return(nullptr);
    When(Method(builder, buildStructure)).Return(nullptr);
    When(Method(builder, buildTransmission)).Return(nullptr);
    When(Method(builder, buildFileSystem)).Return(nullptr);
    When(Method(builder, buildDataChannelSocket)).Return(0);
    When(Method(builder, clone)).Return(&builder.get());

    FakeAccountInfoBuilder::setMock(builder);
    CmdUser::setAccountInfoBuilder(FakeAccountInfoBuilder());

    CmdUser cmd(toQString(USER_NAME), USER_SOCKET_ON_SERVER_SIDE_COMMAND_CHANNEL);

    QVERIFY_EXCEPTION_THROWN(cmd.execute(), CmdUser::AccountIsLoggedException);
}

void CmdUserTest::test_execute_accountCreatedAndLoggedOut_resultLoggedIn()
{
    AccountInfo account;

    Mock<AccountDatabase> database;
    When(Method(database, addAccountInfo)).Throw(AccountDatabase::AccountExistsException());
    When(OverloadedMethod(database, getAccountInfo, AccountInfo(QString))).Return(createUser(LoginStatus::LoggedOut));
    When(Method(database, setAccountInfo)).Do([&account](AccountInfo acc){account = acc;});

    FakeAccountDatabaseSingletonFactory::setMock(database);
    FTPcommand::setAccountDatabaseFactory(FakeAccountDatabaseSingletonFactory());

    Mock<AccountInfoBuilder> builder;

    When(Method(builder, buildFileSystem)).Return(nullptr);
    When(Method(builder, buildMode)).Return(nullptr);
    When(Method(builder, buildStructure)).Return(nullptr);
    When(Method(builder, buildTransmission)).Return(nullptr);
    When(Method(builder, buildFileSystem)).Return(nullptr);
    When(Method(builder, buildDataChannelSocket)).Return(0);
    When(Method(builder, clone)).Return(&builder.get());

    FakeAccountInfoBuilder::setMock(builder);
    CmdUser::setAccountInfoBuilder(FakeAccountInfoBuilder());

    CmdUser cmd(toQString(USER_NAME), USER_SOCKET_ON_SERVER_SIDE_COMMAND_CHANNEL);

    cmd.execute();
    QCOMPARE(account.status, LoginStatus::LoggedIn);
}

AccountInfo CmdUserTest::createUser(LoginStatus status)
{
    AccountInfo account;
    account.name = toQString(USER_NAME);
    account.commandChannelSocket = USER_SOCKET_ON_SERVER_SIDE_COMMAND_CHANNEL;
    account.status = status;

    return account;
}

QString CmdUserTest::toQString(std::string_view view)
{
    return QString::fromStdString(std::string(view));
}


QTEST_APPLESS_MAIN(CmdUserTest)

#include "tst_cmdusertest.moc"
