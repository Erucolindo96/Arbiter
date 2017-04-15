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

SOURCES += \
    Arbiter.cpp \
    Instruction.cpp \
    RealInstruction.cpp \
    Operand.cpp \
    Processor.cpp

HEADERS += \
    RealInstructions.hpp \
    Operand.hpp \
    Instruction.hpp \
    Arbiter.hpp \
    Processor.hpp
unix {
    target.path = /usr/lib
    INSTALLS += target
}
