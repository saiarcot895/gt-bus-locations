#include "bus.h"
#include <QSharedData>

class BusData : public QSharedData {
public:
    QSharedPointer<geos::geom::Point> location;
    Bus::Status status;
    Route route;
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

Stop Bus::getArrivingStop() const {
    return data->arrivingStop;
}

Stop Bus::getDepartingStop() const {
    return data->departingStop;
}

void Bus::setLocation(QSharedPointer<geos::geom::Point> location) {
    data->location = location;

    QList<Stop> stops;

    for (int i = 0; i < data->route.getDirections().values().size(); i++) {
        Direction direction = data->route.getDirections().values().at(i);
        stops.append(direction.getStops());
    }

    for (int i = 0; i < stops.length(); i++) {
        Stop prevStop = stops.at(i);
        Stop stop = stops.at((i + 1) % stops.length());

        if (data->location->isWithinDistance(stop.getArrivingSegment().data(), (double)15 / DEGREES_TO_METERS)) {
            data->arrivingStop = stop;
            data->departingStop = prevStop;
            data->status = Bus::InTransit;
            break;
        }
    }
}

void Bus::setRoute(Route route) {
    data->route = route;
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
