#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include <QQmlApplicationEngine>
#include "mainwindow.h"

class MainController : public QObject
{
    Q_OBJECT
public:
    explicit MainController(QObject *parent = 0);

private slots:
    void continueLoading();

private:
    MainWindow* mainWindow;

    QQmlApplicationEngine* engine;
    QQmlComponent* component;
    QObject* rootObject;

};

#endif // MAINCONTROLLER_H
