#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"

#include <mainwindow.h>
#include <QModelIndex>

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

public slots:
    void updateActions();

private slots:
    void insertChild();
    bool insertColum();
    void insertRow();
    bool removeColumn();
    void removeRow();
};

#endif // MAINWINDOW_H
