#-------------------------------------------------
#
# Project created by QtCreator 2013-10-12T22:26:31
#
#-------------------------------------------------

CONFIG = staticlib

QT       -= core gui

TARGET = ihanclient
TEMPLATE = lib

DEFINES += MUSCLE_SINGLE_THREAD_ONLY

SOURCES += src/varcontainer.cpp \
    src/ZBLocations.cpp \
    muscle/message/Message.cpp \
    muscle/util/String.cpp \
    muscle/util/SocketMultiplexer.cpp \
    muscle/util/PulseNode.cpp \
    muscle/util/NetworkUtilityFunctions.cpp \
    muscle/util/FilePathInfo.cpp \
    muscle/util/ByteBuffer.cpp \
    muscle/syslog/SysLog.cpp \
    muscle/iogateway/MessageIOGateway.cpp \
    muscle/iogateway/AbstractMessageIOGateway.cpp \
    muscle/system/SetupSystem.cpp

HEADERS += include/varcontainer.hpp \
    include/config.h \
    include/ZBLocations.hpp \
    include/ZBHAProfiles.hpp \
    include/MsgTypes.hpp \
    include/DeviceTypes.hpp \
    muscle/message/Message.h \
    muscle/util/String.h \
    muscle/util/SocketMultiplexer.h \
    muscle/util/PulseNode.h \
    muscle/util/NetworkUtilityFunctions.h \
    muscle/util/FilePathInfo.h \
    muscle/util/ByteBuffer.h \
    muscle/syslog/SysLog.h \
    muscle/syslog/LogCallback.h \
    muscle/iogateway/MessageIOGateway.h \
    muscle/iogateway/AbstractMessageIOGateway.h \
    muscle/system/SetupSystem.h

INCLUDEPATH += include/ muscle/

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
