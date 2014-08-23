#include "route.h"
#include <QSharedData>

class RouteData : public QSharedData {
public:
    QString routeName;
    QString tag;
    QList<Direction> directions;
    QList<Stop> stops;
    int color;
};

Route::Route() : data(new RouteData)
{
}

Route::Route(const Route &rhs) : data(rhs.data)
{
}

QString Route::getRouteName() const {
    return data->routeName;
}

QString Route::getTag() const {
    return data->tag;
}

QList<Direction> Route::getDirections() const {
    return data->directions;
}

QList<Stop> Route::getStops() const {
    return data->stops;
}

int Route::getColor() const {
    return data->color;
}

void Route::setRouteName(QString routeName) {
    data->routeName = routeName;
}

void Route::setTag(QString tag) {
    data->tag = tag;
}

void Route::setDirections(QList<Direction> directions) {
    data->directions = directions;
}

void Route::setStops(QList<Stop> stops) {
    data->stops = stops;
}

void Route::setColor(int color) {
    data->color = color;
}

Route &Route::operator=(const Route &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

Route::~Route()
{
}
