#ifndef STOP_H
#define STOP_H

#include <QObject>

#include <QExplicitlySharedDataPointer>

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
    Q_PROPERTY(double latitude READ getLatitude WRITE setLatitude NOTIFY latitudeChanged)
    Q_PROPERTY(double longitude READ getLongitude WRITE setLongitude NOTIFY longitudeChanged)

    QString getStopName() const;
    QString getTag() const;
    double getLatitude() const;
    double getLongitude() const;
    QList<int>& getStopTimes();

    void setStopName(QString stopName);
    void setTag(QString tag);
    void setLatitude(double latitude);
    void setLongitude(double longitude);

signals:
    void stopNameChanged();
    void tagChanged();
    void latitudeChanged();
    void longitudeChanged();

private:
    QExplicitlySharedDataPointer<StopData> data;
};

#endif // STOP_H
