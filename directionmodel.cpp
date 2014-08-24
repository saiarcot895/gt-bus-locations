#include "directionmodel.h"

DirectionModel::DirectionModel(QObject *parent) :
    QAbstractListModel(parent)
{
}

void DirectionModel::setDirections(QList<Direction> directions) {
    this->directions = directions;
}

int DirectionModel::rowCount(const QModelIndex &parent) const {
    return directions.size();
}

QHash<int, QByteArray> DirectionModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles.insert(DirectionModel::Name, "name");
    return roles;
}

QVariant DirectionModel::data(const QModelIndex &index, int role) const {
    return directions.at(index.row()).getDirectionName();
}
