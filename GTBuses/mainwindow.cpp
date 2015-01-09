#include "mainwindow.h"

#include <QQmlComponent>
#include <QQmlContext>
#include <QDebug>

#include "routemodel.h"
#include "directionmodel.h"
#include "stopmodel.h"
#include "bus.h"
#include "maincontroller.h"

MainWindow::MainWindow(QObject* rootObject, QObject *parent) :
    QObject(parent),
    fetcher(new GTWikiBusFetcher),
    rootObject(rootObject),
    visible(false)
{
    connect(fetcher, SIGNAL(loadingDone()), this, SLOT(displayRoutes()));
    connect(fetcher, SIGNAL(waitTimesUpdated(QString)), this, SLOT(refreshWaitTimes(QString))); 
}

void MainWindow::showMainWindow() {
    Q_ASSERT(rootObject);
    rootObject->findChild<QObject*>("mainWindowItem")->setProperty("visible", true);
    rootObject->findChild<QObject*>("busScheduleItem")->setProperty("visible", false);
    visible = true;
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
    rootObject->findChild<QObject*>("mainWindowItem")->findChild<QObject*>("stopWaitTimeView")->setProperty("visible", true);
}

void MainWindow::displayWaitTimes() {
    if (!visible) {
        return;
    }
    QObject* mainWindowItem = rootObject->findChild<QObject*>("mainWindowItem");
    for (int i = 0; i < 3; i++) {
        QString time;
        QString position;
        int id = 0;
        if (selectedStop.getStopTimes().size() > i) {
            StopWait stopWait = selectedStop.getStopTimes().at(i);
            time = QString("%1 minutes").arg(stopWait.getTime() / 60);
            Bus bus = selectedRoute.getBuses().value(stopWait.getBusId());
            id = bus.getId();
            position = bus.getStatusString();
        } else {
            time = QStringLiteral("No prediction");
        }
        QMetaObject::invokeMethod(mainWindowItem, "setItem",
                                  Q_ARG(QVariant, i),
                                  Q_ARG(QVariant, time),
                                  Q_ARG(QVariant, position),
                                  Q_ARG(QVariant, id));
    }
}

void MainWindow::refreshWaitTimes(QString routeTag) {
    if (selectedRoute.getTag() == routeTag) {
        displayWaitTimes();
    }
}

void MainWindow::displayBusSchedule(int busId) {
    Bus bus = selectedRoute.getBuses().value(busId);
    visible = false;
    static_cast<MainController*>(parent())->showBusSchedule(bus);
}

MainWindow::~MainWindow() {
    delete fetcher;
    delete rootObject;
}
