#include <QtTest>
#include "FakeTransmissionClasses.h"
#include <QTextStream>

#include "transmission/transmission.h"

class TransmissionTest : public QObject
{
    Q_OBJECT
    FakeClass *transmission;
    QFile notExistFile = QFile("notExistFile");
    const QString CLIENT_INPUT_DATA = "CLIENT_INPUT_DATA";
    const char EOF_BYTES[3] = {0x7F, 0x2, '\0'};
public:
    TransmissionTest();
    ~TransmissionTest();

private slots:
    void test_send_openingError_resultFileOpeningException();
    void test_send_resultTextSent();
    void test_receive_resultTextReceived();

private:
    void prepareClientInputFile(QTemporaryFile &clientInput);
    QString readClientOutputFile(QTemporaryFile &clientOutput);
};

TransmissionTest::TransmissionTest()
{
    transmission = new FakeClass;
}

TransmissionTest::~TransmissionTest()
{
    delete transmission;
}

void TransmissionTest::test_send_openingError_resultFileOpeningException()
{
    QTemporaryFile clientOutput;
    clientOutput.open();
    QVERIFY_EXCEPTION_THROWN(transmission->send(clientOutput.handle(), notExistFile),
                             TransmissionReaderInterface::FileOpeningException);
    clientOutput.close();
}

void TransmissionTest::test_send_resultTextSent()
{
    QTemporaryFile clientOutput, serverInput;
    clientOutput.open();
    transmission->send(clientOutput.handle(), serverInput);
    clientOutput.close();

    QCOMPARE(readClientOutputFile(clientOutput), FakeTransmissionReader::getSentText());
}

void TransmissionTest::test_receive_resultTextReceived()
{
    QTemporaryFile clientInput, serverOutput;
    prepareClientInputFile(clientInput);
    clientInput.open();
    transmission->receive(clientInput.handle(), serverOutput);
    QCOMPARE(transmission->getRecvData(), CLIENT_INPUT_DATA);
    clientInput.close();
}

void TransmissionTest::prepareClientInputFile(QTemporaryFile &clientInput)
{
    if(!clientInput.isOpen()) {
        clientInput.open();
    }

    QTextStream s(&clientInput);
    s << CLIENT_INPUT_DATA << EOF_BYTES;
    clientInput.close();
}

QString TransmissionTest::readClientOutputFile(QTemporaryFile &clientOutput)
{
    clientOutput.open();

    QDataStream fileStream(&clientOutput);
    int fileSize = static_cast<int>(clientOutput.size());

    QByteArray data(fileSize, '\0');
    fileStream.readRawData(data.data(), fileSize);

    QString dataString(data);

    clientOutput.close();
    return dataString;
}

QTEST_APPLESS_MAIN(TransmissionTest)

#include "tst_transmissiontest.moc"
