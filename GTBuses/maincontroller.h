#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include <QQmlApplicationEngine>
#include "mainwindow.h"
#include "busschedule.h"

class MainController : public QObject
{
    Q_OBJECT
public:
    explicit MainController(QObject *parent = 0);

    void showBusSchedule(Bus bus);

private slots:
    void continueLoading();

private:
    MainWindow* mainWindow;
    BusSchedule* busSchedule;

    QQmlApplicationEngine* engine;
    QQmlComponent* component;
    QObject* rootObject;

};

#endif // MAINCONTROLLER_H
