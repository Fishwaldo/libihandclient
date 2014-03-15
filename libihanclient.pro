#-------------------------------------------------
#
# Project created by QtCreator 2014-03-15T21:59:46
#
#-------------------------------------------------

QT       -= core gui

TARGET = libihanclient
TEMPLATE = lib
CONFIG += lib_bundle c++11

SOURCES += src/LogClass.cpp \
    src/varcontainer.cpp \
    src/ZBLocations.cpp \
    muscle/message/Message.cpp \
    muscle/util/ByteBuffer.cpp \
    muscle/util/Directory.cpp \
    muscle/util/FilePathInfo.cpp \
    muscle/util/NetworkUtilityFunctions.cpp \
    muscle/util/PulseNode.cpp \
    muscle/util/SocketMultiplexer.cpp \
    muscle/util/String.cpp \
    muscle/system/SetupSystem.cpp \
    muscle/syslog/Syslog.cpp \
    muscle/iogateway/AbstractMessageIOGateway.cpp \
    muscle/iogateway/MessageIOGateway.cpp

HEADERS += include/iHanClient/DeviceTypes.hpp \
    include/iHanClient/LogClass.hpp \
    include/iHanClient/MsgTypes.hpp \
    include/iHanClient/varcontainer.hpp \
    include/iHanClient/ZBHAProfiles.hpp \
    include/iHanClient/ZBLocations.hpp \
    muscle/message/Message.h \
    muscle/util/ByteBuffer.h \
    muscle/util/Directory.h \
    muscle/util/FilePathInfo.h \
    muscle/util/NetworkUtilityFunctions.h \
    muscle/util/PulseNode.h \
    muscle/util/SocketMultiplexer.h \
    muscle/util/String.h \
    muscle/util/Queue.h \
    muscle/util/Hashtable.h \
    muscle/util/FlatCountable.h \
    muscle/util/RefCount.h \
    muscle/util/Cloneable.h \
    muscle/util/ObjectPool.h \
    muscle/util/TimeUtilityFunctions.h \
    muscle/util/MemoryAllocator.h \
    muscle/util/Socket.h \
    muscle/util/GenericCallback.h \
    muscle/util/MiscUtilityFunctions.h \
    muscle/util/NestCount.h \
    muscle/util/DebugTimer.h \
    muscle/util/PointerAndBool.h \
    muscle/util/CountedObject.h \
    muscle/util/DemandConstructedObject.h \
    muscle/util/StringTokenizer.h \
    muscle/iogateway/AbstractMessageIOGateway.h \
    muscle/iogateway/MessageIOGateway.h \
    muscle/support/MuscleSupport.h \
    muscle/support/Point.h support/Rect.h \
    muscle/support/Flattenable.h \
    muscle/support/Tuple.h \
    muscle/system/GlobalMemoryAllocator.h \
    muscle/system/AtomicCounter.h \
    muscle/system/Mutex.h \
    muscle/system/SetupSystem.h \
    muscle/system/SystemInfo.h \
    muscle/syslog/SysLog.h \
    muscle/syslog/LogCallback.h \
    muscle/dataio/DataIO.h \
    muscle/dataio/TCPSocketDataIO.h \
    muscle/dataio/FileDataIO.h \
    muscle/reflector/StorageReflectConstants.h


unix {
    target.path = /usr/lib
    INSTALLS += target
}

DEFINES += MUSCLE_SINGLE_THREAD_ONLY
INCLUDEPATH += muscle/ include/
ios {
    INCLUDEPATH += /Users/justinhammond/Documents/Development/boost-xcode5-iosx/ios/framework/boost.framework/Headers/
    LIBS += -F/Users/justinhammond/Documents/Development/boost-xcode5-iosx/ios/framework/ -framework boost
    QMAKE_LFLAGS += -F/Users/justinhammond/Documents/Development/boost-xcode5-iosx/ios/framework/
}
macx {
    INCLUDEPATH += /Users/justinhammond/Documents/Development/boost-xcode5-iosx/osx/framework/boost.framework/Headers/
    LIBS += -F/Users/justinhammond/Documents/Development/boost-xcode5-iosx/osx/framework/ -framework boost
    QMAKE_LFLAGS += -F/Users/justinhammond/Documents/Development/boost-xcode5-iosx/osx/framework/
}
ios|macx {
    FRAMEWORK_HEADERS_IH.files = include/iHanClient/
    FRAMEWORK_HEADERS_IH.path = Headers/iHanClient/
    FRAMEWORK_HEADERS_MM.files = muscle/message/Message.h
    FRAMEWORK_HEADERS_MM.path = Headers/muscle/message/
    FRAMEWORK_HEADERS_MU.files = muscle/util/ByteBuffer.h muscle/util/Directory.h muscle/util/FilePathInfo.h \
    muscle/util/NetworkUtilityFunctions.h muscle/util/PulseNode.h muscle/util/SocketMultiplexer.h \
    muscle/util/String.h muscle/util/Queue.h muscle/util/FlatCountable.h muscle/util/Hashtable.h \
    muscle/util/RefCount.h muscle/util/TimeUtilityFunctions.h \
    muscle/util/Cloneable.h muscle/util/ObjectPool.h muscle/util/MemoryAllocator.h muscle/util/Socket.h \
    muscle/util/GenericCallback.h muscle/util/MiscUtilityFunctions.h muscle/util/NestCount.h \
    muscle/util/DebugTimer.h muscle/util/PointerAndBool.h \
    muscle/util/CountedObject.h muscle/util/DemandConstructedObject.h muscle/util/StringTokenizer.h
    FRAMEWORK_HEADERS_MU.path = Headers/muscle/util/
    FRAMEWORK_HEADERS_MI.files = muscle/iogateway/AbstractMessageIOGateway.h muscle/iogateway/MessageIOGateway.h
    FRAMEWORK_HEADERS_MI.path = Headers/muscle/iogateway/
    FRAMEWORK_HEADERS_MS.files = muscle/support/MuscleSupport.h muscle/support/Point.h muscle/support/Rect.h \
    muscle/support/Flattenable.h muscle/support/Tuple.h
    FRAMEWORK_HEADERS_MS.path = Headers/muscle/support/
    FRAMEWORK_HEADERS_MSYS.files = muscle/system/GlobalMemoryAllocator.h muscle/system/AtomicCounter.h muscle/system/Mutex.h \
    muscle/system/SetupSystem.h muscle/system/SystemInfo.h
    FRAMEWORK_HEADERS_MSYS.path = Headers/muscle/system/
    FRAMEWORK_HEADERS_MLOG.files = muscle/syslog/SysLog.h muscle/syslog/LogCallback.h
    FRAMEWORK_HEADERS_MLOG.path = Headers/muscle/syslog/
    FRAMEWORK_HEADERS_MD.files = muscle/dataio/DataIO.h muscle/dataio/TCPSocketDataIO.h muscle/dataio/FileDataIO.h
    FRAMEWORK_HEADERS_MD.path = Headers/muscle/dataio/
    FRAMEWORK_HEADERS_MR.files = muscle/reflector/StorageReflectConstants.h
    FRAMEWORK_HEADERS_MR.path = Headers/muscle/reflector/

    QMAKE_BUNDLE_DATA += FRAMEWORK_HEADERS_IH FRAMEWORK_HEADERS_MM FRAMEWORK_HEADERS_MU FRAMEWORK_HEADER_MI \
    FRAMEWORK_HEADERS_MS FRAMEWORK_HEADERS_MSYS FRAMEWORK_HEADERS_MD FRAMEWORK_HEADERS_MR

}
