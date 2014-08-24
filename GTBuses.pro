TEMPLATE = app

QT += qml quick widgets network

SOURCES += main.cpp \
    route.cpp \
    direction.cpp \
    stop.cpp \
    directionmodel.cpp \
    mainwindow.cpp \
    gtwikibusfetcher.cpp

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
    gtwikibusfetcher.h
