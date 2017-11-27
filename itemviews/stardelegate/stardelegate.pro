QT += widgets

TARGET = stardelegate
TEMPLATE = app

DESTDIR = ../../../demo_bin/startDelegate/bin
UI_DIR = ../../../demo_bin/startDelegate/ui
MOC_DIR = ../../../demo_bin/startDelegate/moc
OBJECTS_DIR = ../../../demo_bin/startDelegate/moc
RCC_DIR = ../../../demo_bin/startDelegate/rcc

SOURCES += \
    main.cpp \
    stardelegate.cpp \
    stareditor.cpp \
    starrating.cpp

HEADERS += \
    stardelegate.h \
    stareditor.h \
    starrating.h
