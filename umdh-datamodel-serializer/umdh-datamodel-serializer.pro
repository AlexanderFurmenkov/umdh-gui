QT -= gui

TARGET = umdh-datamodel-serializer
TEMPLATE = lib
DEFINES += UMDH_DATAMODEL_SERIALIZER_LIBRARY

CONFIG -= qt
CONFIG += c++14

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    impl/cforwardparser.cpp \
    impl/cloadedmoduleserializer.cpp \
    impl/clogentryserializer.cpp \
    impl/creportserializer.cpp \
    impl/cserializerfactory.cpp \
    impl/cserializerfactorycreator.cpp \
    impl/csettingsserializer.cpp \
    impl/cstacktraceframeserializer.cpp \
    impl/ctotalincreaseserializer.cpp \
    impl/serializerfactorycreatorprovider.cpp \
    impl/utils.cpp

HEADERS += \
    impl/cforwardparser.h \
    impl/cloadedmoduleserializer.h \
    impl/clogentryserializer.h \
    impl/creportserializer.h \
    impl/cserializerfactory.h \
    impl/cserializerfactorycreator.h \
    impl/csettingsserializer.h \
    impl/cstacktraceframeserializer.h \
    impl/ctotalincreaseserializer.h \
    impl/utils.h \
    interface/serializerfactorycreatorprovider.h \
    interface/umdh.datamodel.serializer.global.h

include($$PWD/../umdh-gui/umdh-gui.pri)


PATH_TO_TARGET_OUTPUT = ""
CONFIG(release, debug|release) {
  PATH_TO_TARGET_OUTPUT = $$OUT_PWD/release/$$TARGET".dll"
}
CONFIG(debug, debug|release) {
  PATH_TO_TARGET_OUTPUT = $$OUT_PWD/debug/$$TARGET".dll"
}

DLLDESTDIR=$$PWD/../bin/
