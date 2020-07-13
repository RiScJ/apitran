QT += quick

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += \
        $$PWD/../inc/ \
        $$PWD/../src/ \
        $$PWD/../res/ \

HEADERS += 

SOURCES += \
    ../src/main.cpp 

RESOURCES += qml.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
