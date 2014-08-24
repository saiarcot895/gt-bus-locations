#ifndef ROUTE_H
#define ROUTE_H

#include <QObject>
#include <QSharedDataPointer>
#include <QHash>
#include <QColor>
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
    QHash<QString, Direction>& getDirections();
    QHash<QString, Stop>& getStops();
    QColor getColor() const;

    void setRouteName(QString routeName);
    void setTag(QString tag);
    void setDirections(QHash<QString, Direction> directions);
    void setStops(QHash<QString, Stop> stops);
    void setColor(QColor color);

private:
    QSharedDataPointer<RouteData> data;
};

#endif // ROUTE_H
