#include <QtTest>

// add necessary includes here

class CmdStruTest : public QObject
{
    Q_OBJECT

public:
    CmdStruTest();
    ~CmdStruTest();

private slots:
    void test_case1();

};

CmdStruTest::CmdStruTest()
{

}

CmdStruTest::~CmdStruTest()
{

}

void CmdStruTest::test_case1()
{

}

QTEST_APPLESS_MAIN(CmdStruTest)

#include "tst_cmdstrutest.moc"
