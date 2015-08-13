#ifndef STOPWAIT_H
#define STOPWAIT_H

#include <QObject>

#include <QExplicitlySharedDataPointer>

class StopWaitData;

class StopWait
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
    QExplicitlySharedDataPointer<StopWaitData> data;
};

#endif // STOPWAIT_H
