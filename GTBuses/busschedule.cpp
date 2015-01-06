#include "busschedule.h"

#include <QVariant>

BusSchedule::BusSchedule(QObject *rootObject, QObject *parent) :
    QObject(parent),
    rootObject(rootObject)
{
}

void BusSchedule::setBus(Bus bus) {
    this->bus = bus;
}

void BusSchedule::showBusSchedule() {
    Q_ASSERT(rootObject);
    rootObject->findChild<QObject*>("pageLoader")->setProperty("source", QStringLiteral("qrc:///BusSchedule.qml"));

    QObject* busScheduleView = rootObject->findChild<QObject*>(QStringLiteral("busScheduleView"));
    busScheduleView->setProperty("id", bus.getId());
    busScheduleView->setProperty("status", bus.getStatusString().isEmpty() ? "Unknown" : bus.getStatusString());

    const QList<Direction> directions = bus.getRoute().getDirections().values();
    for (int i = 0; i < directions.size(); i++) {
        const Direction direction = directions.at(i);
        const QList<Stop> stops = direction.getStops();
        for (int j = 0; j < stops.size(); j++) {
            const Stop stop = stops.at(j);
            const QList<StopWait> stopWaits = stop.getStopTimes();
            for (int k = 0; k < stopWaits.size(); k++) {
                const StopWait stopWait = stopWaits.at(k);
                if (stopWait.getBusId() == bus.getId()) {
                    QMetaObject::invokeMethod(busScheduleView, "addItem",
                                              Q_ARG(QVariant, stop.getStopName()),
                                              Q_ARG(QVariant, stopWait.getTime()));
                    break;
                }
            }
        }
    }
}
