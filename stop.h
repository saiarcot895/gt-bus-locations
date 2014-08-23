#ifndef STOP_H
#define STOP_H

#include <QObject>

#include <QSharedDataPointer>

class StopData;

class Stop : public QObject
{
public:
    Stop();
    Stop(const Stop &);
    Stop &operator=(const Stop &);
    ~Stop();

    QString getStopName() const;
    QString getTag() const;
    double getLatitude() const;
    double getLongitude() const;

    void setStopName(QString stopName);
    void setTag(QString tag);
    void setLatitude(double latitude);
    void setLongitude(double longitude);

private:
    QSharedDataPointer<StopData> data;
};

#endif // STOP_H
