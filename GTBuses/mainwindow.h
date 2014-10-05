#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include "gtwikibusfetcher.h"

#include "route.h"

class MainWindow : public QObject
{
    Q_OBJECT
public:
    explicit MainWindow(QObject* rootObject, QObject *parent = 0);

    void showMainWindow();

    Q_INVOKABLE void displayDirections(int routeIndex);
    Q_INVOKABLE void displayStops(int directionsIndex);

    ~MainWindow();
public slots:
    Q_INVOKABLE void displayStopTimes(int stopIndex);

private slots:
    void displayRoutes();
    void refreshWaitTimes(QString routeTag);

private:
    void displayWaitTimes();

    QObject* rootObject;
    GTWikiBusFetcher* fetcher;

    Route selectedRoute;
    Direction selectedDirection;
    Stop selectedStop;

    QList<Direction> availableDirections;
    QList<Stop> availableStops;

};

#endif // MAINWINDOW_H
