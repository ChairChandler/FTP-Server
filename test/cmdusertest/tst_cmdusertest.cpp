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

CmdUserTest::CmdUserTest(): cmd(QString::fromStdString(std::string(USER_NAME)), USER_SOCKET)
{
    db = &AccountDatabase::getInstance();

}

CmdUserTest::~CmdUserTest()
{

}

void CmdUserTest::test_execute_accountWasntCreated_resultAccountCreatedAndLoggedIn_returnTrue()
{
    DB::AccountInfo acc;
    acc.name = QString::fromStdString(std::string(USER_NAME));
    acc.commandStreamSocket = USER_SOCKET;

    QVERIFY_EXCEPTION_THROWN(db->getAccountInfo(USER_SOCKET), DB::AccountNotFoundException);
    QCOMPARE(cmd.execute(), true);


    DB::AccountInfo getAccount = db->getAccountInfo(USER_SOCKET);
    QVERIFY(getAccount.name == acc.name && getAccount.commandStreamSocket == acc.commandStreamSocket);
    QCOMPARE(getAccount.status, DB::LoginStatus::LoggedIn);
}

void CmdUserTest::test_execute_accountCreatedAndLoggedIn_resultNothingChanged_returnFalse()
{
    QCOMPARE(cmd.execute(), false);
    QCOMPARE(db->getAccountInfo(USER_SOCKET).status, DB::LoginStatus::LoggedIn);
}

void CmdUserTest::test_execute_accountCreatedAndLoggedOut_resultLoggedIn_returnTrue()
{
    DB::AccountInfo acc = db->getAccountInfo(USER_SOCKET);
    acc.status = DB::LoginStatus::LoggedOut;
    db->setAccountInfo(acc);

    QCOMPARE(cmd.execute(), true);
    QCOMPARE(db->getAccountInfo(USER_SOCKET).status, DB::LoginStatus::LoggedIn);
}

QTEST_APPLESS_MAIN(CmdUserTest)

#include "tst_cmdusertest.moc"
