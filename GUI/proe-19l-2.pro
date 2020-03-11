#-------------------------------------------------
#
# Project created by QtCreator 2019-05-22T11:22:26
#
#-------------------------------------------------

TEMPLATE = subdirs

SUBDIRS = libFiguresPDAG app
libFiguresPDAG.file = lib/libFiguresPDAG.pro
app.file = app/app.pro
app.depends = libFiguresPDAG

CONFIG += ordered

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.14
QMAKE_CFLAGS += -mmacosx-version-min=10.7
QMAKE_CXXFLAGS += -mmacosx-version-min=10.7
QMAKE_CFLAGS += -std=c++11 -stdlib=libc++
QMAKE_CXXFLAGS += -std=c++11 -stdlib=libc++
