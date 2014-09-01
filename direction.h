#ifndef DIRECTION_H
#define DIRECTION_H

#include <QObject>
#include <QSharedDataPointer>
#include <QList>
#include "stop.h"

class DirectionData;

class Direction : public QObject
{
public:
    Direction();
    Direction(const Direction &);
    Direction &operator=(const Direction &);
    ~Direction();

    QString getDirectionName() const;
    QString getTag() const;
    QList<Stop>& getStops();

    void setDirectionName(QString directionName);
    void setTag(QString tag);

private:
    QSharedDataPointer<DirectionData> data;
};

#endif // DIRECTION_H
