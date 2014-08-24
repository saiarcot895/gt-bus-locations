#include "mainwindow.h"

#include <QQmlComponent>
#include <QQmlContext>
#include <QDebug>

#include "directionmodel.h"

MainWindow::MainWindow(QObject *parent) :
    QObject(parent)
{
    engine = new QQmlApplicationEngine;
    QQmlComponent component(engine, QUrl(QStringLiteral("qrc:///main.qml")));
    rootObject = component.create();

    QList<Direction> directions;
    for (int i = 0; i < 4; i++) {
        Direction direction;
        direction.setDirectionName(QStringLiteral("Test %1").arg(i));
        directions.append(direction);
    }

    model.setDirections(directions);

    QList<Direction> directions2;
    for (int i = 4; i < 8; i++) {
        Direction direction;
        direction.setDirectionName(QStringLiteral("Test %1").arg(i));
        directions2.append(direction);
    }

    model2.setDirections(directions2);

    QList<Direction> directions3;
    for (int i = 8; i < 12; i++) {
        Direction direction;
        direction.setDirectionName(QStringLiteral("Test %1").arg(i));
        directions3.append(direction);
    }

    model3.setDirections(directions3);

    QMetaObject::invokeMethod(rootObject, "addRouteTab",
                              Q_ARG(QVariant, "Blue"),
                              Q_ARG(QVariant, "blue"),
                              Q_ARG(QVariant, QVariant::fromValue(&model)));
    QMetaObject::invokeMethod(rootObject, "addRouteTab",
                              Q_ARG(QVariant, "Red"),
                              Q_ARG(QVariant, "red"),
                              Q_ARG(QVariant, QVariant::fromValue(&model2)));
    QMetaObject::invokeMethod(rootObject, "addRouteTab",
                              Q_ARG(QVariant, "Green"),
                              Q_ARG(QVariant, "green"),
                              Q_ARG(QVariant, QVariant::fromValue(&model3)));
}
