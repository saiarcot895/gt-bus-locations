#ifndef ROUTE_H
#define ROUTE_H

#include <QObject>
#include <QSharedDataPointer>
#include <QList>
#include "direction.h"
#include "stop.h"

class RouteData;

class Route : public QObject
{
public:
    Route();
    Route(const Route &);
    Route &operator=(const Route &);
    ~Route();

    QString getRouteName() const;
    QString getTag() const;
    QList<Direction> getDirections() const;
    QList<Stop> getStops() const;
    int getColor() const;

    void setRouteName(QString routeName);
    void setTag(QString tag);
    void setDirections(QList<Direction> directions);
    void setStops(QList<Stop> stops);
    void setColor(int color);

private:
    QSharedDataPointer<RouteData> data;
};

#endif // ROUTE_H
