QT += core
QT -= gui

CONFIG += c++11

TARGET = backupcameradriver
TEMPLATE = app
CONFIG += console

LIBS += -lSDL2_image -lSDL2
CONFIG += link_pkgconfig
PKGCONFIG += opencv

INCLUDEPATH += /usr/local/include/SDL2/

SOURCES += \
    BackupCamera.cpp \
    GraphicsHandler.cpp \
    main.cpp \
    VideoStream.cpp

HEADERS += \
    BackupCamera.h \
    GraphicsHandler.h \
    ThreadClass.hpp \
    VideoStream.hpp

