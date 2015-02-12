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

        fetcher = new GTWikiBusFetcher(this);

        mainWindow = new MainWindow(fetcher, rootObject, this);
        busSchedule = new BusSchedule(fetcher, rootObject, this);

        engine->rootContext()->setContextProperty("mainController", this);
        engine->rootContext()->setContextProperty("mainWindow", mainWindow);
        engine->rootContext()->setContextProperty("busSchedule", busSchedule);

        mainWindow->showMainWindow();
    }
}

void MainController::showBusSchedule(Bus bus) {
    busSchedule->setBus(bus);
    busSchedule->showBusSchedule();
}

void MainController::showMainWindow() {
    mainWindow->showMainWindow();
}

void MainController::showAboutScreen() {
    rootObject->findChild<QObject*>("loader")->setProperty("source", QStringLiteral("qrc:///About.qml"));
}

MainController::~MainController() {
    delete component;
    delete engine;
}
