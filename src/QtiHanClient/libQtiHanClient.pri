
INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

SOURCES += 	$$PWD/DeviceModel.cpp \
		$$PWD/MessageHandler.cpp \
		$$PWD/QtiHanClient.cpp \
		$$PWD/modeltest.cpp \
		$$PWD/kdescendantsproxymodel.cpp

HEADERS += 	include/QtiHanClient/DeviceModel.h \
		include/QtiHanClient/QtiHanClient.h \
		include/QtiHanClient/MessageHandler.h \
		include/QtiHanClient/modeltest.h \
		include/QtiHanClient/kdescendantsproxymodel.h \
		include/QtiHanClient/kbihash_p.h \
		include/QtiHanClient/kitemmodels_export.h
