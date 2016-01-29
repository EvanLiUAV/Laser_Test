#-------------------------------------------------
#
# Project created by QtCreator 2016-01-22T11:55:22
#
#-------------------------------------------------

QT       += core gui serialport webkit network opengl
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webkitwidgets
QMAKE_CXXFLAGS += -std=c++11
TARGET = Laser_Test
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    laser_data_parser.cpp \
    laser_driver.cpp\
    settingsdialog.cpp \
    console.cpp \
    laser_handler.cpp \
    laser_view.cpp

HEADERS  += mainwindow.h \
    laser_data_parser.h \
    laser_driver.h \
    laser_parse_define.h\
    settingsdialog.h \
    console.h \
    laser_handler.h \
    laser_message.h \
    laser_view.h

FORMS += \
    mainwindow.ui \
    settingsdialog.ui \
    laser_view.ui

RESOURCES += \
    terminal.qrc

DISTFILES += \
    ../build-Laser_Test-Desktop_Qt_5_5_1_MinGW_32bit-Release/examples/Laser_viewer.html \
    ../build-Laser_Test-Desktop_Qt_5_5_1_MinGW_32bit-Release/examples/js/laser_viewer.js
