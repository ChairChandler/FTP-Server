#include <QtTest>
#include <string_view>
#include "accountdatabase.h"

#include "cmds/cmduser.h"

class CmdUserTest : public QObject
{
    Q_OBJECT
    using DB = AccountDatabase;
    DB *db;
    CmdUser cmd;
    DB::AccountInfo account;
    static constexpr std::string_view USER_NAME = "NAME";
    static constexpr int USER_SOCKET_ON_SERVER_SIDE_COMMAND_CHANNEL = 0;
public:
    CmdUserTest();
    ~CmdUserTest();

private slots:
    void init();
    void test_execute_accountWasntCreated_resultAccountCreatedAndLoggedIn();
    void test_execute_accountCreatedAndLoggedIn_resultAccountIsLoggedException();
    void test_execute_accountCreatedAndLoggedOut_resultLoggedIn();

private:
    void createUser(DB::LoginStatus status);
    QString toQString(std::string_view view);
};

CmdUserTest::CmdUserTest(): cmd(toQString(USER_NAME), USER_SOCKET_ON_SERVER_SIDE_COMMAND_CHANNEL)
{
    account.name = QString::fromStdString(std::string(USER_NAME));
    account.commandChannelSocket = USER_SOCKET_ON_SERVER_SIDE_COMMAND_CHANNEL;
    db = &AccountDatabase::getInstance();
}

CmdUserTest::~CmdUserTest()
{

}

void CmdUserTest::init()
{
    db->resetDatabase();
}

void CmdUserTest::test_execute_accountWasntCreated_resultAccountCreatedAndLoggedIn()
{
    QVERIFY_EXCEPTION_THROWN(db->getAccountInfo(USER_SOCKET_ON_SERVER_SIDE_COMMAND_CHANNEL), DB::AccountNotFoundException);
    cmd.execute();


    DB::AccountInfo getAccount = db->getAccountInfo(USER_SOCKET_ON_SERVER_SIDE_COMMAND_CHANNEL);
    QVERIFY(getAccount.name == account.name && getAccount.commandChannelSocket == account.commandChannelSocket);
    QCOMPARE(getAccount.status, DB::LoginStatus::LoggedIn);
}

void CmdUserTest::test_execute_accountCreatedAndLoggedIn_resultAccountIsLoggedException()
{
    createUser(DB::LoginStatus::LoggedIn);
    QVERIFY_EXCEPTION_THROWN(cmd.execute(), CmdUser::AccountIsLoggedException);
}

void CmdUserTest::test_execute_accountCreatedAndLoggedOut_resultLoggedIn()
{
    createUser(DB::LoginStatus::LoggedOut);
    cmd.execute();
    QCOMPARE(db->getAccountInfo(USER_SOCKET_ON_SERVER_SIDE_COMMAND_CHANNEL).status, DB::LoginStatus::LoggedIn);
}

void CmdUserTest::createUser(AccountDatabase::LoginStatus status)
{
    DB::AccountInfo account;
    account.name = toQString(USER_NAME);
    account.commandChannelSocket = USER_SOCKET_ON_SERVER_SIDE_COMMAND_CHANNEL;
    account.status = status;
    db->addAccountInfo(account);
}

QString CmdUserTest::toQString(std::string_view view)
{
    return QString::fromStdString(std::string(view));
}


QTEST_APPLESS_MAIN(CmdUserTest)

#include "tst_cmdusertest.moc"
