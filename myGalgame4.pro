
QT += core
QT       += core gui
QT +=core gui sql
QT+=sql


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DATA/Card/cardbase.cpp \
    DATA/Card/cardcharacter.cpp \
    DATA/Card/cardequipment.cpp \
    DATA/Card/cardprop.cpp \
    DATA/Model/modelbase.cpp \
    DATA/Model/modelbattle.cpp \
    DATA/Model/modelbuff.cpp \
    DATA/Model/modelgesture.cpp \
    DATA/Model/modellove.cpp \
    DATA/Model/modelstory.cpp \
    DATA/Model/modelstratagy.cpp \
    DATA/Player/playerai.cpp \
    DATA/Player/playerbase.cpp \
    DATA/Player/playeruser.cpp \
    DATA/sqlitesolve.cpp \
    TOOLS/callcard.cpp \
    TOOLS/cardsearch.cpp \
    TOOLS/storyshowlabel.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    DATA/Card/cardbase.h \
    DATA/Card/cardcharacter.h \
    DATA/Card/cardequipment.h \
    DATA/Card/cardprop.h \
    DATA/Model/modelbase.h \
    DATA/Model/modelbattle.h \
    DATA/Model/modelbuff.h \
    DATA/Model/modelgesture.h \
    DATA/Model/modellove.h \
    DATA/Model/modelstory.h \
    DATA/Model/modelstratagy.h \
    DATA/Player/playerai.h \
    DATA/Player/playerbase.h \
    DATA/Player/playeruser.h \
    DATA/sqlitesolve.h \
    TOOLS/callcard.h \
    TOOLS/cardsearch.h \
    TOOLS/storyshowlabel.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    myGalgame4_zh_CN.ts


INCLUDEPATH+=  \
    DATA       \
    DATA/Card  \
    DATA/Model \
    DATA/Player \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    TOOLS/新建 文本文档.txt \
    TOOLS/新建 文本文档.txt
