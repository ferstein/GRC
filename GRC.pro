#-------------------------------------------------
#
# Project created by QtCreator 2018-07-27T10:01:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = grc
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    VISCA/VISCA.cpp \
    SimpleGPIO.cpp \
    analogjoystick.cpp \
    gimbalcontrol.cpp \
    serialport.cpp \
    camera.cpp

HEADERS  += widget.h \
    VISCA/libvisca.h \
    VISCA/VISCA.h \
    analogjoystick.h \
    SimpleGPIO.h \
    gimbalcontrol.h \
    gimbal_defs.h \
    serialport.h \
    camera.h

FORMS    += widget.ui


# Default rules for deployment.

qnx: target.path = /tmp/$${TARGET}/bin

else: unix:!android: target.path = /home/debian/$${TARGET}

!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    VISCA/VISCA.h.bak

