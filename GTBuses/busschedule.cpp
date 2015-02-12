#include "busschedule.h"

#include <QVariant>

BusSchedule::BusSchedule(GTWikiBusFetcher* fetcher, QObject *rootObject, QObject *parent) :
    QObject(parent),
    fetcher(fetcher),
    rootObject(rootObject)
{
    connect(fetcher, &GTWikiBusFetcher::waitTimesUpdated, this, &BusSchedule::updateTimes);
}

void BusSchedule::setBus(Bus bus) {
    this->bus = bus;
}

void BusSchedule::showBusSchedule() {
    Q_ASSERT(rootObject);
    rootObject->findChild<QObject*>("loader")->setProperty("source", QStringLiteral("qrc:///BusSchedule.qml"));
    updateTimes(bus.getRoute().getTag());
}

void BusSchedule::updateTimes(QString routeTag) {
    if (bus.getRoute().getTag() != routeTag) {
        return;
    }

    QObject* loader = rootObject->findChild<QObject*>(QStringLiteral("loader"));
    QObject* busScheduleView = loader->property("item").value<QObject*>();
    if (!busScheduleView) {
        return;
    }
    busScheduleView->setProperty("id", bus.getId());
    busScheduleView->setProperty("status", bus.getStatusString().isEmpty() ? "Unknown" : bus.getStatusString());

    QMetaObject::invokeMethod(busScheduleView, "clearItems");

    foreach (const Direction direction, bus.getRoute().getDirections()) {
        foreach (const Stop stop, direction.getStops()) {
            bool highlight = false;
            if ((bus.getStatus() == Bus::Arriving || bus.getStatus() == Bus::AtStop) && bus.getArrivingStop() == stop) {
                highlight = true;
            } else if (bus.getStatus() == Bus::Departing && bus.getDepartingStop() == stop) {
                highlight = true;
            } else if (bus.getStatus() == Bus::InTransit && (bus.getArrivingStop() == stop || bus.getDepartingStop() == stop)) {
                highlight = true;
            }

            foreach (const StopWait stopWait, stop.getStopTimes()) {
                if (stopWait.getBusId() == bus.getId()) {
                    QMetaObject::invokeMethod(busScheduleView, "addItem",
                                              Q_ARG(QVariant, stop.getStopName()),
                                              Q_ARG(QVariant, QString("%1 minutes").arg(stopWait.getTime() / 60)),
                                              Q_ARG(QVariant, highlight));
                    break;
                }
            }
        }
    }
}
