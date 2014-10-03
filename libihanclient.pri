SOURCES += $$PWD/src/LogClass.cpp \
    $$PWD/src/varcontainer.cpp \
    $$PWD/src/ZBLocations.cpp \
    $$PWD/src/VariableTypes.cpp \
    $$PWD/src/MessageBus.cpp \
    $$PWD/muscle/message/Message.cpp \
    $$PWD/muscle/util/ByteBuffer.cpp \
    $$PWD/muscle/util/Directory.cpp \
    $$PWD/muscle/util/FilePathInfo.cpp \
    $$PWD/muscle/util/NetworkUtilityFunctions.cpp \
    $$PWD/muscle/util/PulseNode.cpp \
    $$PWD/muscle/util/SocketMultiplexer.cpp \
    $$PWD/muscle/util/MString.cpp \
    $$PWD/muscle/system/SetupSystem.cpp \
    $$PWD/muscle/syslog/Syslog.cpp \
    $$PWD/muscle/iogateway/AbstractMessageIOGateway.cpp \
    $$PWD/muscle/iogateway/MessageIOGateway.cpp

HEADERS += $$PWD/include/iHanClient/DeviceTypes.hpp \
    $$PWD/include/iHanClient/LogClass.hpp \
    $$PWD/include/iHanClient/MsgTypes.hpp \
    $$PWD/include/iHanClient/varcontainer.hpp \
    $$PWD/include/iHanClient/ZBHAProfiles.hpp \
    $$PWD/include/iHanClient/ZBLocations.hpp \
    $$PWD/include/iHanClient/VariableTypes.hpp \
    $$PWD/include/iHanClient/MessageBus.hpp \
    $$PWD/muscle/message/Message.h \
    $$PWD/muscle/util/ByteBuffer.h \
    $$PWD/muscle/util/Directory.h \
    $$PWD/muscle/util/FilePathInfo.h \
    $$PWD/muscle/util/NetworkUtilityFunctions.h \
    $$PWD/muscle/util/PulseNode.h \
    $$PWD/muscle/util/SocketMultiplexer.h \
    $$PWD/muscle/util/MString.h \
    $$PWD/muscle/util/Queue.h \
    $$PWD/muscle/util/Hashtable.h \
    $$PWD/muscle/util/FlatCountable.h \
    $$PWD/muscle/util/RefCount.h \
    $$PWD/muscle/util/Cloneable.h \
    $$PWD/muscle/util/ObjectPool.h \
    $$PWD/muscle/util/TimeUtilityFunctions.h \
    $$PWD/muscle/util/MemoryAllocator.h \
    $$PWD/muscle/util/Socket.h \
    $$PWD/muscle/util/GenericCallback.h \
    $$PWD/muscle/util/MiscUtilityFunctions.h \
    $$PWD/muscle/util/NestCount.h \
    $$PWD/muscle/util/DebugTimer.h \
    $$PWD/muscle/util/PointerAndBool.h \
    $$PWD/muscle/util/CountedObject.h \
    $$PWD/muscle/util/DemandConstructedObject.h \
    $$PWD/muscle/util/StringTokenizer.h \
    $$PWD/muscle/iogateway/AbstractMessageIOGateway.h \
    $$PWD/muscle/iogateway/MessageIOGateway.h \
    $$PWD/muscle/support/MuscleSupport.h \
    $$PWD/muscle/support/Point.h \
    $$PWD/muscle/support/Rect.h \
    $$PWD/muscle/support/Flattenable.h \
    $$PWD/muscle/support/Tuple.h \
    $$PWD/muscle/system/GlobalMemoryAllocator.h \
    $$PWD/muscle/system/AtomicCounter.h \
    $$PWD/muscle/system/Mutex.h \
    $$PWD/muscle/system/SetupSystem.h \
    $$PWD/muscle/system/SystemInfo.h \
    $$PWD/muscle/syslog/SysLog.h \
    $$PWD/muscle/syslog/LogCallback.h \
    $$PWD/muscle/dataio/DataIO.h \
    $$PWD/muscle/dataio/TCPSocketDataIO.h \
    $$PWD/muscle/dataio/FileDataIO.h \
    $$PWD/muscle/reflector/StorageReflectConstants.h


DEFINES += MUSCLE_SINGLE_THREAD_ONLY
INCLUDEPATH += $$PWD/muscle/ $$PWD/include/

ios|macx {
    FRAMEWORK_HEADERS_IH.files = $$PWD/include/iHanClient/
    FRAMEWORK_HEADERS_IH.path = Headers/iHanClient/
    FRAMEWORK_HEADERS_MM.files = $$PWD/muscle/message/Message.h
    FRAMEWORK_HEADERS_MM.path = Headers/muscle/message/
    FRAMEWORK_HEADERS_MU.files = $$PWD/muscle/util/ByteBuffer.h $$PWD/muscle/util/Directory.h $$PWD/muscle/util/FilePathInfo.h \
    $$PWD/muscle/util/NetworkUtilityFunctions.h $$PWD/muscle/util/PulseNode.h $$PWD/muscle/util/SocketMultiplexer.h \
    $$PWD/muscle/util/MString.h $$PWD/muscle/util/Queue.h $$PWD/muscle/util/FlatCountable.h $$PWD/muscle/util/Hashtable.h \
    $$PWD/muscle/util/RefCount.h $$PWD/muscle/util/TimeUtilityFunctions.h \
    $$PWD/muscle/util/Cloneable.h $$PWD/muscle/util/ObjectPool.h $$PWD/muscle/util/MemoryAllocator.h $$PWD/muscle/util/Socket.h \
    $$PWD/muscle/util/GenericCallback.h $$PWD/muscle/util/MiscUtilityFunctions.h $$PWD/muscle/util/NestCount.h \
    $$PWD/muscle/util/DebugTimer.h $$PWD/muscle/util/PointerAndBool.h \
    $$PWD/muscle/util/CountedObject.h $$PWD/muscle/util/DemandConstructedObject.h $$PWD/muscle/util/StringTokenizer.h
    FRAMEWORK_HEADERS_MU.path = Headers/muscle/util/
    FRAMEWORK_HEADERS_MI.files = $$PWD/muscle/iogateway/AbstractMessageIOGateway.h $$PWD/muscle/iogateway/MessageIOGateway.h
    FRAMEWORK_HEADERS_MI.path = Headers/muscle/iogateway/
    FRAMEWORK_HEADERS_MS.files = $$PWD/muscle/support/MuscleSupport.h $$PWD/muscle/support/Point.h $$PWD/muscle/support/Rect.h \
    $$PWD/muscle/support/Flattenable.h $$PWD/muscle/support/Tuple.h
    FRAMEWORK_HEADERS_MS.path = Headers/muscle/support/
    FRAMEWORK_HEADERS_MSYS.files = $$PWD/muscle/system/GlobalMemoryAllocator.h $$PWD/muscle/system/AtomicCounter.h $$PWD/muscle/system/Mutex.h \
    $$PWD/muscle/system/SetupSystem.h $$PWD/muscle/system/SystemInfo.h
    FRAMEWORK_HEADERS_MSYS.path = Headers/muscle/system/
    FRAMEWORK_HEADERS_MLOG.files = $$PWD/muscle/syslog/SysLog.h $$PWD/muscle/syslog/LogCallback.h
    FRAMEWORK_HEADERS_MLOG.path = Headers/muscle/syslog/
    FRAMEWORK_HEADERS_MD.files = $$PWD/muscle/dataio/DataIO.h $$PWD/muscle/dataio/TCPSocketDataIO.h $$PWD/muscle/dataio/FileDataIO.h
    FRAMEWORK_HEADERS_MD.path = Headers/muscle/dataio/
    FRAMEWORK_HEADERS_MR.files = $$PWD/muscle/reflector/StorageReflectConstants.h
    FRAMEWORK_HEADERS_MR.path = Headers/muscle/reflector/
}
