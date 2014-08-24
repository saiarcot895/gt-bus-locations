#include "mainwindow.h"

#include <QQmlComponent>
#include <QQmlContext>
#include <QDebug>

#include "directionmodel.h"

MainWindow::MainWindow(QObject *parent) :
    QObject(parent),
    fetcher(new GTWikiBusFetcher)
{
    connect(fetcher, SIGNAL(loadingDone()), this, SLOT(displayRoutes()));

    engine = new QQmlApplicationEngine;
    QQmlComponent component(engine, QUrl(QStringLiteral("qrc:///main.qml")));
    rootObject = component.create();

    engine->rootContext()->setContextProperty("mainWindow", this);
}

void MainWindow::displayRoutes() {
    for (int i = 0; i < fetcher->getRoutes().size(); i++) {
        Route route = fetcher->getRoutes().at(i);
        DirectionModel* model = new DirectionModel(this);
        model->setDirections(route.getDirections().values());

        QMetaObject::invokeMethod(rootObject, "addRouteTab",
                                  Q_ARG(QVariant, route.getRouteName()),
                                  Q_ARG(QVariant, route.getTag()),
                                  Q_ARG(QVariant, QVariant::fromValue(model)));
    }
}

void MainWindow::displayStops(QString routeTag, QString directionTag) {
    qDebug() << routeTag + " " + directionTag;
}
