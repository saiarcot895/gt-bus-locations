#ifndef BUSSCHEDULE_H
#define BUSSCHEDULE_H

#include <QObject>
#include "bus.h"
#include "gtwikibusfetcher.h"

class BusSchedule : public QObject
{
    Q_OBJECT
public:
    explicit BusSchedule(GTWikiBusFetcher* fetcher, QObject* rootObject, QObject *parent = 0);

    void setBus(Bus bus);
    void showBusSchedule();
public slots:
    void updateTimes(QString routeTag);
private:
    QObject* rootObject;
    GTWikiBusFetcher* fetcher;
    Bus bus;

};

#endif // BUSSCHEDULE_H
