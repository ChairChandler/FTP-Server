#include <QtTest>
#include "FakeModeClasses.h"
#pragma GCC diagnostic ignored "-Wpadded"

#include "cmds/cmdmode.h"

class CmdModeTest : public QObject
{
    Q_OBJECT
    const int COMMAND_CHANNEL_SOCKET = 0;
    using DB = AccountDatabase;
    DB *db;
    Mode *modeA, *modeB;
public:
    CmdModeTest();
    ~CmdModeTest();

private slots:
    void init();
    void cleanup();
    void test_execute_accountWasntCreated_resultAccountNotFoundException();
    void test_execute_accountCreated_resultModeSet();

private:
    void createAccount();
};

CmdModeTest::CmdModeTest()
{
    db = &AccountDatabaseSingletonFactoryDefault().getInstance();
}

CmdModeTest::~CmdModeTest()
{

}

void CmdModeTest::init()
{
    modeA = new FakeClassA;
    modeB = new FakeClassB;
}

void CmdModeTest::cleanup()
{
    db->resetDatabase();
    delete modeA;
    delete modeB;
}

void CmdModeTest::test_execute_accountWasntCreated_resultAccountNotFoundException()
{
    CmdMode cmd(COMMAND_CHANNEL_SOCKET, modeA);
    QVERIFY_EXCEPTION_THROWN(cmd.execute(), CmdMode::AccountNotFoundException);
}

void CmdModeTest::test_execute_accountCreated_resultModeSet()
{
    createAccount();
    CmdMode cmd(COMMAND_CHANNEL_SOCKET, modeA);
    cmd.execute();
    QVERIFY(db->getAccountInfo(COMMAND_CHANNEL_SOCKET).mode != modeB);
}

void CmdModeTest::createAccount()
{
    AccountInfo acc;
    acc.commandChannelSocket = COMMAND_CHANNEL_SOCKET;
    db->addAccountInfo(acc);
}

QTEST_APPLESS_MAIN(CmdModeTest)

#include "tst_cmdmodetest.moc"
