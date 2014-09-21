TEMPLATE = app

QT += qml quick widgets network

CONFIG += c++11

SOURCES += main.cpp \
    route.cpp \
    direction.cpp \
    stop.cpp \
    directionmodel.cpp \
    mainwindow.cpp \
    gtwikibusfetcher.cpp \
    routemodel.cpp \
    stopmodel.cpp \
    bus.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    route.h \
    direction.h \
    stop.h \
    directionmodel.h \
    mainwindow.h \
    gtwikibusfetcher.h \
    routemodel.h \
    stopmodel.h \
    bus.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../geos/release/ -lgeos
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../geos/debug/ -lgeos
else:unix: LIBS += -L$$OUT_PWD/../geos/ -lgeos
ANDROID_EXTRA_LIBS += $$OUT_PWD/../geos/libgeos.so

INCLUDEPATH += $$PWD/../geos/include
DEPENDPATH += $$PWD/../geos/include
