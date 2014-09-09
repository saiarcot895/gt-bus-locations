#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QQmlApplicationEngine>
#include "gtwikibusfetcher.h"

#include "route.h"

class MainWindow : public QObject
{
    Q_OBJECT
public:
    explicit MainWindow(QObject *parent = 0);

    Q_INVOKABLE void displayDirections(int routeIndex);
    Q_INVOKABLE void displayStops(int directionsIndex);

public slots:
    Q_INVOKABLE void displayStopTimes(int stopIndex);

private slots:
    void displayRoutes();
    void refreshWaitTimes(QString routeTag);

private:
    void displayWaitTimes();

    QQmlApplicationEngine* engine;
    QObject* rootObject;
    GTWikiBusFetcher* fetcher;

    Route selectedRoute;
    Direction selectedDirection;
    Stop selectedStop;

    QList<Direction> availableDirections;
    QList<Stop> availableStops;

};

#endif // MAINWINDOW_H