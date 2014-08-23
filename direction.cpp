#include "direction.h"
#include <QSharedData>

class DirectionData : public QSharedData {
public:
    QString directionName;
    QString tag;
    QList<Stop> stops;
};

Direction::Direction() : data(new DirectionData)
{
}

Direction::Direction(const Direction &rhs) : data(rhs.data)
{
}

QString Direction::getDirectionName() const {
    return data->directionName;
}

QString Direction::getTag() const {
    return data->tag;
}

QList<Stop> Direction::getStops() const {
    return data->stops;
}

void Direction::setDirectionName(QString directionName) {
    data->directionName = directionName;
}

void Direction::setTag(QString tag) {
    data->tag = tag;
}

void Direction::setStops(QList<Stop> stops) {
    data->stops = stops;
}

Direction &Direction::operator=(const Direction &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

Direction::~Direction()
{
}
