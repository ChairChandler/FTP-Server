#include <QtTest>
#include <string_view>
#include "accountdatabase.h"
#include "cmds/cmdquit.h"

#include "cmds/cmduser.h"

class CmdUserTest : public QObject
{
    Q_OBJECT
    using DB = AccountDatabase;
    DB *db;
    CmdUser cmd;
    CmdQuit quit;
    DB::AccountInfo account;
    static constexpr std::string_view USER_NAME = "NAME";
    static constexpr int USER_SOCKET = 0;
public:
    CmdUserTest();
    ~CmdUserTest();

private slots:
    void test_execute_accountWasntCreated_resultAccountCreatedAndLoggedIn_returnTrue();
    void test_execute_accountCreatedAndLoggedIn_resultNothingChanged_returnFalse();
    void test_execute_accountCreatedAndLoggedOut_resultLoggedIn_returnTrue();
};

CmdUserTest::CmdUserTest(): cmd(QString::fromStdString(std::string(USER_NAME)), USER_SOCKET), quit(USER_SOCKET)
{
    account.name = QString::fromStdString(std::string(USER_NAME));
    account.commandStreamSocket = USER_SOCKET;
    db = &AccountDatabase::getInstance();
}

CmdUserTest::~CmdUserTest()
{

}

void CmdUserTest::test_execute_accountWasntCreated_resultAccountCreatedAndLoggedIn_returnTrue()
{
    QVERIFY_EXCEPTION_THROWN(db->getAccountInfo(USER_SOCKET), DB::AccountNotFoundException);
    QCOMPARE(cmd.execute(), true);


    DB::AccountInfo getAccount = db->getAccountInfo(USER_SOCKET);
    QVERIFY(getAccount.name == account.name && getAccount.commandStreamSocket == account.commandStreamSocket);
    QCOMPARE(getAccount.status, DB::LoginStatus::LoggedIn);
}

void CmdUserTest::test_execute_accountCreatedAndLoggedIn_resultNothingChanged_returnFalse()
{
    QCOMPARE(cmd.execute(), false);
    QCOMPARE(db->getAccountInfo(USER_SOCKET).status, DB::LoginStatus::LoggedIn);
}

void CmdUserTest::test_execute_accountCreatedAndLoggedOut_resultLoggedIn_returnTrue()
{
    quit.execute();

    QCOMPARE(cmd.execute(), true);
    QCOMPARE(db->getAccountInfo(USER_SOCKET).status, DB::LoginStatus::LoggedIn);
}

QTEST_APPLESS_MAIN(CmdUserTest)

#include "tst_cmdusertest.moc"
