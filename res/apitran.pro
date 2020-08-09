QT += core gui widgets multimedia

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

QMAKE_CXXFLAGS +=

INCLUDEPATH += \
		$$PWD/../inc/ \
		$$PWD/../src/ \
		$$PWD/../res/ \

HEADERS +=  \
	../inc/canvas.hpp \
	../inc/main_window.hpp \

SOURCES += \
	../src/canvas.cpp \
	../src/main.cpp \
	../src/main_window.cpp

RESOURCES += \
	icons.qrc

LIBS += -lfftw3

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
