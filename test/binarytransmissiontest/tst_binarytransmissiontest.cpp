#include <QtTest>
#pragma GCC diagnostic ignored "-Wpadded"

#include "transmission/types/binarytransmission.h"

class BinaryTransmissionTest : public QObject
{
    Q_OBJECT
    using Stream = QTemporaryFile;
    QFile notExistFile = QFile("notExistFile");
    const QByteArray SERVER_INPUT_DATA = QByteArray::fromStdString("SERVER_INPUT_DATA");
    const QByteArray CLIENT_INPUT_DATA = QByteArray::fromStdString("CLIENT_INPUT_DATA");
    const QByteArray EOF_BYTES = {"\x7F\x02", 2};

public:
    BinaryTransmissionTest();
    ~BinaryTransmissionTest();
    Transmission *transmission;

private slots:
    void test_send_openingError_resultFileOpeningException();
    void test_send_dataShorterThanBuffer_resultFileSent();
    void test_receive_dataShorterThanBuffer_resultFileReceived();
    void test_send_dataLongerThanBuffer_resultFileSent();
    void test_receive_dataLongerThanBuffer_resultFileReceived();

private:
    void prepareClientInputStream(Stream &clientInput, QByteArray data);
    void prepareServerInput(QTemporaryFile &file, QByteArray data);
    QString readClientStream(Stream &stream);
    QString readFile(QTemporaryFile &file);
    QByteArray prepareRandomData(size_t size);
};

BinaryTransmissionTest::BinaryTransmissionTest()
{
    transmission = new BinaryTransmission();
}

BinaryTransmissionTest::~BinaryTransmissionTest()
{
    delete transmission;
}

void BinaryTransmissionTest::test_send_openingError_resultFileOpeningException()
{
    Stream clientOutput;
    clientOutput.open();
    QVERIFY_EXCEPTION_THROWN(transmission->send(clientOutput.handle(), notExistFile),
                             BinaryTransmission::FileOpeningException);
    clientOutput.close();
}

void BinaryTransmissionTest::test_send_dataShorterThanBuffer_resultFileSent()
{
    Stream clientOutput;
    QTemporaryFile serverInput;

    prepareServerInput(serverInput, SERVER_INPUT_DATA);
    clientOutput.open();
    transmission->send(clientOutput.handle(), serverInput);
    clientOutput.close();

    QCOMPARE(readClientStream(clientOutput), SERVER_INPUT_DATA + EOF_BYTES);
}

void BinaryTransmissionTest::test_receive_dataShorterThanBuffer_resultFileReceived()
{
    Stream clientInput;
    QTemporaryFile serverOutput;

    prepareClientInputStream(clientInput, CLIENT_INPUT_DATA);
    clientInput.open();
    transmission->receive(clientInput.handle(), serverOutput);

    QCOMPARE(readFile(serverOutput), CLIENT_INPUT_DATA);
    clientInput.close();
}

void BinaryTransmissionTest::test_send_dataLongerThanBuffer_resultFileSent()
{
    Stream clientOutput;
    QTemporaryFile serverInput;

    QByteArray data = prepareRandomData(Transmission::getBuffSize() * 10);
    prepareServerInput(serverInput, data);
    clientOutput.open();
    transmission->send(clientOutput.handle(), serverInput);
    clientOutput.close();

    QCOMPARE(readClientStream(clientOutput), data + EOF_BYTES);
}

void BinaryTransmissionTest::test_receive_dataLongerThanBuffer_resultFileReceived()
{
    Stream clientInput;
    QTemporaryFile serverOutput;

    QByteArray data = prepareRandomData(Transmission::getBuffSize() * 10);
    prepareClientInputStream(clientInput, data);
    clientInput.open();
    transmission->receive(clientInput.handle(), serverOutput);

    QCOMPARE(readFile(serverOutput), data);
    clientInput.close();
}

void BinaryTransmissionTest::prepareClientInputStream(Stream &clientInput, QByteArray data)
{
    if(!clientInput.isOpen()) {
        clientInput.open();
    }

    clientInput.write(data);
    clientInput.write(EOF_BYTES);
    clientInput.close();
}

void BinaryTransmissionTest::prepareServerInput(QTemporaryFile &file, QByteArray data)
{
    if(!file.isOpen()) {
        file.open();
    }

    file.write(data);
    file.close();
}

QString BinaryTransmissionTest::readClientStream(Stream &stream)
{
    return readFile(stream);
}

QString BinaryTransmissionTest::readFile(QTemporaryFile &file)
{
    file.open();
    QDataStream fileStream(&file);
    int fileSize = static_cast<int>(file.size());

    QByteArray data(fileSize, '\0');
    fileStream.readRawData(data.data(), fileSize);

    QString txt(data);
    file.close();

    return txt;
}

QByteArray BinaryTransmissionTest::prepareRandomData(size_t size)
{
    QByteArray ret;
    for(size_t i=0; i<size; i++) {
        ret += qrand()%127;
    }
    return ret;
}

QTEST_APPLESS_MAIN(BinaryTransmissionTest)

#include "tst_binarytransmissiontest.moc"
