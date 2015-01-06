#include "maincontroller.h"
#include <QQmlComponent>
#include <QQmlContext>

MainController::MainController(QObject *parent) :
    QObject(parent)
{
    engine = new QQmlApplicationEngine(this);
    component = new QQmlComponent(engine, QUrl(QStringLiteral("qrc:///main.qml")));
    if (component->isLoading()) {
        connect(component, SIGNAL(statusChanged(QQmlComponent::Status)),
                this, SLOT(continueLoading()));
    } else {
        continueLoading();
    }
}

void MainController::continueLoading() {
    if (component->isError()) {
        qCritical() << component->errors();
    } else {
        rootObject = component->create();

        mainWindow = new MainWindow(rootObject, this);
        busSchedule = new BusSchedule(rootObject, this);

        engine->rootContext()->setContextProperty("mainWindow", mainWindow);
        engine->rootContext()->setContextProperty("busSchedule", busSchedule);

        mainWindow->showMainWindow();
    }
}

void MainController::showBusSchedule(Bus bus) {
    busSchedule->setBus(bus);
    busSchedule->showBusSchedule();
}
