#include "mainwindow.h"
#include "treemodel.h"

#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent)
{
    setupUi(this);

    //set header
    QStringList headers;
    headers<< tr("Title")<< tr("Description");

    //read file and create TreeModel
    QFile file(":/default.txt");
    file.open(QIODevice::ReadOnly);
    TreeModel *model = new TreeModel(headers, file.readAll());
//    TreeModel *model = new TreeModel(headers, file.readAll());
    file.close();

    view_2->setModel(model);
    //connect signal and slots
}

void MainWindow::insertChild()
{

}

bool MainWindow::insertColum()
{
    return true;
}

void MainWindow::insertRow()
{

}

bool MainWindow::removeColumn()
{
    return true;
}

void MainWindow::removeRow()
{

}

void MainWindow::updateActions()
{

}
