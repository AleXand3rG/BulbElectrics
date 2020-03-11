#-------------------------------------------------
#
# app.pro file created by A. 2019-05-25T16:45:34
#
#-------------------------------------------------

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT       += core gui
QT       += svg
QT       += printsupport

#proe-19l-2
TARGET = ../proe-19l-2

CONFIG += gui
CONFIG += c++11

TEMPLATE = app

SOURCES += \
    colordialog.cpp \
    editelementdialog.cpp \
    emmiter.cpp \
    main.cpp \
    mainwindow.cpp \
    newelementdialog.cpp \

HEADERS += \
    colordialog.h \
    editelementdialog.h \
    emmiter.h \
    mainwindow.h \
    newelementdialog.h

FORMS += \
    colordialog.ui \
    editelementdialog.ui \
    mainwindow.ui \
    newelementdialog.ui


#libFiguresPDAG
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../lib/release/ -lFiguresPDAG
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../lib/debug/ -lFiguresPDAG
else:unix: LIBS += -L$$OUT_PWD/../lib/ -lFiguresPDAG

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib/release/libFiguresPDAG.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib/debug/libFiguresPDAG.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib/release/FiguresPDAG.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib/debug/FiguresPDAG.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../lib/libFiguresPDAG.a

#include & install headers
INCLUDEPATH += $$PWD/../lib
DEPENDPATH += $$PWD/../lib

headersDataFiles.path = $$[QT_INSTALL_HEADERS]
headersDataFiles.files = $$PWD/../lib/*.hpp
INSTALLS += headersDataFiles
libraryFiles.path = $$[QT_INSTALL_LIBS]
CONFIG(debug, debug|release):libraryFiles.files = $$OUT_PWD/debug/*.a $$OUT_PWD/debug/*.prl
CONFIG(release, debug|release):libraryFiles.files = $$OUT_PWD/release/*.a $$OUT_PWD/release/*.prl
INSTALLS += libraryFiles
