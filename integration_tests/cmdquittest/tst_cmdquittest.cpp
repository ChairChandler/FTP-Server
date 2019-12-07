#include <QtTest>
#include <string_view>
#include "accountdatabase.h"

#include "cmds/cmdquit.h"

class CmdQuitTest : public QObject
{
    Q_OBJECT
    using DB = AccountDatabase;
    DB *db;
    CmdQuit cmd;
    static constexpr std::string_view USER_NAME = "NAME";
    static constexpr int USER_SOCKET_ON_SERVER_COMMAND_CHANNEL = 0;
public:
    CmdQuitTest();
    ~CmdQuitTest();

private slots:
    void init();
    void test_execute_userWasntCreated_resultAccountNotFoundException();
    void test_execute_userCreatedAndLogged_resultLoggedOut();
    void test_execute_userCreatedButUnlogged_resultAccountIsUnloggedException();

private:
    void createUser(LoginStatus status) const;
    QString toQString(std::string_view view) const;
};

CmdQuitTest::CmdQuitTest(): cmd(USER_SOCKET_ON_SERVER_COMMAND_CHANNEL)
{
    db = &AccountDatabaseSingletonFactoryDefault().getInstance();
}

CmdQuitTest::~CmdQuitTest()
{

}

void CmdQuitTest::init()
{
    db->resetDatabase();
}

void CmdQuitTest::test_execute_userWasntCreated_resultAccountNotFoundException()
{
    QVERIFY_EXCEPTION_THROWN(cmd.execute(), CmdQuit::AccountNotFoundException);
}

void CmdQuitTest::test_execute_userCreatedAndLogged_resultLoggedOut()
{
    createUser(LoginStatus::LoggedIn);
    cmd.execute();

    AccountInfo getAccount = db->getAccountInfo(USER_SOCKET_ON_SERVER_COMMAND_CHANNEL);
    QCOMPARE(getAccount.status, LoginStatus::LoggedOut);
}

void CmdQuitTest::test_execute_userCreatedButUnlogged_resultAccountIsUnloggedException()
{
    createUser(LoginStatus::LoggedOut);
    QVERIFY_EXCEPTION_THROWN(cmd.execute(), CmdQuit::AccountIsUnloggedException);
}

void CmdQuitTest::createUser(LoginStatus status) const
{
    AccountInfo account;
    account.name = toQString(USER_NAME);
    account.commandChannelSocket = USER_SOCKET_ON_SERVER_COMMAND_CHANNEL;
    account.status = status;
    db->addAccountInfo(account);
}

QString CmdQuitTest::toQString(std::string_view view) const
{
    return QString::fromStdString(std::string(view));
}

QTEST_APPLESS_MAIN(CmdQuitTest)

#include "tst_cmdquittest.moc"
