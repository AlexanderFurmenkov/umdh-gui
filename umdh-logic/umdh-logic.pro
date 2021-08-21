QT -= gui

TARGET = umdh-logic
TEMPLATE = lib
DEFINES += UMDH_LOGIC_LIBRARY

CONFIG -= qt
CONFIG += c++14

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    impl/cbyallocatedbytessorter.cpp \
    impl/cbyallocationcountsorter.cpp \
    impl/ccommandexecuter.cpp \
    impl/ccommandexecutercreator.cpp \
    impl/cdefaultfilter.cpp \
    impl/cdefaultsorter.cpp \
    impl/cfilterfactory.cpp \
    impl/cfilterfactorycreator.cpp \
    impl/chotpathcalculator.cpp \
    impl/cleakedmorethanbytesfilter.cpp \
    impl/cleakedmorethancountfilter.cpp \
    impl/commandexecuterprovider.cpp \
    impl/creportmanager.cpp \
    impl/creportmanagercreator.cpp \
    impl/csorterfactory.cpp \
    impl/csorterfactorycreator.cpp \
    impl/cumdh.cpp \
    impl/cumdhcreator.cpp \
    impl/cwithoutpatternfilter.cpp \
    impl/cwithoutsystemmodulesfilter.cpp \
    impl/cwithpatternfilter.cpp \
    impl/cwithsourcesfilter.cpp \
    impl/cwithsymbolsfilter.cpp \
    impl/filterfactorycreatorprovider.cpp \
    impl/reportmanagercreatorprovider.cpp \
    impl/sorterfactorycreatorprovider.cpp \
    impl/umdhcreatorprovider.cpp


HEADERS += \
    impl/cbyallocatedbytessorter.h \
    impl/cbyallocationcountsorter.h \
    impl/ccommandexecuter.h \
    impl/ccommandexecutercreator.h \
    impl/cdefaultfilter.h \
    impl/cdefaultsorter.h \
    impl/cfilterfactory.h \
    impl/cfilterfactorycreator.h \
    impl/ihotpathcalculator.h \
    impl/cleakedmorethanbytesfilter.h \
    impl/cleakedmorethancountfilter.h \
    impl/creportmanager.h \
    impl/creportmanagercreator.h \
    impl/csorterfactory.h \
    impl/csorterfactorycreator.h \
    impl/cumdh.h \
    impl/cumdhcreator.h \
    impl/cwithoutpatternfilter.h \
    impl/cwithoutsystemmodulesfilter.h \
    impl/cwithpatternfilter.h \
    impl/cwithsourcesfilter.h \
    impl/cwithsymbolsfilter.h \
    impl/chotpathcalculator.h \
    interface/commandexecuterprovider.h \
    interface/filterfactorycreatorprovider.h \
    interface/reportmanagercreatorprovider.h \
    interface/sorterfactorycreatorprovider.h \
    interface/umdh.logic.global.h \
    interface/umdhcreatorprovider.h

include($$PWD/../umdh-gui/umdh-gui.pri)

PATH_TO_TARGET_OUTPUT = ""
CONFIG(release, debug|release) {
  PATH_TO_TARGET_OUTPUT = $$OUT_PWD/release/$$TARGET".dll"
}
CONFIG(debug, debug|release) {
  PATH_TO_TARGET_OUTPUT = $$OUT_PWD/debug/$$TARGET".dll"
}

DLLDESTDIR=$$PWD/../bin/
