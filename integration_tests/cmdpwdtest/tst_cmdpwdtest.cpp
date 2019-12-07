#include <QtTest>

#include "cmds/cmdpwd.h"

class CmdPwdTest : public QObject
{
    Q_OBJECT

public:
    CmdPwdTest();
    ~CmdPwdTest();

private slots:
    void test_case1();

};

CmdPwdTest::CmdPwdTest()
{

}

CmdPwdTest::~CmdPwdTest()
{

}

void CmdPwdTest::test_case1()
{

}

QTEST_APPLESS_MAIN(CmdPwdTest)

#include "tst_cmdpwdtest.moc"
