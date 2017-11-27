QT += widgets

DESTDIR = ../../../demo_bin/editableTreeModel/bin
UI_DIR = ../../../demo_bin/editableTreeModel/ui
MOC_DIR = ../../../demo_bin/editableTreeModel/moc
OBJECTS_DIR = ../../../demo_bin/editableTreeModel/moc
RCC_DIR = ../../../demo_bin/editableTreeModel/rcc

HEADERS = mainwindow.h \
    treeitem.h \
    treemodel.h

SOURCES = mainwindow.cpp \
    main.cpp \
    treeitem.cpp \
    treemodel.cpp

FORMS = \
    mainwindow.ui

RESOURCES = editabletreemodel.qrc

