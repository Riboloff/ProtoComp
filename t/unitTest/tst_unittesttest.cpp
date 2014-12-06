#include <QString>
#include <QtTest>

class UnitTestTest : public QObject
{
    Q_OBJECT

public:
    UnitTestTest();

private Q_SLOTS:
    void testCase1();
};

UnitTestTest::UnitTestTest()
{
}

void UnitTestTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(UnitTestTest)

#include "tst_unittesttest.moc"
