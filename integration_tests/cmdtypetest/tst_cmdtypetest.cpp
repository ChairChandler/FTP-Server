#include <QtTest>
#include "FakeTransmissionClasses.h"
#pragma GCC diagnostic ignored "-Wpadded"

#include "cmds/cmdtype.h"

class CmdTypeTest : public QObject
{
    Q_OBJECT
    const int COMMAND_CHANNEL_SOCKET = 0;
    using DB = AccountDatabase;
    DB *db;
    Transmission *transmissionA, *transmissionB;
public:
    CmdTypeTest();
    ~CmdTypeTest();

private slots:
    void init();
    void cleanup();
    void test_execute_accountWasntCreated_resultAccountNotFoundException();
    void test_execute_accountCreated_resultTransmissionSet();

private:
    void createAccount();
};

CmdTypeTest::CmdTypeTest()
{
    db = &AccountDatabaseSingletonFactoryDefault().getInstance();
}

CmdTypeTest::~CmdTypeTest()
{

}

void CmdTypeTest::init()
{
    transmissionA = new FakeClassA;
    transmissionB = new FakeClassB;
}

void CmdTypeTest::cleanup()
{
    db->resetDatabase();
    delete  transmissionA;
    delete  transmissionB;
}

void CmdTypeTest::test_execute_accountWasntCreated_resultAccountNotFoundException()
{
    CmdType cmd(COMMAND_CHANNEL_SOCKET, transmissionA);
    QVERIFY_EXCEPTION_THROWN(cmd.execute(), CmdType::AccountNotFoundException);
}

void CmdTypeTest::test_execute_accountCreated_resultTransmissionSet()
{
    createAccount();
    CmdType cmd(COMMAND_CHANNEL_SOCKET, transmissionA);
    cmd.execute();
    QVERIFY(db->getAccountInfo(COMMAND_CHANNEL_SOCKET).transmission != transmissionB);
}

void CmdTypeTest::createAccount()
{
    AccountInfo acc;
    acc.commandChannelSocket = COMMAND_CHANNEL_SOCKET;
    db->addAccountInfo(acc);
}

QTEST_APPLESS_MAIN(CmdTypeTest)

#include "tst_cmdtypetest.moc"
