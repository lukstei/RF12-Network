#-------------------------------------------------
#
# Project created by QtCreator 2011-01-10T10:46:48
#
#-------------------------------------------------

QT       += core gui

TARGET = MasterBluetoothBridge
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    NetworkManager.cpp \
    HttpWebApp.cpp \
    Helper.cpp

HEADERS  += MainWindow.h \
    NetworkManager.h \
    WebApp.h \
    HttpWebApp.h \
    Helper.h

FORMS    += MainWindow.ui

CONFIG += qt mobility 
QT += network

MOBILITY = 

# !aendern
INCLUDEPATH += "D:/My Dropbox/da/arduino/libraries/"

symbian {
    TARGET.UID3 = 0xee72dac3
    # TARGET.CAPABILITY += 
    TARGET.EPOCSTACKSIZE = 0x14000
    TARGET.EPOCHEAPSIZE = 0x020000 0x800000
}
