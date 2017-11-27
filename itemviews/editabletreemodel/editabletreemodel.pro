QT += widgets

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


#install
target.path = $$
