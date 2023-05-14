
QT += core
QT       += core gui
QT +=core gui sql
QT+=sql

QT       += core gui multimedia
QT += multimedia
CONFIG += resources_big
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat
CONFIG += c++17

QMAKE_CXXFLAGS += -std:c++17 -Zc:__cplusplus
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

QT +=multimedia \
     multimediawidgets

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
    DATA/Story/character.cpp \
    DATA/Story/storyoption.cpp \
    DATA/instruction.cpp \
    DATA/instructionsolver.cpp \
    DATA/sqlitesolve.cpp \
    TOOLS/PLayer/player.cpp \
    TOOLS/PLayer/playercontrols.cpp \
    TOOLS/PLayer/playlistmodel.cpp \
    TOOLS/PLayer/qmediaplaylist.cpp \
    TOOLS/PLayer/qplaylistfileparser.cpp \
    TOOLS/PLayer/videowidget.cpp \
    TOOLS/achievementmanager.cpp \
    TOOLS/callcard.cpp \
    TOOLS/cardsearch.cpp \
    TOOLS/datareader.cpp \
    TOOLS/jsreader.cpp \
    TOOLS/jssaver.cpp \
    TOOLS/musicplayer.cpp \
    TOOLS/nowachievement.cpp \
    TOOLS/storyshowlabel.cpp \
    TOOLS/updater.cpp \
    UI/SPECIAL/ripple.cpp \
    UI/SPECIAL/rippleeffect.cpp \
    UI/chievementwidget.cpp \
    UI/choicelabel.cpp \
    UI/jumplabel.cpp \
    UI/menuwidget.cpp \
    UI/rswidget.cpp \
    UI/settingwidget.cpp \
    UI/style.cpp \
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
    DATA/Story/character.h \
    DATA/Story/storyoption.h \
    DATA/instruction.h \
    DATA/instructionsolver.h \
    DATA/sqlitesolve.h \
    TOOLS/PLayer/player.h \
    TOOLS/PLayer/playercontrols.h \
    TOOLS/PLayer/playlistmodel.h \
    TOOLS/PLayer/qmediaplaylist.h \
    TOOLS/PLayer/qmediaplaylist_p.h \
    TOOLS/PLayer/qplaylistfileparser_p.h \
    TOOLS/PLayer/videowidget.h \
    TOOLS/achievementmanager.h \
    TOOLS/callcard.h \
    TOOLS/cardsearch.h \
    TOOLS/datareader.h \
    TOOLS/jsreader.h \
    TOOLS/jssaver.h \
    TOOLS/musicplayer.h \
    TOOLS/nowachievement.h \
    TOOLS/storyshowlabel.h \
    TOOLS/updater.h \
    UI/SPECIAL/ripple.h \
    UI/SPECIAL/rippleeffect.h \
    UI/chievementwidget.h \
    UI/choicelabel.h \
    UI/jumplabel.h \
    UI/menuwidget.h \
    UI/rswidget.h \
    UI/settingwidget.h \
    UI/style.h \
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

RESOURCES += \
    CardImage.qrc
    win32: {
        QMAKE_CXXFLAGS += /permissive-
    }

    MSVC: {
        QMAKE_CXXFLAGS += /permissive-
    }
