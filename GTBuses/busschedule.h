#ifndef BUSSCHEDULE_H
#define BUSSCHEDULE_H

#include <QObject>
#include "bus.h"

class BusSchedule : public QObject
{
    Q_OBJECT
public:
    explicit BusSchedule(QObject* rootObject, QObject *parent = 0);

    void setBus(Bus bus);
    void showBusSchedule();

private:
    QObject* rootObject;
    Bus bus;

};

#endif // BUSSCHEDULE_H
