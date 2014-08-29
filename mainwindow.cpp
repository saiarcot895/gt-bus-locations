#include "mainwindow.h"

#include <QQmlComponent>
#include <QQmlContext>
#include <QDebug>

#include "routemodel.h"

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
    model->setDirections(route.getDirections().values());
    engine->rootContext()->setContextProperty("directionsModel", model);
    rootObject->findChild<QObject*>("directionsComboBox")->setProperty("enabled", true);
}

void MainWindow::displayStops(int routeIndex, int directionsIndex) {
    qDebug() << routeIndex + " " + directionsIndex;
}
