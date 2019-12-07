#include <QtTest>
#include <unistd.h>
#include "fakeit.hpp"
#include "fakeaccountdatabasefactory.h"
#include "fakebsdsocketfactory.h"
#pragma GCC diagnostic ignored "-Wpadded"
#pragma GCC diagnostic ignored "-Wpragmas" //turn off warning about below turning warning off
#pragma GCC diagnostic ignored "-Wdisabled-macro-expansion"

#include "cmds/cmdport.h"

using namespace fakeit;

class CmdPortTest : public QObject
{
    Q_OBJECT
    const in_port_t CLIENT_DATA_CHANNEL_PORT = 2137;
    const std::string CLIENT_ADDRESS = "127.0.0.1";
    const sockaddr_in CLIENT_DATA_CHANNEL_ADDRESS_STRUCT = createAddressStruct();
    const int CLIENT_SOCKET_ON_SERVER_COMMAND_CHANNEL = 2137;
    const AccountInfo CLIENT_ACCOUNT = createAccount();

    CmdPort *cmd;

public:
    CmdPortTest();
    ~CmdPortTest();

private slots:
    void init();
    void cleanup();
    void test_execute_accountWasntCreated_resultAccountNotFoundException();
    void test_execute_accountCreated_clientDidntStartDataStream_resultCannotConnectException();
    void test_execute_and_getDataChannelSocket_accountCreated_clientStartDataChannel_resultConnected();
    void test_getDataChannelSocket_notConected_resultDataChannelSocketNotExistsException();

private:
    const sockaddr_in createAddressStruct() const;
    const AccountInfo createAccount() const;
};

CmdPortTest::CmdPortTest()
{

}

CmdPortTest::~CmdPortTest()
{

}

void CmdPortTest::init()
{
    cmd = new CmdPort(CLIENT_SOCKET_ON_SERVER_COMMAND_CHANNEL, CLIENT_DATA_CHANNEL_ADDRESS_STRUCT);
}

void CmdPortTest::cleanup()
{
    FTPcommand::setAccountDatabaseFactory(AccountDatabaseSingletonFactoryDefault());
    CmdPort::setBsdSocketFactory(BsdSocketFactoryDefault());
    delete cmd;
}

void CmdPortTest::test_execute_accountWasntCreated_resultAccountNotFoundException()
{
    Mock<AccountDatabase> database;
    When(OverloadedMethod(database, getAccountInfo, AccountInfo(int))).Throw(AccountDatabase::AccountNotFoundException());

    FakeAccountDatabaseSingletonFactory::setMock(database);
    FTPcommand::setAccountDatabaseFactory(FakeAccountDatabaseSingletonFactory());

    QVERIFY_EXCEPTION_THROWN(cmd->execute(), CmdPort::AccountNotFoundException);
}

void CmdPortTest::test_execute_accountCreated_clientDidntStartDataStream_resultCannotConnectException()
{
    Mock<AccountDatabase> database;
    When(OverloadedMethod(database, getAccountInfo, AccountInfo(int))).Return(CLIENT_ACCOUNT);

    FakeAccountDatabaseSingletonFactory::setMock(database);
    FTPcommand::setAccountDatabaseFactory(FakeAccountDatabaseSingletonFactory());

    Mock<BsdSocketFactory> functions;
    When(Method(functions, socket)).Return(0);
    When(Method(functions, connect)).Return(-1);

    FakeBsdSocketFactory::setMock(functions);
    CmdPort::setBsdSocketFactory(FakeBsdSocketFactory());

    QVERIFY_EXCEPTION_THROWN(cmd->execute(), CmdPort::CannotConnectException);
}

void CmdPortTest::test_execute_and_getDataChannelSocket_accountCreated_clientStartDataChannel_resultConnected()
{
    Mock<AccountDatabase> database;
    When(OverloadedMethod(database, getAccountInfo, AccountInfo(int))).Return(CLIENT_ACCOUNT);

    FakeAccountDatabaseSingletonFactory::setMock(database);
    FTPcommand::setAccountDatabaseFactory(FakeAccountDatabaseSingletonFactory());

    Mock<BsdSocketFactory> functions;
    When(Method(functions, socket)).Return(0);
    When(Method(functions, connect)).Return(0);

    FakeBsdSocketFactory::setMock(functions);
    CmdPort::setBsdSocketFactory(FakeBsdSocketFactory());

    cmd->execute();
    cmd->getDataChannelSocket();
}

void CmdPortTest::test_getDataChannelSocket_notConected_resultDataChannelSocketNotExistsException()
{
    QVERIFY_EXCEPTION_THROWN(cmd->getDataChannelSocket(), CmdPort::DataChannelSocketNotExistsException);
}

const sockaddr_in CmdPortTest::createAddressStruct() const
{
    sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(CLIENT_DATA_CHANNEL_PORT);
    inet_pton(AF_INET, CLIENT_ADDRESS.c_str(), &address.sin_addr);
    return address;
}

const AccountInfo CmdPortTest::createAccount() const
{
    AccountInfo account;
    account.commandChannelSocket = CLIENT_SOCKET_ON_SERVER_COMMAND_CHANNEL;
    return account;
}


QTEST_APPLESS_MAIN(CmdPortTest)

#include "tst_cmdporttest.moc"
