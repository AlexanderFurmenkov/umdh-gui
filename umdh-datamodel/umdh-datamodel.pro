QT -= gui

TARGET = umdh-datamodel
TEMPLATE = lib
DEFINES += UMDH_DATAMODEL_LIBRARY

CONFIG -= qt
CONFIG += c++14 dll

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        impl/cloadedmodule.cpp \
        impl/clogentry.cpp \
        impl/cobjectfactory.cpp \
        impl/creport.cpp \
        impl/csettings.cpp \
        impl/cstacktraceframe.cpp \
        impl/ctotalincrease.cpp \
        impl/objectfactorycreator.cpp

HEADERS += \
    impl/cloadedmodule.h \
    impl/clogentry.h \
    impl/cobjectfactory.h \
    impl/creport.h \
    impl/csettings.h \
    impl/cstacktraceframe.h \
    impl/ctotalincrease.h \
    interface/objectfactorycreator.h \
    interface/umdh.datamodel.global.h \

include($$PWD/../umdh-gui/umdh-gui.pri)


PATH_TO_TARGET_OUTPUT = ""
CONFIG(release, debug|release) {
  PATH_TO_TARGET_OUTPUT = $$OUT_PWD/release/$$TARGET".dll"
}
CONFIG(debug, debug|release) {
  PATH_TO_TARGET_OUTPUT = $$OUT_PWD/debug/$$TARGET".dll"
}

DLLDESTDIR=$$PWD/../bin/
