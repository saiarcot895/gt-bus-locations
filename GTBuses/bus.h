#ifndef BUS_H
#define BUS_H

#define DEGREES_TO_METERS 111000

#include <QObject>
#include <QExplicitlySharedDataPointer>
#include <QSharedPointer>
#include <geos/geom/Point.h>
#include "route.h"
#include "stop.h"

class BusData;

class Bus : public QObject
{
public:
    Bus();
    Bus(const Bus &);
    Bus &operator=(const Bus &);
    ~Bus();

    enum Status {
        Unknown = 0,
        Arriving,
        Departing,
        InTransit,
        AtStop
    };

    QSharedPointer<geos::geom::Point> getLocation() const;
    Status getStatus() const;
    Route getRoute() const;
    Stop getArrivingStop() const;
    Stop getDepartingStop() const;

    void setLocation(QSharedPointer<geos::geom::Point> location);
    void setRoute(Route route);

private:
    QExplicitlySharedDataPointer<BusData> data;
};

#endif // BUS_H
