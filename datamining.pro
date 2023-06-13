QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets charts opengl

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    about.cpp \
    array.cpp \
    datameaning.cpp \
    datameaningcore.cpp \
    datarow.cpp \
    main.cpp \
    mainwindow.cpp ptable.cpp chart.cpp \
    report.cpp \
    support.cpp

HEADERS += \
    about.h \
    array.h \
    datameaning.h \
    datameaningcore.h \
    datarow.h \
    mainwindow.h ptable.h chart.h \
    report.h \
    support.h

FORMS += \
    about.ui \
    help.ui \
    mainwindow.ui

OBJECTS_DIR = obj
MOC_DIR = moc
UI_DIR = moc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    datamining.qrc



#unix {
 # CONFIG += create_pc create_prl no_install_prl
  #QMAKE_PKGCONFIG_NAME = $${TARGET}
 # QMAKE_PKGCONFIG_DESCRIPTION = Dynamic Python binding for the Qt framework
 # QMAKE_PKGCONFIG_PREFIX = $$INSTALLBASE
 # QMAKE_PKGCONFIG_LIBDIR = $$target.path
 # QMAKE_PKGCONFIG_INCDIR = $$headers.path
 # QMAKE_PKGCONFIG_INCDIR += ${prefix}/include/python3.8
 # QMAKE_PKGCONFIG_VERSION = $$VERSION

  #INCLUDEPATH += /usr/include/python
#}

#include ( $$PWD/pythonqt/common.prf )
#include ( $$PWD/pythonqt/python.prf )
#include ( $$PWD/pythonqt/PythonQt.prf )
#include ( $$PWD/pythonqt/PythonQt_QtAll.prf )
#include($$PWD/pythonqt/src.pri)

