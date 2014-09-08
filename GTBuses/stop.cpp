#include "stop.h"
#include <QSharedData>

class StopData : public QSharedData {
public:
    QString stopName;
    QString tag;
    double latitude;
    double longitude;
    QList<int> waitTimes;
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

double Stop::getLatitude() const {
    return data->latitude;
}

double Stop::getLongitude() const {
    return data->longitude;
}

QList<int>& Stop::getStopTimes() {
    return data->waitTimes;
}

void Stop::setStopName(QString stopName) {
    data->stopName = stopName;
    emit stopNameChanged();
}

void Stop::setTag(QString tag) {
    data->tag = tag;
    emit tagChanged();
}

void Stop::setLatitude(double latitude) {
    data->latitude = latitude;
    emit latitudeChanged();
}

void Stop::setLongitude(double longitude) {
    data->longitude = longitude;
    emit longitudeChanged();
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
