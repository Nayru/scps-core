#-------------------------------------------------
#
# Project created by QtCreator 2013-01-25T16:49:41
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = scps-core
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    data.cpp \
    argument.cpp \
    instruction.cpp \
    protocol.cpp \
    protocol.math.cpp \
    protocol.jump.cpp \
    protocol.stack.cpp

HEADERS += \
    data.h \
    argument.h \
    instruction.h \
    protocol.h \
    protocol.math.h \
    protocol.jump.h \
    protocol.stack.h

unix|win32: LIBS += -lgmp

unix|win32: LIBS += -lgmpxx
