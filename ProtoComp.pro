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
    DumperGrammar.h


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../c_plus_plus/boost2/boost_1_55_0/stage/lib/release/ -lboost_regex
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../c_plus_plus/boost2/boost_1_55_0/stage/lib/debug/ -lboost_regex
else:unix: LIBS += -L$$PWD/../c_plus_plus/boost2/boost_1_55_0/stage/lib/ -lboost_regex

INCLUDEPATH += $$PWD/../c_plus_plus/boost2/boost_1_55_0
DEPENDPATH += $$PWD/../c_plus_plus/boost2/boost_1_55_0

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../c_plus_plus/boost2/boost_1_55_0/stage/lib/release/libboost_regex.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../c_plus_plus/boost2/boost_1_55_0/stage/lib/debug/libboost_regex.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../c_plus_plus/boost2/boost_1_55_0/stage/lib/release/boost_regex.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../c_plus_plus/boost2/boost_1_55_0/stage/lib/debug/boost_regex.lib
else:unix: PRE_TARGETDEPS += $$PWD/../c_plus_plus/boost2/boost_1_55_0/stage/lib/libboost_regex.a
