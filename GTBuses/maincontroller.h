#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include <QQmlApplicationEngine>
#include "mainwindow.h"
#include "busschedule.h"
#include "gtwikibusfetcher.h"

class MainController : public QObject
{
    Q_OBJECT
public:
    explicit MainController(QObject *parent = 0);
    ~MainController();

    void showBusSchedule(Bus bus);
    Q_INVOKABLE void showMainWindow();

private slots:
    void continueLoading();

private:
    MainWindow* mainWindow;
    BusSchedule* busSchedule;
    GTWikiBusFetcher* fetcher;

    QQmlApplicationEngine* engine;
    QQmlComponent* component;
    QObject* rootObject;

};

#endif // MAINCONTROLLER_H
