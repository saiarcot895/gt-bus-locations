#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QQmlApplicationEngine>
#include "directionmodel.h"

class MainWindow : public QObject
{
    Q_OBJECT
public:
    explicit MainWindow(QObject *parent = 0);

private:
    QQmlApplicationEngine* engine;
    QObject* rootObject;
    DirectionModel model;
    DirectionModel model2;
    DirectionModel model3;

};

#endif // MAINWINDOW_H
