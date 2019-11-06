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
    void test_execute_accountWasntCreated_resultAccountCreatedAndLoggedIn();
    void test_execute_accountCreatedAndLoggedIn_resultPass();
    void test_execute_accountCreatedAndLoggedOut_resultLoggedIn();
};

CmdUserTest::CmdUserTest(): cmd(QString::fromStdString(std::string(USER_NAME)), USER_SOCKET)
{
    db = &AccountDatabase::getInstance();

}

CmdUserTest::~CmdUserTest()
{

}

void CmdUserTest::test_execute_accountWasntCreated_resultAccountCreatedAndLoggedIn()
{
    DB::AccountInfo acc;
    acc.name = QString::fromStdString(std::string(USER_NAME));
    acc.commandStreamSocket = USER_SOCKET;

    QVERIFY_EXCEPTION_THROWN(db->getAccountInfo(USER_SOCKET), DB::AccountNotFoundException);
    cmd.execute();


    DB::AccountInfo getAccount = db->getAccountInfo(USER_SOCKET);
    QVERIFY(getAccount.name == acc.name && getAccount.commandStreamSocket == acc.commandStreamSocket);
    QCOMPARE(getAccount.status, DB::LoginStatus::LoggedIn);
}

void CmdUserTest::test_execute_accountCreatedAndLoggedIn_resultPass()
{
    cmd.execute();
    QCOMPARE(db->getAccountInfo(USER_SOCKET).status, DB::LoginStatus::LoggedIn);
}

void CmdUserTest::test_execute_accountCreatedAndLoggedOut_resultLoggedIn()
{
    DB::AccountInfo acc = db->getAccountInfo(USER_SOCKET);
    acc.status = DB::LoginStatus::LoggedOut;
    db->setAccountInfo(acc);

    cmd.execute();
    QCOMPARE(db->getAccountInfo(USER_SOCKET).status, DB::LoginStatus::LoggedIn);
}

QTEST_APPLESS_MAIN(CmdUserTest)

#include "tst_cmdusertest.moc"
