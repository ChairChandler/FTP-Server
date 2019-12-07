#include <QtTest>
#include "FakeTransmissionClasses.h"
#include <QTextStream>

#include "transmission/transmission.h"

class TransmissionTest : public QObject
{
    Q_OBJECT
    using Stream = QTemporaryFile;
    FakeClass *transmission;
    QFile notExistFile = QFile("notExistFile");
    const QString CLIENT_INPUT_DATA = "CLIENT_INPUT_DATA";
    const QByteArray EOF_BYTES = {"\x7F\x02", 2};

public:
    TransmissionTest();
    ~TransmissionTest();

private slots:
    void test_send_openingError_resultFileOpeningException();
    void test_send_textShorterThanBuffer_resultTextSent();
    void test_receive_textShorterThanBuffer_resultTextReceived();
    void test_send_textLongerThanBuffer_resultTextSent();
    void test_receive_textLongerThanBuffer_resultTextReceived();

private:
    void prepareClientInputStream(Stream &clientInput);
    QString readClientStream(Stream &stream);
    QString prepareRandomText(size_t size);
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
    Stream clientOutput;
    clientOutput.open();
    QVERIFY_EXCEPTION_THROWN(transmission->send(clientOutput.handle(), notExistFile),
                             TransmissionReaderInterface::FileOpeningException);
    clientOutput.close();
}

void TransmissionTest::test_send_textShorterThanBuffer_resultTextSent()
{
    Stream clientOutput;
    QTemporaryFile serverInput;

    clientOutput.open();
    transmission->send(clientOutput.handle(), serverInput);
    clientOutput.close();

    QCOMPARE(readClientStream(clientOutput), FakeTransmissionReader::getSentText() + EOF_BYTES);
}

void TransmissionTest::test_receive_textShorterThanBuffer_resultTextReceived()
{
    Stream clientInput;
    QTemporaryFile serverOutput;

    prepareClientInputStream(clientInput);
    clientInput.open();
    transmission->receive(clientInput.handle(), serverOutput);

    QCOMPARE(transmission->getRecvData(), CLIENT_INPUT_DATA);
    clientInput.close();
}

void TransmissionTest::test_send_textLongerThanBuffer_resultTextSent()
{
    Stream clientOutput;
    QTemporaryFile serverInput;

    QString txt = prepareRandomText(Transmission::getBuffSize() * 10);
    clientOutput.open();
    transmission->send(clientOutput.handle(), serverInput);
    clientOutput.close();

    QCOMPARE(readClientStream(clientOutput), txt + EOF_BYTES);
}

void TransmissionTest::test_receive_textLongerThanBuffer_resultTextReceived()
{
    Stream clientInput;
    QTemporaryFile serverOutput;

    prepareClientInputStream(clientInput);
    clientInput.open();
    transmission->receive(clientInput.handle(), serverOutput);

    QCOMPARE(transmission->getRecvData(), CLIENT_INPUT_DATA);
    clientInput.close();
}

void TransmissionTest::prepareClientInputStream(Stream &clientInput)
{
    if(!clientInput.isOpen()) {
        clientInput.open();
    }

    QTextStream s(&clientInput);
    s << CLIENT_INPUT_DATA << EOF_BYTES;
    clientInput.close();
}

QString TransmissionTest::readClientStream(Stream &stream)
{
    stream.open();

    QDataStream fileStream(&stream);
    int fileSize = static_cast<int>(stream.size());

    QByteArray data(fileSize, '\0');
    fileStream.readRawData(data.data(), fileSize);

    QString dataString(data);

    stream.close();
    return dataString;
}

QString TransmissionTest::prepareRandomText(size_t size)
{
    QString ret;
    for(size_t i=0; i<size; i++) {
        ret += qrand()%('z' - 'A' + 1) + 'A';
    }
    return ret;
}

QTEST_APPLESS_MAIN(TransmissionTest)

#include "tst_transmissiontest.moc"
