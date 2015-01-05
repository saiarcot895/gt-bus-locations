#include "mainwindow.h"

#include <QQmlComponent>
#include <QQmlContext>
#include <QDebug>

#include "routemodel.h"
#include "directionmodel.h"
#include "stopmodel.h"
#include "bus.h"

MainWindow::MainWindow(QObject* rootObject, QObject *parent) :
    QObject(parent),
    fetcher(new GTWikiBusFetcher),
    rootObject(rootObject)
{
    connect(fetcher, SIGNAL(loadingDone()), this, SLOT(displayRoutes()));
    connect(fetcher, SIGNAL(waitTimesUpdated(QString)), this, SLOT(refreshWaitTimes(QString))); 
}

void MainWindow::showMainWindow() {
    Q_ASSERT(rootObject);
    rootObject->findChild<QObject*>("pageLoader")->setProperty("source", QStringLiteral("qrc:///mainWindow.qml"));
}

void MainWindow::displayRoutes() {
    RouteModel* model = new RouteModel(this);
    model->setRoutes(fetcher->getRoutes());
    rootObject->findChild<QObject*>("mainWindowItem")->setProperty("routesModel", QVariant::fromValue(model));
}

void MainWindow::displayDirections(int routeIndex) {
    DirectionModel* model = new DirectionModel(this);
    selectedRoute = fetcher->getRoutes().at(routeIndex);
    availableDirections = selectedRoute.getDirections().values();
    model->setDirections(availableDirections);
    rootObject->findChild<QObject*>("mainWindowItem")->setProperty("directionsModel", QVariant::fromValue(model));
}

void MainWindow::displayStops(int directionsIndex) {
    StopModel* model = new StopModel(this);
    selectedDirection = availableDirections.at(directionsIndex);
    availableStops = selectedDirection.getStops();
    model->setStops(availableStops);
    rootObject->findChild<QObject*>("mainWindowItem")->setProperty("stopsModel", QVariant::fromValue(model));
}

void MainWindow::displayStopTimes(int stopIndex) {
    selectedStop = availableStops.at(stopIndex);
    displayWaitTimes();
    rootObject->findChild<QObject*>("mainWindowItem")->findChild<QObject*>("stopTimesRectangle")->setProperty("visible", true);
}

void MainWindow::displayWaitTimes() {
    for (int i = 0; i < 3; i++) {
        QObject* timeLabel = rootObject->findChild<QObject*>(QStringLiteral("stopTime%1").arg(i));
        if (selectedStop.getStopTimes().size() > i) {
            StopWait stopWait = selectedStop.getStopTimes().at(i);
            timeLabel->setProperty("time", QStringLiteral("%1 minutes").arg(stopWait.getTime() / 60));
            Bus bus = selectedRoute.getBuses().value(stopWait.getBusId());
            if (bus.getStatus() == Bus::AtStop) {
                timeLabel->setProperty("position", QString("At %1")
                                              .arg(bus.getArrivingStop().getStopName()));
            } else if (bus.getStatus() == Bus::InTransit) {
                timeLabel->setProperty("position", QString("Between %1 and %2")
                                              .arg(bus.getDepartingStop().getStopName())
                                              .arg(bus.getArrivingStop().getStopName()));
            } else if (bus.getStatus() == Bus::Departing) {
                timeLabel->setProperty("position", QString("Departing %1")
                                              .arg(bus.getDepartingStop().getStopName()));
            } else if (bus.getStatus() == Bus::Arriving) {
                timeLabel->setProperty("position", QString("Arriving %1")
                                              .arg(bus.getArrivingStop().getStopName()));
            } else {
                timeLabel->setProperty("position", "");
            }
        } else {
            timeLabel->setProperty("time", QStringLiteral("No prediction"));
            timeLabel->setProperty("position", "");
        }
    }
}

void MainWindow::refreshWaitTimes(QString routeTag) {
    if (selectedRoute.getTag() == routeTag) {
        displayWaitTimes();
    }
}

MainWindow::~MainWindow() {
    delete fetcher;
    delete rootObject;
}
