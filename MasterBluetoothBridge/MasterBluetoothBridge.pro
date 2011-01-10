#-------------------------------------------------
#
# Project created by QtCreator 2011-01-10T07:55:13
#
#-------------------------------------------------

QT       += core gui

TARGET = MasterBluetoothBridge
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp

HEADERS  += MainWindow.h

FORMS    += MainWindow.ui

CONFIG += mobility
MOBILITY = 

symbian {
    TARGET.UID3 = 0xe40a7880
    # TARGET.CAPABILITY += 
    TARGET.EPOCSTACKSIZE = 0x14000
    TARGET.EPOCHEAPSIZE = 0x020000 0x800000
}
