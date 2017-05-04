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
QMAKE_CXXFLAGS += -std=c++11 #dodane przeze mnie

SOURCES += \
    Arbiter.cpp \
    Instruction.cpp \
    Operand.cpp \
    Processor.cpp \
    Queuemanager.cpp \
    Process.cpp \
    Core.cpp \
    IntegerRegister.cpp \
    RealInstruction.cpp \
    RealOperands.cpp \
    ExecutionLog.cpp \
    main.cpp \
    CoreCreator.cpp

HEADERS += \
    Operand.hpp \
    Instruction.hpp \
    Arbiter.hpp \
    Processor.hpp \
    Queuemanager.hpp \
    Process.hpp \
    Core.hpp \
    IntegerRegister.hpp \
    ExecutionLog.hpp \
    RealInstructions.hpp \
    RealOperands.hpp \
    CoreCreator.hpp
unix {
    target.path = /usr/lib
    INSTALLS += target
}
