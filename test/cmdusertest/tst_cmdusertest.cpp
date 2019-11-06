#include <QtTest>

// add necessary includes here

class cmdusertest : public QObject
{
    Q_OBJECT

public:
    cmdusertest();
    ~cmdusertest();

private slots:
    void test_case1();

};

cmdusertest::cmdusertest()
{

}

cmdusertest::~cmdusertest()
{

}

void cmdusertest::test_case1()
{

}

QTEST_APPLESS_MAIN(cmdusertest)

#include "tst_cmdusertest.moc"
