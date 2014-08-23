#include "stop.h"
#include <QSharedData>

class StopData : public QSharedData {
public:
    QString stopName;
    QString tag;
    double latitude;
    double longitude;
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

void Stop::setStopName(QString stopName) {
    data->stopName = stopName;
}

void Stop::setTag(QString tag) {
    data->tag = tag;
}

void Stop::setLatitude(double latitude) {
    data->latitude = latitude;
}

void Stop::setLongitude(double longitude) {
    data->longitude = longitude;
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
