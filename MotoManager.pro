QT += core widgets multimedia

TARGET = MotoManager
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

SOURCES += \
        main.cpp \
        MotoManager.cpp

HEADERS += \
        MotoManager.h
        
RESOURCES += \
        MotoManager.qrc