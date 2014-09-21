#ifndef STOP_H
#define STOP_H

#include <QObject>
#include <QExplicitlySharedDataPointer>
#include <QSharedPointer>
#include <geos/geom/Point.h>
#include <geos/geom/LineString.h>

class StopData;

class Stop : public QObject
{
    Q_OBJECT
public:
    Stop();
    Stop(const Stop &);
    Stop &operator=(const Stop &);
    ~Stop();

    Q_PROPERTY(QString stopName READ getStopName WRITE setStopName NOTIFY stopNameChanged)
    Q_PROPERTY(QString tag READ getTag WRITE setTag NOTIFY tagChanged)
    Q_PROPERTY(QSharedPointer<geos::geom::Point> coordinate READ getCoordinate WRITE setCoordinate NOTIFY coordinateChanged)

    QString getStopName() const;
    QString getTag() const;
    QSharedPointer<geos::geom::Point> getCoordinate() const;
    QList<int>& getStopTimes();
    QSharedPointer<geos::geom::LineString> getArrivingSegment() const;
    QSharedPointer<geos::geom::LineString> getDepartingSegment() const;

    void setStopName(QString stopName);
    void setTag(QString tag);
    void setCoordinate(QSharedPointer<geos::geom::Point> coordinate);
    void setArrivingSegment(QSharedPointer<geos::geom::LineString> arrivingSegment);
    void setDepartingSegment(QSharedPointer<geos::geom::LineString> departingSegment);

signals:
    void stopNameChanged();
    void tagChanged();
    void coordinateChanged();

private:
    QExplicitlySharedDataPointer<StopData> data;
};

#endif // STOP_H
