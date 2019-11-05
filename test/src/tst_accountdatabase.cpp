#include <QtTest>

// add necessary includes here

class AccountDatabase : public QObject
{
    Q_OBJECT

public:
    AccountDatabase();
    ~AccountDatabase();

private slots:
    void test_case1();

};

AccountDatabase::AccountDatabase()
{

}

AccountDatabase::~AccountDatabase()
{

}

void AccountDatabase::test_case1()
{

}

QTEST_APPLESS_MAIN(AccountDatabase)

#include "tst_accountdatabase.moc"
