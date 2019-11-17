#include <QtTest>

// add necessary includes here

class TransmissionTest : public QObject
{
    Q_OBJECT

public:
    TransmissionTest();
    ~TransmissionTest();

private slots:
    void test_case1();

};

TransmissionTest::TransmissionTest()
{

}

TransmissionTest::~TransmissionTest()
{

}

void TransmissionTest::test_case1()
{

}

QTEST_APPLESS_MAIN(TransmissionTest)

#include "tst_transmissiontest.moc"
