#ifndef DIRECTION_H
#define DIRECTION_H

#include <QObject>
#include <QExplicitlySharedDataPointer>
#include <QList>
#include "stop.h"

class DirectionData;

class Direction
{
public:
    Direction();
    Direction(const Direction &);
    Direction &operator=(const Direction &);
    ~Direction();

    QString getDirectionName() const;
    QString getTag() const;
    QList<Stop>& getStops();
    const QList<Stop> getStops() const;

    void setDirectionName(QString directionName);
    void setTag(QString tag);

private:
    QExplicitlySharedDataPointer<DirectionData> data;
};

#endif // DIRECTION_H
