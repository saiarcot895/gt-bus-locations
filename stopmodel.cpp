#include "stopmodel.h"

StopModel::StopModel(QObject *parent) :
    QAbstractListModel(parent)
{
}

void StopModel::setStops(QList<Stop> stops) {
    this->stops = stops;
}

int StopModel::rowCount(const QModelIndex &parent) const {
    return stops.size();
}

QHash<int, QByteArray> StopModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles.insert(StopModel::Name, "name");
    roles.insert(StopModel::Tag, "tag");
    return roles;
}

QVariant StopModel::data(const QModelIndex &index, int role) const {
    if (role == StopModel::Name) {
        return stops.at(index.row()).getStopName();
    } else if (role == StopModel::Tag) {
        return stops.at(index.row()).getTag();
    }
}
