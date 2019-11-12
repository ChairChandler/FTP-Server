#include <QtTest>

// add necessary includes here

class CmdModeTest : public QObject
{
    Q_OBJECT

public:
    CmdModeTest();
    ~CmdModeTest();

private slots:
    void test_case1();

};

CmdModeTest::CmdModeTest()
{

}

CmdModeTest::~CmdModeTest()
{

}

void CmdModeTest::test_case1()
{

}

QTEST_APPLESS_MAIN(CmdModeTest)

#include "tst_cmdmodetest.moc"
