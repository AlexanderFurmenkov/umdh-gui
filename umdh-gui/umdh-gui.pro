QT += core gui

TARGET = umdh-gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14 ordered

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    src/impl/main.cpp \
    src/impl/mainwindow.cpp \
    src/impl/reportwidget.cpp \
    src/impl/reportviewwidget.cpp \
    src/impl/umdhwidget.cpp

HEADERS += \
    src/impl/reportwidget.h \
    src/impl/reportviewwidget.h \
    src/impl/umdhwidget.h \
    src/interface/customuniqueptr.h \
    src/interface/guiutils.h \
    src/interface/idatamodel/iclonable.h \
    src/interface/idatamodel/idataobject.h \
    src/interface/idatamodel/iloadedmodule.h \
    src/interface/idatamodel/ilogentry.h \
    src/interface/idatamodel/iobjectfactory.h \
    src/interface/idatamodel/ireport.h \
    src/interface/idatamodel/iserializable.h \
    src/interface/idatamodel/isettings.h \
    src/interface/idatamodel/istacktraceframe.h \
    src/interface/idatamodel/itotalincrease.h \
    src/interface/idatamodelserializer/iserializer.h \
    src/interface/idatamodelserializer/iserializerfactory.h \
    src/interface/idatamodelserializer/iserializerfactorycreator.h \
    src/interface/ilogic/icommandexecuter.h \
    src/interface/ilogic/icommandexecutercreator.h \
    src/interface/ilogic/ifilterfactory.h \
    src/interface/ilogic/ifilterfactorycreator.h \
    src/interface/ilogic/ileakedmorethanbytesfilter.h \
    src/interface/ilogic/ileakedmorethancountfilter.h \
    src/interface/ilogic/ireportfilter.h \
    src/interface/ilogic/ireportfilterwithoutpattern.h \
    src/interface/ilogic/ireportfilterwithpattern.h \
    src/interface/ilogic/ireportmanager.h \
    src/interface/ilogic/ireportsorter.h \
    src/interface/ilogic/isorterfactory.h \
    src/interface/ilogic/isorterfactorycreator.h \
    src/interface/ilogic/iumdh.h \
    src/interface/ilogic/iumdhcreator.h \
    src/interface/metamodel.h \
    src/impl/mainwindow.h

FORMS += \
    ui/reportwidget.ui \
    ui/umdhwidget.ui \
    ui/reportviewwidget.ui \
    ui/mainwindow.ui

INCLUDEPATH += src/interface

include($$PWD/../umdh-datamodel-serializer/umdh-datamodel-serializer.pri)
include($$PWD/../umdh-datamodel/umdh-datamodel.pri)
include($$PWD/../umdh-logic/umdh-logic.pri)

LIBS += -lPsapi

PATH_TO_TARGET_OUTPUT = ""
CONFIG(release, debug|release) {
  PATH_TO_TARGET_OUTPUT = $$OUT_PWD/release/$$TARGET".exe"
}
CONFIG(debug, debug|release) {
  PATH_TO_TARGET_OUTPUT = $$OUT_PWD/debug/$$TARGET".exe"
}

PATH_TO_DEPLOY_TARGET = $$PWD/../bin

QT_DIR = $$(Qt6_DIR)
QMAKE_POST_LINK = copy /Y $$shell_path($$PATH_TO_TARGET_OUTPUT) $$shell_path($$PATH_TO_DEPLOY_TARGET)$$escape_expand(\\) && "$$shell_quote($$shell_path($$QT_DIR\bin\windeployqt.exe))" "$$shell_quote($$shell_path($$PATH_TO_DEPLOY_TARGET\umdh-gui.exe))"
