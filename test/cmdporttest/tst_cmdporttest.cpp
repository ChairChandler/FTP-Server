#include <QtTest>
#include <unistd.h>
#include "fakeclientdataserver.h"
#pragma GCC diagnostic ignored "-Wpadded"

#include "cmds/cmdport.h"

class CmdPortTest : public QObject
{
    Q_OBJECT
    const in_port_t CLIENT_DATA_STREAM_SOCKET = 2137;
    const std::string CLIENT_ADDRESS = "127.0.0.1";
    const sockaddr_in ADDRESS_STRUCT = createAddressStruct();
    const int SERVER_COMMAND_STREAM_SOCKET = 2137;
    const AccountDatabase::AccountInfo ACCOUNT = createAccount();
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
    void test_execute_and_getDataStreamSocket_accountCreated_clientStartDataStream_resultConnected();
    void test_getDataStreamSocket_notConected_resultDataStreamSocketNotExistsException();

private:
    const sockaddr_in createAddressStruct() const;
    const AccountDatabase::AccountInfo createAccount() const;
    void createDataStream();
    void waitUntilServerReady();
    void deleteDataStream();
};

CmdPortTest::CmdPortTest()
{
    db = &DB::getInstance();
}

CmdPortTest::~CmdPortTest()
{

}

void CmdPortTest::init()
{
    cmd = new CmdPort(SERVER_COMMAND_STREAM_SOCKET, ADDRESS_STRUCT);
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
    db->addAccountInfo(ACCOUNT);
    QVERIFY_EXCEPTION_THROWN(cmd->execute(), CmdPort::CannotConnectException);
}

void CmdPortTest::test_execute_and_getDataStreamSocket_accountCreated_clientStartDataStream_resultConnected()
{
    createDataStream();
    waitUntilServerReady();

    db->addAccountInfo(ACCOUNT);
    cmd->execute();
    QThread::msleep(WAIT_TIME_MS);
    QCOMPARE(fakeClient->isNewConnection(), true);
    QCOMPARE(fakeClient->isError(), false);
    close(cmd->getDataStreamSocket());
}

void CmdPortTest::test_getDataStreamSocket_notConected_resultDataStreamSocketNotExistsException()
{
    QVERIFY_EXCEPTION_THROWN(cmd->getDataStreamSocket(), CmdPort::DataStreamSocketNotExistsException);
}

const sockaddr_in CmdPortTest::createAddressStruct() const
{
    sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(CLIENT_DATA_STREAM_SOCKET);
    inet_pton(AF_INET, CLIENT_ADDRESS.c_str(), &address.sin_addr);
    return address;
}

const AccountDatabase::AccountInfo CmdPortTest::createAccount() const
{
    DB::AccountInfo account;
    account.commandStreamSocket = SERVER_COMMAND_STREAM_SOCKET;
    return account;
}

void CmdPortTest::createDataStream()
{
    fakeClient = new FakeClientDataServer(ADDRESS_STRUCT);
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
