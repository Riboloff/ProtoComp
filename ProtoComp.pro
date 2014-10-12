TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    main.cpp

HEADERS += \
    Grammar.h \
    Notion.h \
    Parser.h \
    ReadFile.h \
    TableSymbol.h \
    Token.h \
    Sentence.h \
    DumperGrammar.h \
    Lexer.h \
    ExceptionStorage.h


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../usr/local/lib/release/ -lboost_regex
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../usr/local/lib/debug/ -lboost_regex
else:unix: LIBS += -L$$PWD/../../../../../usr/local/lib/ -lboost_regex

INCLUDEPATH += $$PWD/../../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../../usr/local/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../usr/local/lib/release/libboost_regex.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../usr/local/lib/debug/libboost_regex.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../usr/local/lib/release/boost_regex.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../usr/local/lib/debug/boost_regex.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../../../../usr/local/lib/libboost_regex.a
