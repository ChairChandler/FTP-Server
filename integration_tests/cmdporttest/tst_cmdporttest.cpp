#include <QtTest>
#include <unistd.h>
#include "fakeclientdataserver.h"
#pragma GCC diagnostic ignored "-Wpadded"

#include "cmds/cmdport.h"

class CmdPortTest : public QObject
{
    Q_OBJECT
    const in_port_t CLIENT_DATA_CHANNEL_PORT = 2137;
    const std::string CLIENT_ADDRESS = "127.0.0.1";
    const sockaddr_in CLIENT_DATA_CHANNEL_ADDRESS_STRUCT = createAddressStruct();
    const int CLIENT_SOCKET_ON_SERVER_COMMAND_CHANNEL = 2137;
    const AccountInfo CLIENT_ACCOUNT = createAccount();
    const unsigned long WAIT_TIME_MS = 200;

    using DB = AccountDatabase;
    DB *db;
    CmdPort *cmd;
    FakeClientDataServer *fakeClient = nullptr;

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
    void createDataStream();
    void waitUntilServerReady();
    void deleteDataStream();
};

CmdPortTest::CmdPortTest()
{
    db = &AccountDatabaseSingletonFactoryDefault().getInstance();
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
    db->resetDatabase();
    deleteDataStream();
    delete cmd;
}

void CmdPortTest::test_execute_accountWasntCreated_resultAccountNotFoundException()
{
    QVERIFY_EXCEPTION_THROWN(cmd->execute(), CmdPort::AccountNotFoundException);
}

void CmdPortTest::test_execute_accountCreated_clientDidntStartDataStream_resultCannotConnectException()
{
    db->addAccountInfo(CLIENT_ACCOUNT);
    QVERIFY_EXCEPTION_THROWN(cmd->execute(), CmdPort::CannotConnectException);
}

void CmdPortTest::test_execute_and_getDataChannelSocket_accountCreated_clientStartDataChannel_resultConnected()
{
    createDataStream();
    waitUntilServerReady();

    db->addAccountInfo(CLIENT_ACCOUNT);
    cmd->execute();
    QThread::msleep(WAIT_TIME_MS);
    QCOMPARE(fakeClient->isNewConnection(), true);
    QCOMPARE(fakeClient->isError(), false);
    close(cmd->getDataChannelSocket());
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

void CmdPortTest::createDataStream()
{
    fakeClient = new FakeClientDataServer(CLIENT_DATA_CHANNEL_ADDRESS_STRUCT);
}

void CmdPortTest::waitUntilServerReady()
{
    while(!fakeClient->isServerReady()) {
        if(fakeClient->isError()) {
            throw std::runtime_error(fakeClient->getErrorMsg().toUtf8().constData());
        }
    }
}

void CmdPortTest::deleteDataStream()
{
    if(fakeClient) {
        delete fakeClient;
        fakeClient = nullptr;
    }
}


QTEST_APPLESS_MAIN(CmdPortTest)

#include "tst_cmdporttest.moc"
