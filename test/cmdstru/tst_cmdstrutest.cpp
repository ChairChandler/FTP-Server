#include <QtTest>
#include "FakeFileStructureClasses.h"
#pragma GCC diagnostic ignored "-Wpadded"

#include "cmds/cmdstru.h"

class CmdStruTest : public QObject
{
    Q_OBJECT
    const int COMMAND_CHANNEL_SOCKET = 0;
    using DB = AccountDatabase;
    DB *db;
    FileStructure *fileStructureA, *fileStructureB;
public:
    CmdStruTest();
    ~CmdStruTest();

private slots:
    void init();
    void cleanup();
    void test_execute_accountWasntCreated_resultAccountNotFoundException();
    void test_execute_accountCreated_resultFileStructureSet();

private:
    void createAccount();
};

CmdStruTest::CmdStruTest()
{
    db = &DB::getInstance();
}

CmdStruTest::~CmdStruTest()
{

}

void CmdStruTest::init()
{
    fileStructureA = new FakeClassA;
    fileStructureB = new FakeClassB;
}

void CmdStruTest::cleanup()
{
    db->resetDatabase();
    delete fileStructureA;
    delete fileStructureB;
}

void CmdStruTest::test_execute_accountWasntCreated_resultAccountNotFoundException()
{
    CmdStru cmd(COMMAND_CHANNEL_SOCKET, fileStructureA);
    QVERIFY_EXCEPTION_THROWN(cmd.execute(), CmdStru::AccountNotFoundException);
}

void CmdStruTest::test_execute_accountCreated_resultFileStructureSet()
{
    createAccount();
    CmdStru cmd(COMMAND_CHANNEL_SOCKET, fileStructureA);
    cmd.execute();
    QVERIFY(db->getAccountInfo(COMMAND_CHANNEL_SOCKET).fileStructure != fileStructureB);
}

void CmdStruTest::createAccount()
{
    DB::AccountInfo acc;
    acc.commandChannelSocket = COMMAND_CHANNEL_SOCKET;
    db->addAccountInfo(acc);
}

QTEST_APPLESS_MAIN(CmdStruTest)

#include "tst_cmdstrutest.moc"
