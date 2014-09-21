#include "stop.h"
#include <QSharedData>

class StopData : public QSharedData {
public:
    QString stopName;
    QString tag;
    QSharedPointer<geos::geom::Point> coordinate;
    QList<int> waitTimes;
    QSharedPointer<geos::geom::LineString> arrivingSegment;
    QSharedPointer<geos::geom::LineString> departingSegment;
};

Stop::Stop() : data(new StopData)
{
}

Stop::Stop(const Stop &rhs) : data(rhs.data)
{
}

QString Stop::getStopName() const {
    return data->stopName;
}

QString Stop::getTag() const {
    return data->tag;
}

QSharedPointer<geos::geom::Point> Stop::getCoordinate() const {
    return data->coordinate;
}

QList<int>& Stop::getStopTimes() {
    return data->waitTimes;
}

QSharedPointer<geos::geom::LineString> Stop::getArrivingSegment() const {
    return data->arrivingSegment;
}

QSharedPointer<geos::geom::LineString> Stop::getDepartingSegment() const {
    return data->departingSegment;
}

void Stop::setStopName(QString stopName) {
    data->stopName = stopName;
    emit stopNameChanged();
}

void Stop::setTag(QString tag) {
    data->tag = tag;
    emit tagChanged();
}

void Stop::setCoordinate(QSharedPointer<geos::geom::Point> coordinate) {
    data->coordinate = coordinate;
    emit coordinateChanged();
}

void Stop::setArrivingSegment(QSharedPointer<geos::geom::LineString> arrivingSegment) {
    data->arrivingSegment = arrivingSegment;
}

void Stop::setDepartingSegment(QSharedPointer<geos::geom::LineString> departingSegment) {
    data->departingSegment = departingSegment;
}

Stop &Stop::operator=(const Stop &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

Stop::~Stop()
{
}
