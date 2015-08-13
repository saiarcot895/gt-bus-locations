#ifndef ROUTE_H
#define ROUTE_H

#include <QObject>
#include <QExplicitlySharedDataPointer>
#include <QHash>
#include <QColor>
#include "direction.h"
#include "stop.h"

class RouteData;
class Bus;

class Route
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
    QHash<int, Bus>& getBuses();
    QStringList& getMessages();

    void setRouteName(QString routeName);
    void setTag(QString tag);
    void setColor(QColor color);

private:
    QExplicitlySharedDataPointer<RouteData> data;
};

#endif // ROUTE_H
