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
    Processor.cpp \
    Queuemanager.cpp \
    process.cpp \
    interegregister.cpp

HEADERS += \
    RealInstructions.hpp \
    Operand.hpp \
    Instruction.hpp \
    Arbiter.hpp \
    Processor.hpp \
    Queuemanager.hpp \
    process.hpp \
    interegregister.hpp
unix {
    target.path = /usr/lib
    INSTALLS += target
}
