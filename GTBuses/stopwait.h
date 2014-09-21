#ifndef STOPWAIT_H
#define STOPWAIT_H

#include <QObject>

#include <QSharedDataPointer>

class StopWaitData;

class StopWait : public QObject
{
public:
    StopWait();
    StopWait(const StopWait &);
    StopWait &operator=(const StopWait &);
    ~StopWait();

    int getTime() const;
    int getBusId() const;

    void setTime(int time);
    void setBusId(int busId);

private:
    QSharedDataPointer<StopWaitData> data;
};

#endif // STOPWAIT_H
