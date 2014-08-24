#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QQmlApplicationEngine>
#include "directionmodel.h"
#include "gtwikibusfetcher.h"

class MainWindow : public QObject
{
    Q_OBJECT
public:
    explicit MainWindow(QObject *parent = 0);

    Q_INVOKABLE void displayStops(QString routeTag, QString directionTag);

private slots:
    void displayRoutes();

private:
    QQmlApplicationEngine* engine;
    QObject* rootObject;

    GTWikiBusFetcher* fetcher;

};

#endif // MAINWINDOW_H
