QT       += core gui
QT += widgets
QT += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += debug_and_release
CONFIG(debug, debug|release){
    TARGET = ../../_debug/Tetris
} else {
    TARGET = ../../_release/Tetris
}
TEMPLATE = app


SOURCES += main.cpp\
    background.cpp \
    choosegame.cpp \
    history.cpp \
    keyboard.cpp \
    mainwindow.cpp \
    Item.cpp \
    GameArea.cpp \
    NextArea.cpp \
    mainwindow2.cpp \
    ranking.cpp \
    sethistory.cpp \
    setting.cpp \
    startwinodw.cpp \
    userhistory.cpp

HEADERS  += mainwindow.h \
    Item.h \
    GameArea.h \
    NextArea.h \
    background.h \
    choosegame.h \
    history.h \
    keyboard.h \
    mainwindow2.h \
    ranking.h \
    sethistory.h \
    setting.h \
    startwinodw.h \
    userhistory.h

FORMS    += mainwindow.ui \
    background.ui \
    choosegame.ui \
    history.ui \
    keyboard.ui \
    mainwindow2.ui \
    ranking.ui \
    sethistory.ui \
    setting.ui \
    startwinodw.ui \
    userhistory.ui

RESOURCES += \
    lastGame.qrc \
    rc.qrc

RC_FILE = app.rc

