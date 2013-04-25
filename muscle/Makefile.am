noinst_LTLIBRARIES = libmusclemessage.la
libmusclemessage_la_SOURCES = message/Message.cpp util/ByteBuffer.cpp util/String.cpp syslog/SysLog.cpp system/SetupSystem.cpp iogateway/MessageIOGateway.cpp iogateway/AbstractMessageIOGateway.cpp util/PulseNode.cpp util/NetworkUtilityFunctions.cpp util/SocketMultiplexer.cpp util/Directory.cpp util/FilePathInfo.cpp
libmusclemessage_la_CXXFLAGS = -DMUSCLE_SINGLE_THREAD_ONLY

noinst_HEADERS = util/ByteBuffer.h util/Queue.h message/Message.h util/FlatCountable.h \
	support/MuscleSupport.h support/Point.h support/Rect.h util/String.h util/Hashtable.h \
	support/Flattenable.h util/RefCount.h syslog/SysLog.h support/Tuple.h system/GlobalMemoryAllocator.h \
	util/TimeUtilityFunctions.h dataio/DataIO.h util/Cloneable.h util/ObjectPool.h \
	system/AtomicCounter.h util/MemoryAllocator.h util/Socket.h system/Mutex.h util/GenericCallback.h \
	util/MiscUtilityFunctions.h syslog/LogCallback.h system/SetupSystem.h util/NestCount.h \
	util/DebugTimer.h iogateway/MessageIOGateway.h reflector/StorageReflectConstants.h \
	dataio/TCPSocketDataIO.h iogateway/AbstractMessageIOGateway.h util/NetworkUtilityFunctions.h \
	util/PulseNode.h
	
EXTRA_DIST = muscle.vcproj	
	
	
