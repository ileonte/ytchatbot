#-------------------------------------------------
#
# Project created by QtCreator 2015-09-05T01:11:36
#
#-------------------------------------------------

QT += core gui widgets webenginewidgets webchannel
linux-g++ {
        QMAKE_CXXFLAGS += -std=c++11
}

TARGET = YTChatBot
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    youtubelogin.cpp \
    ytloginproxy.cpp \
    utils.cpp \
    ytchatproxy.cpp \
    ytloginstatuswidget.cpp

HEADERS  += mainwindow.h \
    youtubelogin.h \
    ytloginproxy.h \
    utils.h \
    ytloginstatuswidget.h \
    ytchatproxy.h

RESOURCES += \
    res.qrc

DISTFILES +=
