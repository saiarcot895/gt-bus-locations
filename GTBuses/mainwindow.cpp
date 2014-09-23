#include "mainwindow.h"

#include <QQmlComponent>
#include <QQmlContext>
#include <QDebug>

#include "routemodel.h"
#include "directionmodel.h"
#include "stopmodel.h"
#include "bus.h"

MainWindow::MainWindow(QObject *parent) :
    QObject(parent),
    fetcher(new GTWikiBusFetcher),
    rootObject(NULL)
{
    connect(fetcher, SIGNAL(loadingDone()), this, SLOT(displayRoutes()));
    connect(fetcher, SIGNAL(waitTimesUpdated(QString)), this, SLOT(refreshWaitTimes(QString)));

    engine = new QQmlApplicationEngine(this);
    component = new QQmlComponent(engine, QUrl(QStringLiteral("qrc:///main.qml")));
    if (component->isLoading()) {
        connect(component, SIGNAL(statusChanged(QQmlComponent::Status)),
                this, SLOT(continueLoading()));
    } else {
        continueLoading();
    }
}

void MainWindow::continueLoading() {
    if (component->isError()) {
        qWarning() << component->errors();
    } else {
        rootObject = component->create();
        engine->rootContext()->setContextProperty("mainWindow", this);
    }

}

void MainWindow::displayRoutes() {
    RouteModel* model = new RouteModel(this);
    model->setRoutes(fetcher->getRoutes());
    engine->rootContext()->setContextProperty("routesModel", model);
    rootObject->findChild<QObject*>("routesComboBox")->setProperty("enabled", true);
}

void MainWindow::displayDirections(int routeIndex) {
    DirectionModel* model = new DirectionModel(this);
    selectedRoute = fetcher->getRoutes().at(routeIndex);
    availableDirections = selectedRoute.getDirections().values();
    model->setDirections(availableDirections);
    engine->rootContext()->setContextProperty("directionsModel", model);
    rootObject->findChild<QObject*>("directionsComboBox")->setProperty("enabled", true);
}

void MainWindow::displayStops(int directionsIndex) {
    StopModel* model = new StopModel(this);
    selectedDirection = availableDirections.at(directionsIndex);
    availableStops = selectedDirection.getStops();
    model->setStops(availableStops);
    engine->rootContext()->setContextProperty("stopsModel", model);
    rootObject->findChild<QObject*>("stopsComboBox")->setProperty("enabled", true);
}

void MainWindow::displayStopTimes(int stopIndex) {
    selectedStop = availableStops.at(stopIndex);
    displayWaitTimes();
    rootObject->findChild<QObject*>("stopTimesRectangle")->setProperty("visible", true);
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
