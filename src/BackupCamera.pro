QT += core
QT -= gui

CONFIG += c++11

TARGET = BackupCamera
TEMPLATE = app
CONFIG += console

LIBS += -lSDL2_image -lSDL2 `pkg-config --libs opencv`


INCLUDEPATH += /usr/local/include/SDL2/ /usr/include/opencv/

OBJECTS_DIR = ../build/.obj
DESTDIR = ../build/

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

