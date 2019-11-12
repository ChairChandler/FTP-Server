#include <QtTest>

// add necessary includes here

class CmdTypeTest : public QObject
{
    Q_OBJECT

public:
    CmdTypeTest();
    ~CmdTypeTest();

private slots:
    void test_case1();

};

CmdTypeTest::CmdTypeTest()
{

}

CmdTypeTest::~CmdTypeTest()
{

}

void CmdTypeTest::test_case1()
{

}

QTEST_APPLESS_MAIN(CmdTypeTest)

#include "tst_cmdtypetest.moc"
