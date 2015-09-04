#-------------------------------------------------
#
# Project created by QtCreator 2015-08-31T13:16:01
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Project
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Message/someMessage.cpp \
    Message/someMessageCommunicator.cpp \
    Message/someMessageClient.cpp \
    Message/someMessageServer.cpp \
    Message/somePlainMessage.cpp \
    Test/someClientTest.cpp \
    Test/someServerTest.cpp \
    Message/someMessageManager.cpp \
    Message/someCoordinateMessage.cpp \
    Message/someNotifyMessage.cpp \
    Message/someTimeCountMessage.cpp \
    gameController.cpp \
    Message/someLoadMessage.cpp \
    GamePanel.cpp \
    ViewComponent/gameviewpanel.cpp \
    ViewComponent/gamemessagebox.cpp \
    ViewComponent/gamebutton.cpp \
    mypainter.cpp \
    ViewComponent/GameEnterNumberBox.cpp \
    ViewComponent/GameEntranceInterface.cpp \
    ViewComponent/gamesizechangebutton.cpp \
    ViewComponent/GameBackSliderPlayer.cpp \
    GameAudioPlayer.cpp \
    ViewComponent/GameStateViewer.cpp \
    ViewComponent/gamechoosebox.cpp \
    ViewComponent/GameLoadFilePanel.cpp \
    ViewComponent/GameTypeBox.cpp \
    ViewComponent/GameMessageViewer.cpp \
    Message/someChatMessage.cpp

HEADERS  += mainwindow.h \
    Message/someMessage.h \
    Message/someMessageCommunicator.h \
    Message/someMessageClient.h \
    Message/someMessageServer.h \
    Message/somePlainMessage.h \
    Test/someClientTest.h \
    Test/someServerTest.h \
    Message/someMessageManager.h \
    Message/someCoordinateMessage.h \
    Message/someNotifyMessage.h \
    Message/someTimeCountMessage.h \
    gameController.h \
    Message/someLoadMessage.h \
    GamePanel.h \
    ViewComponent/gameviewpanel.h \
    ViewComponent/gamemessagebox.h \
    ViewComponent/gamebutton.h \
    mypainter.h \
    ViewComponent/GameEnterNumberBox.h \
    ViewComponent/GameEntranceInterface.h \
    ViewComponent/gamesizechangebutton.h \
    ViewComponent/GameBackSliderPlayer.h \
    GameAudioPlayer.h \
    ViewComponent/GameStateViewer.h \
    global.h \
    ViewComponent/gamechoosebox.h \
    ViewComponent/GameLoadFilePanel.h \
    ViewComponent/GameTypeBox.h \
    ViewComponent/GameMessageViewer.h \
    Message/someChatMessage.h

FORMS    += mainwindow.ui \
    Test/someClientTest.ui \
    Test/someServerTest.ui
