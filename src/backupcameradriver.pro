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

SOURCES += main.cpp \
    backup_camera.cpp \
    graphics_handler.cpp \
    videoStream.cpp

HEADERS += \
    backup_camera.h \
    graphics_handler.h \
    I_displayable.h \
    threadClass.hpp \
    videoStream.hpp
