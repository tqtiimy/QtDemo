QT += widgets

TARGET = settingseditor #指定目标文件名称
TEMPLATE = app  #指定生成项目时的模版名称  e.g app/lib/subdirs/aux/vcapp/vclib
DESTDIR = ../../../demo_bin/settingseditor/bin
UI_DIR = ../../../demo_bin/settingseditor/ui
MOC_DIR = ../../../demo_bin/settingseditor/moc
RCC_DIR = ../../../demo_bin/settingseditor/rcc

SOURCES += \
    main.cpp \
    mainwindow.cpp


EXAMPLE_FILES = inifiles

HEADERS += \
    mainwindow.h
