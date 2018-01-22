#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSharedPointer>

QT_BEGIN_NAMESPACE
class QAction;
class QSettings;
QT_END_NAMESPACE
class LocationDialog;
class SettingsTree;

class Mainwindow : public QMainWindow
{
    Q_OBJECT

 public:
    typedef QSharedPointer<QSettings> SettingsPtr;
//    Mainwindow();

private slots:

private:
    void createActions();
    void setSettingObject(const SettingsPtr &settings);

};

#endif // MAINWINDOW_H
