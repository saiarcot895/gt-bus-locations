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

    const QList<Direction> directions = bus.getRoute().getDirections().values();
    for (int i = 0; i < directions.size(); i++) {
        const Direction direction = directions.at(i);
        const QList<Stop> stops = direction.getStops();
        for (int j = 0; j < stops.size(); j++) {
            const Stop stop = stops.at(j);

            bool highlight = false;
            if ((bus.getStatus() == Bus::Arriving || bus.getStatus() == Bus::AtStop) && bus.getArrivingStop() == stop) {
                highlight = true;
            } else if (bus.getStatus() == Bus::Departing && bus.getDepartingStop() == stop) {
                highlight = true;
            } else if (bus.getStatus() == Bus::InTransit && (bus.getArrivingStop() == stop || bus.getDepartingStop() == stop)) {
                highlight = true;
            }

            const QList<StopWait> stopWaits = stop.getStopTimes();
            for (int k = 0; k < stopWaits.size(); k++) {
                const StopWait stopWait = stopWaits.at(k);
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
