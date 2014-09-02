#include "mainwindow.h"

#include <QQmlComponent>
#include <QQmlContext>
#include <QDebug>

#include "routemodel.h"
#include "directionmodel.h"
#include "stopmodel.h"

MainWindow::MainWindow(QObject *parent) :
    QObject(parent),
    fetcher(new GTWikiBusFetcher)
{
    connect(fetcher, SIGNAL(loadingDone()), this, SLOT(displayRoutes()));
    connect(fetcher, SIGNAL(waitTimesUpdated(QString)), this, SLOT(refreshWaitTimes(QString)));

    engine = new QQmlApplicationEngine(this);
    QQmlComponent component(engine, QUrl(QStringLiteral("qrc:///main.qml")));
    rootObject = component.create();

    engine->rootContext()->setContextProperty("mainWindow", this);
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
            timeLabel->setProperty("text", QStringLiteral("%1 minutes").arg(selectedStop.getStopTimes().at(i) / 60));
        } else {
            timeLabel->setProperty("text", "No prediction");
        }
    }
}

void MainWindow::refreshWaitTimes(QString routeTag) {
    if (selectedRoute.getTag() == routeTag) {
        displayWaitTimes();
    }
}
