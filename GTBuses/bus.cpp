#include "bus.h"
#include <QSharedData>

class BusData : public QSharedData {
public:
    QSharedPointer<geos::geom::Point> location;
    Bus::Status status = Bus::Unknown;
    Route route;
    Direction direction;
    Stop departingStop;
    Stop arrivingStop;
};

Bus::Bus() : data(new BusData)
{
}

Bus::Bus(const Bus &rhs) : data(rhs.data)
{
}

QSharedPointer<geos::geom::Point> Bus::getLocation() const {
    return data->location;
}

Bus::Status Bus::getStatus() const {
    return data->status;
}

Route Bus::getRoute() const {
    return data->route;
}

Direction Bus::getDirection() const {
    return data->direction;
}

Stop Bus::getArrivingStop() const {
    return data->arrivingStop;
}

Stop Bus::getDepartingStop() const {
    return data->departingStop;
}

void Bus::setLocation(QSharedPointer<geos::geom::Point> location) {
    data->location = location;

    if (data->route.getTag() == "green") {
        return;
    }

    QList<Stop> stops = data->direction.getStops();

    for (int i = 0; i < stops.length(); i++) {
        Stop stop = stops.at(i);

        if (data->location->isWithinDistance(stop.getCoordinate().data(), (double)15 / DEGREES_TO_METERS)) {
            data->arrivingStop = stop;
            data->status = Bus::AtStop;
            break;
        } else if (data->location->isWithinDistance(stop.getArrivingSegment().data(), (double)30 / DEGREES_TO_METERS)) {
            data->arrivingStop = stop;
            if (data->location->isWithinDistance(stop.getCoordinate().data(), (double)50 / DEGREES_TO_METERS)) {
                data->status = Bus::Arriving;
            } else {
                data->status = Bus::InTransit;
            }
            break;
        }
    }

    for (int i = 0; i < data->route.getDirections().values().size(); i++) {
        Direction direction = data->route.getDirections().values().at(i);
        for (int j = 0; j < direction.getStops().size(); j++) {
            const Stop stop = direction.getStops().at(j);
            if (stop.getDepartingSegment() == data->arrivingStop.getArrivingSegment()) {
                data->departingStop = stop;
                if (data->location->isWithinDistance(stop.getCoordinate().data(), (double)50 / DEGREES_TO_METERS)) {
                    data->status = Bus::Departing;
                }
            }
        }
    }
}

void Bus::setRoute(Route route) {
    data->route = route;
}

void Bus::setDirection(Direction direction) {
    data->direction = direction;
}

Bus &Bus::operator=(const Bus &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

Bus::~Bus()
{
}
