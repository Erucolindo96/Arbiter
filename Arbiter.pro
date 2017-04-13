#-------------------------------------------------
#
# Project created by QtCreator 2017-03-31T19:18:56
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = Arbiter
TEMPLATE = lib
CONFIG += staticlib

SOURCES += arbiter.cpp \
    instruction.cpp \
    operand.cpp

HEADERS += arbiter.hpp \
    instruction.hpp \
    operand.hpp
unix {
    target.path = /usr/lib
    INSTALLS += target
}
