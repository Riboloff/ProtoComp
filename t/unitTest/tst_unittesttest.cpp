#include <QString>
#include <QtTest>
#include "../../Token.h"


class UnitTestTest : public QObject {
    Q_OBJECT

public:
    UnitTestTest();

private Q_SLOTS:
    void testCaseAddWord();
};

UnitTestTest::UnitTestTest() {
}

void UnitTestTest::testCaseAddWord() {
    Token token;
    map <string, string> test_hash;
    test_hash.insert(pair<string, string>("[", "bracket"));
    test_hash.insert(pair<string, string>("]", "bracket"));
    test_hash.insert(pair<string, string>("{", "bracket"));
    test_hash.insert(pair<string, string>("}", "bracket"));
    test_hash.insert(pair<string, string>("(", "bracket"));
    test_hash.insert(pair<string, string>(")", "bracket"));
    map<string, string>::iterator it;
    for (it = test_hash.begin(); it != test_hash.end(); ++it) {
        token.addWord(it->first);
        QCOMPARE(QString(token.getValue().c_str()), QString(it->first.c_str()));
        QCOMPARE(QString(token.getType().c_str()), QString(it->second.c_str()));
    }
}

QTEST_APPLESS_MAIN(UnitTestTest)

#include "tst_unittesttest.moc"
