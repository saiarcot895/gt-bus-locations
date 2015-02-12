#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include "gtwikibusfetcher.h"

#include "route.h"

class MainWindow : public QObject
{
    Q_OBJECT
public:
    explicit MainWindow(GTWikiBusFetcher* fetcher, QObject* rootObject, QObject *parent = 0);

    void showMainWindow();

    Q_INVOKABLE void displayDirections(int routeIndex);
    Q_INVOKABLE void displayStops(int directionsIndex);
    Q_INVOKABLE void displayBusSchedule(int busId);
public slots:
    Q_INVOKABLE void displayStopTimes(int stopIndex);
    void displayRoutes();
    void refreshWaitTimes(QString routeTag);
    void updateMessages();

private:
    void displayWaitTimes();

    QObject* rootObject;
    GTWikiBusFetcher* fetcher;

    Route selectedRoute;
    Direction selectedDirection;
    Stop selectedStop;
    bool visible;

    QList<Direction> availableDirections;
    QList<Stop> availableStops;

};

#endif // MAINWINDOW_H
