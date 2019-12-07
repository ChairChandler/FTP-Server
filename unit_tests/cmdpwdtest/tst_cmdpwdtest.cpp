#include <QtTest>
#include "fakeaccountdatabasefactory.h"
#include "fakebsdsocketfactory.h"
#include "ftpfilesystem/ftpfilesystem.h"
#include "fakeit.hpp"
#pragma GCC diagnostic ignored "-Wpragmas" //turn off warning about below turning warning off
#pragma GCC diagnostic ignored "-Wdisabled-macro-expansion"

#include "cmds/cmdpwd.h"

using namespace fakeit;

class CmdPwdTest : public QObject
{
    Q_OBJECT
    const int COMMAND_CHANNEL_SOCKET = 0;
    const int DATA_CHANNEL_SOCKET = 1;
    const QString WORKING_DIRECTORY = "WORKING_DIRECTORY";
    CmdPwd cmd;
public:
    CmdPwdTest();
    ~CmdPwdTest();

private slots:
    void cleanup();
    void test_execute_accountNotExists_resultAccountNotFoundException();
    void test_execute_accountExists_resultWriteWorkingDirectory();
};

CmdPwdTest::CmdPwdTest(): cmd(COMMAND_CHANNEL_SOCKET, DATA_CHANNEL_SOCKET)
{

}

CmdPwdTest::~CmdPwdTest()
{

}

void CmdPwdTest::cleanup()
{
    FTPcommand::setAccountDatabaseFactory(AccountDatabaseSingletonFactoryDefault());
}

void CmdPwdTest::test_execute_accountNotExists_resultAccountNotFoundException()
{
    Mock<AccountDatabase> database;
    When(OverloadedMethod(database, getAccountInfo, AccountInfo(int))).Throw(AccountDatabase::AccountNotFoundException());

    FakeAccountDatabaseSingletonFactory::setMock(database);
    FTPcommand::setAccountDatabaseFactory(FakeAccountDatabaseSingletonFactory());

    QVERIFY_EXCEPTION_THROWN(cmd.execute(), AccountDatabase::AccountNotFoundException);
}

void CmdPwdTest::test_execute_accountExists_resultWriteWorkingDirectory()
{
    AccountInfo account;

    Mock<FTPfileSystem> fileSystem;
    When(Method(fileSystem, printWorkingDirectory)).Return(WORKING_DIRECTORY);
    account.fileSystem = &fileSystem.get();


    Mock<AccountDatabase> database;
    When(OverloadedMethod(database, getAccountInfo, AccountInfo(int))).Return(account);

    FakeAccountDatabaseSingletonFactory::setMock(database);
    FTPcommand::setAccountDatabaseFactory(FakeAccountDatabaseSingletonFactory());


    QString returnVal;
    Mock<BsdSocketFactory> bsdSocket;
    When(Method(bsdSocket, write)).Do([&returnVal](int __fd, const void *__buf, size_t __n){
        Q_UNUSED(__fd)
        returnVal += QByteArray(static_cast<const char*>(__buf), static_cast<int>(__n));
        return 0;});

    FakeBsdSocketFactory::setMock(bsdSocket);
    CmdPwd::setBsdSocketFactory(FakeBsdSocketFactory());

    cmd.execute();
    QCOMPARE(returnVal, WORKING_DIRECTORY);
}

QTEST_APPLESS_MAIN(CmdPwdTest)

#include "tst_cmdpwdtest.moc"
