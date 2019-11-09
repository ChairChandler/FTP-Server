#include <QtTest>

// add necessary includes here

class CmdPortTest : public QObject
{
    Q_OBJECT

public:
    CmdPortTest();
    ~CmdPortTest();

private slots:
    void test_case1();

};

CmdPortTest::CmdPortTest()
{

}

CmdPortTest::~CmdPortTest()
{

}

void CmdPortTest::test_case1()
{

}

QTEST_APPLESS_MAIN(CmdPortTest)

#include "tst_cmdporttest.moc"
