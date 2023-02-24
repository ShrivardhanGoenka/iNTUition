QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    inputdialog.cpp \
    main.cpp \
    mainwindow.cpp \
    videoinfo.cpp \
    videotab.cpp

HEADERS += \
    inputdialog.h \
    mainwindow.h \
    videoinfo.h \
    videotab.h

FORMS += \
    inputdialog.ui \
    mainwindow.ui \
    videotab.ui

QT_CONFIG -= no-pkg_config
CONFIG += link_pkgconfig
PKGCONFIG += opencv4

ios {
QMAKE_INFO_PLIST=$$PWD/filename.plist
}


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
