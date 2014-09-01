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
    Route route = fetcher->getRoutes().at(routeIndex);
    availableDirections = route.getDirections().values();
    model->setDirections(availableDirections);
    engine->rootContext()->setContextProperty("directionsModel", model);
    rootObject->findChild<QObject*>("directionsComboBox")->setProperty("enabled", true);
}

void MainWindow::displayStops(int directionsIndex) {
    StopModel* model = new StopModel(this);
    Direction direction = availableDirections.at(directionsIndex);
    availableStops = direction.getStops();
    model->setStops(availableStops);
    engine->rootContext()->setContextProperty("stopsModel", model);
    rootObject->findChild<QObject*>("stopsComboBox")->setProperty("enabled", true);
}

void MainWindow::displayStopTimes(int stopIndex) {
    Stop stop = availableStops.at(stopIndex);
    for (int i = 0; i < 3; i++) {
        QObject* timeLabel = rootObject->findChild<QObject*>(QStringLiteral("stopTime%1").arg(i));
        if (stop.getStopTimes().size() > i) {
            timeLabel->setProperty("text", QStringLiteral("%1 seconds").arg(stop.getStopTimes().at(i)));
        } else {
            timeLabel->setProperty("text", "No prediction");
        }
    }
    rootObject->findChild<QObject*>("stopTimesRectangle")->setProperty("visible", true);
}
