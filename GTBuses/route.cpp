#include "route.h"
#include <QSharedData>

class RouteData : public QSharedData {
public:
    QString routeName;
    QString tag;
    QHash<QString, Direction> directions;
    QHash<QString, Stop> stops;
    QColor color;
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

QHash<QString, Direction>& Route::getDirections() {
    return data->directions;
}

QHash<QString, Stop>& Route::getStops() {
    return data->stops;
}

QColor Route::getColor() const {
    return data->color;
}

void Route::setRouteName(QString routeName) {
    data->routeName = routeName;
}

void Route::setTag(QString tag) {
    data->tag = tag;
}

void Route::setColor(QColor color) {
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
