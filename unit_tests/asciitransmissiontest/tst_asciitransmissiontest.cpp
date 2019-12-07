#include <QtTest>
#include "bsdsocketfactory.h"
#include "fakeit.hpp"
#pragma GCC diagnostic ignored "-Wpadded"
#pragma GCC diagnostic ignored "-Wpragmas" //turn off warning about below turning warning off
#pragma GCC diagnostic ignored "-Wdisabled-macro-expansion"

#include "transmission/types/asciitransmission.h"

using namespace fakeit;

class AsciiTransmissionTest : public QObject
{
    Q_OBJECT
    using Stream = QTemporaryFile;
    QFile notExistFile = QFile("notExistFile");
    const QString SERVER_INPUT_DATA = "SERVER_INPUT_DATA";
    const QString CLIENT_INPUT_DATA = "CLIENT_INPUT_DATA";
    const QByteArray EOF_BYTES = {"\x7F\x02", 2};
    const int DATA_CHANNEL_SOCKET = 0;

public:
    AsciiTransmissionTest();
    ~AsciiTransmissionTest();
    Transmission *transmission;

private slots:
    void cleanup();
    void test_send_openingError_resultFileOpeningException();
    void test_send_textShorterThanBuffer_resultFileSent();
    void test_receive_textShorterThanBuffer_resultFileReceived();
    void test_send_textLongerThanBuffer_resultFileSent();
    void test_receive_textLongerThanBuffer_resultFileReceived();

private:
    void prepareClientInputStream(Stream &clientInput, QString txt);
    void prepareServerInput(QTemporaryFile &file, QString txt);
    QString prepareRandomText(size_t size);
    QString readClientStream(Stream &stream);
    QString readFile(QTemporaryFile &file);
};

AsciiTransmissionTest::AsciiTransmissionTest()
{
    transmission = new AsciiTransmission();
}

AsciiTransmissionTest::~AsciiTransmissionTest()
{
    delete transmission;
}

void AsciiTransmissionTest::cleanup()
{
    Transmission::setBsdSocketFactory(BsdSocketFactoryDefault());
}

void AsciiTransmissionTest::test_send_openingError_resultFileOpeningException()
{
    Mock<QFile> notExistFile;
    When(OverloadedMethod(notExistFile, open, bool(QFile::OpenMode))).Return(false);

    QVERIFY_EXCEPTION_THROWN(transmission->send(DATA_CHANNEL_SOCKET, notExistFile.get()),
                             AsciiTransmission::FileOpeningException);
}

void AsciiTransmissionTest::test_send_textShorterThanBuffer_resultFileSent()
{
    Mock<QFile> file;
    When(OverloadedMethod(file, open, bool(QFile::OpenMode))).Return(true);

    Mock<BsdSocketFactory> bsdSocketFactory;
    When(Method(bsdSocketFactory, write)).AlwaysDo([](int __fd, const void *__buf, size_t __n){return -1;});
    Transmission::setBsdSocketFactory(bsdSocketFactory.get());

    transmission->send(DATA_CHANNEL_SOCKET, file.get());

    QCOMPARE(readClientStream(clientOutput), SERVER_INPUT_DATA + EOF_BYTES);
}

void AsciiTransmissionTest::test_receive_textShorterThanBuffer_resultFileReceived()
{
    Stream clientInput;
    QTemporaryFile serverOutput;

    prepareClientInputStream(clientInput, CLIENT_INPUT_DATA);
    clientInput.open();
    transmission->receive(clientInput.handle(), serverOutput);

    QCOMPARE(readFile(serverOutput), CLIENT_INPUT_DATA);
    clientInput.close();
}

void AsciiTransmissionTest::test_send_textLongerThanBuffer_resultFileSent()
{
    Stream clientOutput;
    QTemporaryFile serverInput;

    QString txt = prepareRandomText(Transmission::getBuffSize()*10);
    prepareServerInput(serverInput, txt);
    clientOutput.open();
    transmission->send(clientOutput.handle(), serverInput);
    clientOutput.close();

    QCOMPARE(readClientStream(clientOutput), txt + EOF_BYTES);
}

void AsciiTransmissionTest::test_receive_textLongerThanBuffer_resultFileReceived()
{
    Stream clientInput;
    QTemporaryFile serverOutput;

    QString txt = prepareRandomText(Transmission::getBuffSize()*10);
    prepareClientInputStream(clientInput, txt);
    clientInput.open();
    transmission->receive(clientInput.handle(), serverOutput);

    QCOMPARE(readFile(serverOutput), txt);
    clientInput.close();
}

void AsciiTransmissionTest::prepareClientInputStream(Stream &clientInput, QString txt)
{
    if(!clientInput.isOpen()) {
        clientInput.open();
    }

    QTextStream s(&clientInput);
    s << txt << EOF_BYTES;
    clientInput.close();
}

void AsciiTransmissionTest::prepareServerInput(QTemporaryFile &file, QString txt)
{
    if(!file.isOpen()) {
        file.open();
    }

    QTextStream s(&file);
    s << txt;
    file.close();
}

QString AsciiTransmissionTest::prepareRandomText(size_t size)
{
    QString ret;
    for(size_t i=0; i<size; i++) {
        ret += qrand()%('z' - 'A' + 1) + 'A';
    }
    return ret;
}

QString AsciiTransmissionTest::readClientStream(Stream &stream)
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

QString AsciiTransmissionTest::readFile(QTemporaryFile &file)
{
    file.open();
    QString txt(file.readAll());
    file.close();

    return txt;
}

QTEST_APPLESS_MAIN(AsciiTransmissionTest)

#include "tst_asciitransmissiontest.moc"
