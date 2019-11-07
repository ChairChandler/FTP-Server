#include <QtTest>
#include <string_view>
#include "accountdatabase.h"
#include "cmds/cmduser.h"

#include "cmds/cmdquit.h"

class CmdQuitTest : public QObject
{
    Q_OBJECT
    using DB = AccountDatabase;
    DB *db;
    CmdQuit cmd;
    CmdUser create;
    static constexpr std::string_view USER_NAME = "NAME";
    static constexpr int USER_SOCKET = 0;
public:
    CmdQuitTest();
    ~CmdQuitTest();

private slots:
    void test_execute_userWasntCreated_resultNothingChanged_returnFalse();
    void test_execute_userCreatedAndLogged_resultLoggedOut_returnTrue();
    void test_execute_userCreatedButUnlogged_resultNothingChanged_returnTrue();
};

CmdQuitTest::CmdQuitTest(): cmd(USER_SOCKET), create(QString::fromStdString(std::string(USER_NAME)), USER_SOCKET)
{
    db = &AccountDatabase::getInstance();
}

CmdQuitTest::~CmdQuitTest()
{
    db->resetDatabase();
}

void CmdQuitTest::test_execute_userWasntCreated_resultNothingChanged_returnFalse()
{
    QCOMPARE(cmd.execute(), false);
}

void CmdQuitTest::test_execute_userCreatedAndLogged_resultLoggedOut_returnTrue()
{
    create.execute();

    QCOMPARE(cmd.execute(), true);

    DB::AccountInfo getAccount = db->getAccountInfo(USER_SOCKET);
    QCOMPARE(getAccount.status, DB::LoginStatus::LoggedOut);
}

void CmdQuitTest::test_execute_userCreatedButUnlogged_resultNothingChanged_returnTrue()
{
    QCOMPARE(cmd.execute(), true);

    DB::AccountInfo getAccount = db->getAccountInfo(USER_SOCKET);
    QCOMPARE(getAccount.status, DB::LoginStatus::LoggedOut);
}



QTEST_APPLESS_MAIN(CmdQuitTest)

#include "tst_cmdquittest.moc"
