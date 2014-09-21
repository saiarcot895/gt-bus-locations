#include "stopwait.h"
#include <QSharedData>

class StopWaitData : public QSharedData {
public:
    int time;
    int busId;
};

StopWait::StopWait() : data(new StopWaitData)
{
}

StopWait::StopWait(const StopWait &rhs) : data(rhs.data)
{
}

int StopWait::getTime() const {
    return data->time;
}

int StopWait::getBusId() const {
    return data->busId;
}

void StopWait::setTime(int time) {
    data->time = time;
}

void StopWait::setBusId(int busId) {
    data->busId = busId;
}

StopWait &StopWait::operator=(const StopWait &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

StopWait::~StopWait()
{
}
